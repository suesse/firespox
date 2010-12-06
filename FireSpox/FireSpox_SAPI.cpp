#include "FireSpox_SAPI.h"

#include<iostream>

HWND hwnd;

/* TTS Vars */
ISpVoice * pVoice;
bool tts_loaded = false;

/* Speech Recognition Vars */
MSG msg;
LPWSTR pwszText;
HANDLE hEvent;
CSpEvent recoEvent;
SPPHRASE *pParts;
ISpPhrase *pPhrase;
ULONGLONG ullEvents;
CComPtr<ISpRecognizer> cpEngine;
CComPtr<ISpRecoContext> cpRecoCtx;
CComPtr<ISpRecoGrammar> cpGram;
bool asr_loaded = false;
bool asr_listening = false;
unsigned int asrThread;
nsCOMPtr<nsIServiceManager> serviceManager;
nsCOMPtr<nsIObserverService> observerService;
nsIThread *mainThread;

/* Macro NS_IMPL_ISUPPORTS1: Implements AddRef, Release, and QueryInterface */
NS_IMPL_ISUPPORTS1(FireSpox_SAPI, IFireSpox)

FireSpox_SAPI::FireSpox_SAPI()
{
	/* Nothing to do at this time. */
}

FireSpox_SAPI::~FireSpox_SAPI()
{
	/* Nothing to do at this time. */
}

NS_IMETHODIMP FireSpox_SAPI::SupportedPlatform(PRBool *_retval NS_OUTPARAM)
{
	/* Determine if SAPI runtime is installed */
	*_retval = true;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Log(const PRUnichar *x)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP FireSpox_SAPI::GetTTS_Enabled(PRBool *rtn)
{
	*rtn = tts_loaded;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::GetASR_Enabled(PRBool *rtn)
{
	*rtn = asr_loaded;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Load(PRBool loadTTS, PRBool loadASR)
{
	static char szAppName[] = "FireSpox_DLL";
	WNDCLASS wndclass;
	wndclass.style = CS_GLOBALCLASS;
	wndclass.lpfnWndProc = SPWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;;

	RegisterClass(&wndclass);

	CreateWindow(szAppName, NULL, NULL, 0, 0, 0, 0, 
		HWND_MESSAGE, NULL, NULL, NULL);

	NS_GetMainThread(&mainThread);

	NS_GetServiceManager(getter_AddRefs(serviceManager));
	serviceManager->GetServiceByContractID(
		"@mozilla.org/observer-service;1",
		NS_GET_IID(nsIObserverService),
		getter_AddRefs(observerService));

	observerService->NotifyObservers(
		NULL, "BrowserCallback", L"spox | registered listener with dll");
	
	if (FAILED(CoInitialize(0)))
		return NS_ERROR_FAILURE;

	if (loadTTS)
	{
		if (FAILED(TTS_Load()))
			return NS_ERROR_FAILURE;
		tts_loaded = true;
	}

	if (loadASR)
	{
		if (FAILED(ASR_Load()))
			return NS_ERROR_ABORT;
		asr_loaded = true;
	}
	
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Start()
{
	
	observerService->NotifyObservers(NULL, "BrowserCallback", L"spox | listening...");
	bool st;
	while (st = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		observerService->NotifyObservers(NULL, "BrowserCallback", L"spox | listening...");
		if (st == -1)
			observerService->NotifyObservers(NULL, "BrowserCallback", L"spox | error!");
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	observerService->NotifyObservers(NULL, "BrowserCallback", L"spox | done listening");
	return NS_OK;
}

LRESULT CALLBACK SPWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_RECOEVENT:
		ProcessRecoEvent();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT ProcessRecoEvent()
{
	while (recoEvent.GetFrom(cpRecoCtx) == S_OK)
	{
		if ( recoEvent.eEventId == SPEI_FALSE_RECOGNITION )
					std::wcout << "No recognition" << std::endl;
				else
				{
					pPhrase = recoEvent.RecoResult();
					pPhrase->GetPhrase(&pParts);
					pPhrase->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &pwszText, 0); //(get from beginning, get all parts)
					pVoice->Speak(pwszText, 0, NULL);
					std::wcout << pwszText << " (" << pParts->Rule.Confidence << ") " << std::endl;

					CoTaskMemFree(pParts); // free memory for parts we no longer need.
					CoTaskMemFree(pwszText);

				}
	}
	return S_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Stop()
{
	if (tts_loaded)
		TTS_Unload();

	if (asr_loaded)
		ASR_Unload();

	CoUninitialize();
	return NS_OK;
}

/* Initialize TTS */
HRESULT FireSpox_SAPI::TTS_Load()
{
	observerService->NotifyObservers(
		NULL, "BrowserCallback", L"spox | TTS_Loading");

	return CoCreateInstance(CLSID_SpVoice, 0, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
}


/* Initialize Speech Recognition */
HRESULT FireSpox_SAPI::ASR_Load()
{
	observerService->NotifyObservers(
		NULL, "BrowserCallback", L"spox | ASR_Loading");

	if (FAILED(cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer)))
		return E_FAIL;

	if (FAILED(cpEngine->CreateRecoContext(&cpRecoCtx)))
		return E_FAIL;

	if (FAILED(cpRecoCtx->SetNotifyWin32Event()))
		return E_FAIL;

	//if (FAILED(cpRecoCtx->SetNotifyWindowMessage(hwnd, WM_RECOEVENT, 0, 0)))
	//	return E_FAIL;

	hEvent = cpRecoCtx->GetNotifyEventHandle();
	ullEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
	if (FAILED(cpRecoCtx->SetInterest(ullEvents, ullEvents)))
		return E_FAIL;

	if (FAILED(cpRecoCtx->CreateGrammar(1, &cpGram)))
		return E_FAIL;

	/* TODO: Load grammar rules from resource */
	/*hr = cpGram->LoadCmdFromResource(NULL, MAKEINTRESOURCEW(IDR_ASR_GRAMMAR1), L"ASR_GRAMMAR", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SPLO_DYNAMIC);*/
	if (FAILED(cpGram->LoadCmdFromFile(L"C:\\Documents and Settings\\dale\\My Documents\\Visual Studio 2010\\Projects\\play_firespox\\FireSpox\\commands.cfg", SPLO_STATIC)))
		return E_FAIL;
	
	//if (FAILED(cpGram->SetRuleIdState(0, SPRS_ACTIVE)))
	if (FAILED(cpGram->SetRuleState(0, 0, SPRS_ACTIVE)))
		return E_FAIL;

	return S_OK;
}

HRESULT FireSpox_SAPI::TTS_Unload()
{
	pVoice->Release();
	tts_loaded = false;
	return S_OK;
}

HRESULT FireSpox_SAPI::ASR_Unload()
{	
	cpGram.Release();
	cpRecoCtx.Release();
	cpEngine.Release();
	asr_loaded = false;
	return S_OK;	
}


/* text - string to be spoken.
   param - 0 synchronous, 
		   1 asynchronous, 
		   2 purge before speaking */
NS_IMETHODIMP FireSpox_SAPI::TTS_Speak(const PRUnichar *text, PRInt32 param)
{
	if (pVoice != NULL)
	{
		pVoice->Speak(text, param, NULL);
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Pause()
{
	if (pVoice != NULL)
	{
		pVoice->Pause();
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Resume()
{
	if (pVoice != NULL)
	{
		pVoice->Resume();
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Purge()
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_SetRate(PRInt32 rate)
{
	if (pVoice != NULL)
	{
		pVoice->SetRate(rate);
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_SetVolume(PRUint16 volume)
{
	if (pVoice != NULL)
	{
		pVoice->SetVolume(volume);
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::GetTTS_Ready(PRBool *_retval NS_OUTPARAM)
{
	if (pVoice != NULL)
	{
		SPVOICESTATUS voiceStatus;
		pVoice->GetStatus(&voiceStatus, NULL);
		if (voiceStatus.dwRunningState == 1)
		{
			*_retval = true;
			return NS_OK;
		}
		*_retval = false;
		return NS_OK;
	}
	return NS_ERROR_NOT_INITIALIZED;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Pause()
{
	//SuspendThread(asrThread);
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Resume()
{
	//ResumeThread(asrThread);
	return NS_OK;
}
