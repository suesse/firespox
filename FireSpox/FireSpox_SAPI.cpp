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
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP FireSpox_SAPI::Log(const PRUnichar *x)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* Initialize TTS */
NS_IMETHODIMP FireSpox_SAPI::TTS_Load()
{
	HRESULT hr;
	if (FAILED(CoInitializeEx(0,0)))
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
	if (FAILED(CoInitializeEx(0,0)))
		return NS_ERROR_FAILURE;

	hr = cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hr = cpEngine->CreateRecoContext(&cpRecoCtx);
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hr = cpRecoCtx->SetNotifyWin32Event();
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hEvent = cpRecoCtx->GetNotifyEventHandle();
	ullEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
	hr = cpRecoCtx->SetInterest(ullEvents, ullEvents);
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hr = cpRecoCtx->CreateGrammar(1, &cpGram);
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hr = cpGram->LoadCmdFromFile(L"firespox.cfg", SPLO_STATIC); // Dynamic if defining rules at runtime
	if (hr != S_OK)
		return NS_ERROR_FAILURE;

	hr = cpGram->SetRuleState(0, 0, SPRS_ACTIVE);
	return hr == S_OK ? NS_OK : NS_ERROR_FAILURE;
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

NS_IMETHODIMP FireSpox_SAPI::ASR_Pause()
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP FireSpox_SAPI::ASR_Resume()
{
	return NS_ERROR_NOT_IMPLEMENTED;
}
