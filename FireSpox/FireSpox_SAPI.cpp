#include "FireSpox_SAPI.h"

/* TTS Vars */
ISpVoice * pVoice;
bool tts_loaded = false;

/* Speech Recognition Vars */
LPWSTR pwszText;
HANDLE hEvent;
CSpEvent evt;
SPPHRASE *pParts;
ISpPhrase *pPhrase;
ULONGLONG ullEvents;
CComPtr<ISpRecognizer> cpEngine;
CComPtr<ISpRecoContext> cpRecoCtx;
CComPtr<ISpRecoGrammar> cpGram;
bool asr_loaded = false; 
bool asr_listening = false;

nsCOMPtr<nsIServiceManager> serviceManager;
nsCOMPtr<nsIObserverService> observerService; 

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

NS_IMETHODIMP FireSpox_SAPI::HasSAPI(PRBool *_retval NS_OUTPARAM)
{
	*_retval = true;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Log(const PRUnichar *x)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* Initialize TTS */
NS_IMETHODIMP FireSpox_SAPI::TTS_Load()
{
	HRESULT hr;
	if (FAILED(CoInitialize(0)))
		return NS_ERROR_FAILURE;
	hr = CoCreateInstance(CLSID_SpVoice, 0, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	return hr == S_OK ? NS_OK : NS_ERROR_FAILURE;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_isEnabled(PRBool *_retval NS_OUTPARAM)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* Initialize Speech Recognition */
NS_IMETHODIMP FireSpox_SAPI::ASR_Load()
{
	HRESULT hr;
	if (FAILED(CoInitialize(0)))
		return NS_ERROR_FAILURE;

	hr = cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
	if (FAILED(hr))
		return NS_ERROR_FAILURE;

	hr = cpEngine->CreateRecoContext(&cpRecoCtx);
	if (FAILED(hr))
		return NS_ERROR_FAILURE;

	hr = cpRecoCtx->SetNotifyWin32Event();
	if (FAILED(hr))
		return NS_ERROR_FAILURE;

	hEvent = cpRecoCtx->GetNotifyEventHandle();
	ullEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
	hr = cpRecoCtx->SetInterest(ullEvents, ullEvents);
	if (FAILED(hr))
		return NS_ERROR_FAILURE;

	hr = cpRecoCtx->CreateGrammar(1, &cpGram);
	if (FAILED(hr))
		return NS_ERROR_FAILURE;

	/* TODO: Load grammar rules from resource */
	/*hr = cpGram->LoadCmdFromResource(NULL,
		   MAKEINTRESOURCEW(IDR_ASR_GRAMMAR1),
		   L"ASR_GRAMMAR",
		   MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
		   SPLO_DYNAMIC);*/
	hr = cpGram->LoadCmdFromFile(L"C:\\Documents and Settings\\dale\\My Documents\\github\\firespox\\FireSpox\\commands.cfg", SPLO_STATIC);
	if (FAILED(hr))
		return NS_ERROR_NOT_AVAILABLE;

	hr = cpGram->SetRuleState(0, 0, SPRS_ACTIVE);
	asr_loaded = true;
	asr_listening = true;

	NS_GetServiceManager(getter_AddRefs(serviceManager));
	serviceManager->GetServiceByContractID("@mozilla.org/observer-service;1", NS_GET_IID(nsIObserverService), getter_AddRefs(observerService));

	return FAILED(hr) ? NS_ERROR_FAILURE : NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_isEnabled(PRBool *_retval NS_OUTPARAM)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Unload()
{
	if (tts_loaded)
	{
		pVoice->Release();
		tts_loaded = false;
		if (!asr_loaded)
			CoUninitialize();
	}
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Unload()
{
	if (asr_loaded)
	{
		cpGram.Release();
		cpRecoCtx.Release();
		cpEngine.Release();
		asr_loaded = false;
		asr_listening = false;
		if (!tts_loaded)
			CoUninitialize();
	}
	return NS_OK;	
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

NS_IMETHODIMP FireSpox_SAPI::TTS_Ready(PRBool *_retval NS_OUTPARAM)
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

NS_IMETHODIMP FireSpox_SAPI::ASR_Listen()
{
	observerService->NotifyObservers(NULL, "BrowserCallback", L"listening");
	HRESULT hr;
	while (asr_loaded && asr_listening)
	{
		while ( evt.GetFrom(cpRecoCtx) == S_OK )
		{
			if ( evt.eEventId != SPEI_FALSE_RECOGNITION )
			{
				pPhrase = evt.RecoResult();
				hr = pPhrase->GetPhrase(&pParts);
				ParsePhrase(pParts);

				/* free memory for parts no longer needed */
				CoTaskMemFree(pParts);
				CoTaskMemFree(pwszText);
			}
		}
	}
	return NS_OK;
}

void FireSpox_SAPI::ParsePhrase(SPPHRASE *parts)
{
	observerService->NotifyObservers(NULL, "BrowserCallback", L"parsing");
	switch (parts->ullGrammarID)
	{
	case VID_SPOX:
		switch (parts->LangID)
		{
		case VID_BACK:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_back");
			break;
		case VID_FORWARD:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_forward");
			break;
		case VID_REFRESH:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_refresh");
			break;
		case VID_STOP:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_stop");
			break;
		case VID_HOME:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_home");
			break;
		case VID_EXIT:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_exit");
			break;
		case VID_HISTORY:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_history");
			break;
		case VID_BOOKMARKS:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_bookmarks");
			break;
		case VID_WAIT:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"tts_pause");
			break;
		case VID_RESUME:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"tts_resume");
			break;
		case VID_LIST:
			observerService->NotifyObservers(NULL, "BrowserCallback", L"browser_list");
			break;
		default:
			/* secondary command was not vaild */
			break;
		}
	default:
		/* Top command was not valid */
		break;
	}
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Pause()
{
	asr_listening = false;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Resume()
{
	asr_listening = true;
	ASR_Listen();
	return NS_OK;
}
