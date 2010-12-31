#include "TTS_Thread.h"

MSG tts_msg;
HWND tts_window;
ISpVoice *pVoice;

bool TTS_GetReady();
void TTS_Init();
void TTS_Uninit();

void TTS_ChangePreference(WPARAM, LPARAM);

/* Thread entry point */
DWORD WINAPI TTS_Thread(LPVOID pParams)
{
	TTS_Init();
	while (GetMessage(&tts_msg, NULL, 0, 0))
	{
		TranslateMessage(&tts_msg);
		DispatchMessage(&tts_msg);
	}

	TTS_Uninit();
	return S_OK;
}

TTS_Status TTS_GetStatus(HANDLE thread)
{
	/* TODO: Get the status for the thread passed to the function */
	TTS_Status status;
	status.thread = thread;
	status.enabled = true;
	status.ready = true;

	return status;
}

void TTS_Init()
{
	CoInitialize(0);
	CoCreateInstance(
		CLSID_SpVoice,
		0,
		CLSCTX_ALL,
		IID_ISpVoice,
		(void **)&pVoice);
}

void TTS_Uninit()
{
	pVoice->Release();
	pVoice = NULL;
	CoUninitialize();
}

LRESULT CALLBACK TTS_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case TTS_PREF:
		TTS_ChangePreference(wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void TTS_ChangePreference(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case TTS_PREF_RATE:
		TTS_SetRate(lParam);
		break;
	case TTS_PREF_VOLUME:
		TTS_SetVolume(lParam);
		break;
	}
}

/* text - string to be spoken.
   param - 0 synchronous, 
		   1 asynchronous, 
		   2 purge before speaking */
void TTS_Speak(const PRUnichar *text, PRInt32 param)
{
	if (pVoice != NULL)
		pVoice->Speak(text, param, NULL);
}

//void TTS_Pause()
//{
//	if (pVoice != NULL)
//		pVoice->Pause();
//}
//
//void TTS_Resume()
//{
//	if (pVoice != NULL)
//		pVoice->Resume();
//}

void TTS_Purge()
{
	/* TODO: Implement this */
}

void TTS_SetRate(int rate)
{
	if (pVoice != NULL)
		pVoice->SetRate(rate);
}

void TTS_SetVolume(uint volume)
{
	if (pVoice != NULL)
		pVoice->SetVolume(volume);
}

bool TTS_GetReady()
{
	if (pVoice != NULL)
	{
		SPVOICESTATUS voiceStatus;
		pVoice->GetStatus(&voiceStatus, NULL);
		if (voiceStatus.dwRunningState == 1)
			return true;
		return false;
	}
}