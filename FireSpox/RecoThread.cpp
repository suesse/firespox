#include "RecoThread.h"

MSG asr_msg;
HWND asr_window;

CSpEvent recoEvent;
LPWSTR pwszText;
SPPHRASE *pParts;
ISpPhrase *pPhrase;
CComPtr<ISpNotifySource> notifySource;
CComPtr<ISpRecognizer> cpEngine;
CComPtr<ISpRecoContext> cpRecoCtx;
CComPtr<ISpRecoGrammar> cpGram;
UINT asr_events;
nsCOMPtr<nsIServiceManager> serviceManager;
nsCOMPtr<nsIWindowMediator> windowMediator;
nsIDOMWindowInternal *currentBrowserWindow;

void ASR_Init();
void ASR_InitWindows();
void ASR_InitSAPI();
void ASR_InitXPCOM();
LRESULT CALLBACK ASR_WndProc(HWND, UINT, WPARAM, LPARAM);
void ASR_Uninit();
LRESULT ASR_ProcessEvent();

/* Thread entry point */
DWORD WINAPI ASR_Thread(LPVOID pParams)
{
	ASR_Init();
	while (GetMessage(&asr_msg, NULL, 0, 0))
	{
		TranslateMessage(&asr_msg);
		DispatchMessage(&asr_msg);
	}

	ASR_Uninit();
	return S_OK;
}

void ASR_Init()
{
	ASR_InitXPCOM();
	ASR_InitWindows();
	ASR_InitSAPI();
}

void ASR_InitXPCOM()
{
	/* Setup window mediator in order to communicate to firefox window. */
	NS_GetServiceManager(getter_AddRefs(serviceManager));
	serviceManager->GetServiceByContractID(
		"@mozilla.org/appshell/window-mediator;1",
		NS_GET_IID(nsIWindowMediator),
		getter_AddRefs(windowMediator));
}

void ASR_InitWindows()
{
	static char szAppName[] = "FireSpox_DLL";
	WNDCLASS wndclass;
	wndclass.style = CS_GLOBALCLASS;
	wndclass.lpfnWndProc = ASR_WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;;

	RegisterClass(&wndclass);

	asr_window = CreateWindowExW(
		WS_EX_NOACTIVATE,
		L"FireSpox_SAPI",
		L"FireSpox_DLL",
		CS_GLOBALCLASS,
		0, 0, 0, 0,
		HWND_MESSAGE,
		0, 0, 0);
}

void ASR_InitSAPI()
{
	CoInitialize(0);
	cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
	cpEngine->SetInput(NULL, false);
	cpEngine->CreateRecoContext(&cpRecoCtx);
	cpRecoCtx->SetNotifyWin32Event();
	//hEvent = cpRecoCtx->GetNotifyEventHandle();
	asr_events = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
	//cpRecoCtx->SetNotifyWindowMessage(window, events, 0, 0);
	cpRecoCtx->SetInterest(asr_events, asr_events);
	cpRecoCtx->CreateGrammar(1, &cpGram);
	cpGram->LoadCmdFromResource(
		NULL,
		MAKEINTRESOURCEW(IDR_ASR_GRAMMAR1),
		L"ASR_GRAMMAR",
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
		SPLO_DYNAMIC);
	//cpGram->LoadCmdFromFile(L"C:\\Documents and Settings\\dale\\My Documents\\github\\firespox\\FireSpox\\commands.cfg", SPLO_STATIC);
	
	//cpGram->SetRuleIdState(0, SPRS_ACTIVE);
	cpGram->SetRuleState(0, 0, SPRS_ACTIVE);
}

void ASR_Uninit()
{
	cpGram.Release();
	cpRecoCtx.Release();
	cpEngine.Release();
	CoUninitialize();
}

LRESULT CALLBACK ASR_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case SPEI_RECOGNITION:
		ASR_ProcessEvent();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT ASR_ProcessEvent()
{
	while (recoEvent.GetFrom(cpRecoCtx) == S_OK)
	{
		if ( recoEvent.eEventId != SPEI_FALSE_RECOGNITION )
		{
			const SPPHRASEPROPERTY *prop;
			SPPHRASERULE rule;
			pPhrase = recoEvent.RecoResult();
			pPhrase->GetPhrase(&pParts);

			rule = pParts->Rule;
			prop = pParts->pProperties;
			
			if (VID_COMMANDS == rule.ulId)
			{
				windowMediator->GetMostRecentWindow(L"navigator:browser", &currentBrowserWindow);
				switch (prop->ulId)
				{
				case VID_BACK:
					/* TODO: Check if possible to go back */
					currentBrowserWindow->Back();
					break;
				case VID_FORWARD:
					/* TODO: Check if possible to go forward */
					currentBrowserWindow->Forward();
					break;
				case VID_REFRESH:
					break;
				case VID_STOP:
					currentBrowserWindow->Stop();
					break;
				case VID_HOME:
					currentBrowserWindow->Home();
					break;
				case VID_EXIT:
					currentBrowserWindow->Close();
					break;
				case VID_HISTORY:
					break;
				case VID_BOOKMARKS:
					break;
				case VID_WAIT:
					//FireSpox_SAPI::TTS_Pause();
					break;
				case VID_RESUME:
					//FireSpox_SAPI::TTS_Resume();
					break;
				case VID_LIST:
					break;
				}
			}

			CoTaskMemFree(pParts); // free memory for parts we no longer need.
			CoTaskMemFree(pwszText);

		}
	}
	return S_OK;
}
