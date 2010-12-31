#include "FireSpox_SAPI.h"

#include<iostream>

nsCOMPtr<nsIObserverService> observerService;
HANDLE asr_thread = NULL;
HANDLE tts_thread = NULL;
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
	return tts_thread != NULL;
}

NS_IMETHODIMP FireSpox_SAPI::GetTTS_Ready(PRBool *rtn)
{
	TTS_Status status = TTS_GetStatus(tts_thread);
	*rtn = status.ready;
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::GetASR_Enabled(PRBool *rtn)
{
	return asr_thread != NULL;
}

NS_IMETHODIMP FireSpox_SAPI::Start(PRBool TTS, PRBool ASR)
{
	if (TTS)
		tts_thread = CreateThread(0, 0, TTS_Thread, 0, 0, 0);

	if (ASR)
		asr_thread = CreateThread(0, 0, ASR_Thread, 0, 0, 0);

	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::Stop()
{
	PostThreadMessage(GetThreadId(tts_thread), WM_DESTROY, 0, 0);
	PostThreadMessage(GetThreadId(asr_thread), WM_DESTROY, 0, 0);

	WaitForSingleObject(asr_thread, INFINITE);
	WaitForSingleObject(tts_thread, INFINITE);

	CloseHandle(tts_thread);
	CloseHandle(asr_thread);

	CoUninitialize();
	return NS_OK;
}

/* TTS Functionality */
NS_IMETHODIMP FireSpox_SAPI::TTS_Pause()
{
	SuspendThread(tts_thread);
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Resume()
{
	ResumeThread(tts_thread);
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::TTS_Purge(){}

NS_IMETHODIMP FireSpox_SAPI::TTS_SetRate(PRInt32 rate)
{
	if (tts_thread != NULL)
	{
		PostThreadMessage(
			GetThreadId(tts_thread),
			TTS_PREF,
			TTS_PREF_RATE,
			rate);
	}
}

NS_IMETHODIMP FireSpox_SAPI::TTS_SetVolume(PRUint16 volume)
{
	if (tts_thread != NULL)
	{
		LPARAM lparam;
		PostThreadMessage(
			GetThreadId(tts_thread),
			TTS_PREF,
			TTS_PREF_VOLUME,
			volume);
	}

}
NS_IMETHODIMP FireSpox_SAPI::TTS_Speak(const PRUnichar *x, PRInt32 y){}


/* ASR Functionality */
NS_IMETHODIMP FireSpox_SAPI::ASR_Pause()
{
	SuspendThread(asr_thread);
	return NS_OK;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Resume()
{
	ResumeThread(asr_thread);
	return NS_OK;
}
