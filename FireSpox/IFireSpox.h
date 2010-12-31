/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IFireSpox.idl
 */

#ifndef __gen_IFireSpox_h__
#define __gen_IFireSpox_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IFireSpox */
#define IFIRESPOX_IID_STR "8e2a9cb1-72a9-10fa-943d-8fb157e3f9ac"

#define IFIRESPOX_IID \
  {0x8e2a9cb1, 0x72a9, 0x10fa, \
    { 0x94, 0x3d, 0x8f, 0xb1, 0x57, 0xe3, 0xf9, 0xac }}

class NS_NO_VTABLE NS_SCRIPTABLE IFireSpox : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFIRESPOX_IID)

  /* readonly attribute boolean ASR_Enabled; */
  NS_SCRIPTABLE NS_IMETHOD GetASR_Enabled(PRBool *aASR_Enabled) = 0;

  /* readonly attribute boolean TTS_Enabled; */
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Enabled(PRBool *aTTS_Enabled) = 0;

  /* readonly attribute boolean TTS_Ready; */
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Ready(PRBool *aTTS_Ready) = 0;

  /* void Log (in wstring x); */
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) = 0;

  /* void Start (in boolean enableTTS, in boolean enableASR); */
  NS_SCRIPTABLE NS_IMETHOD Start(PRBool enableTTS, PRBool enableASR) = 0;

  /* void Stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(void) = 0;

  /* boolean SupportedPlatform (); */
  NS_SCRIPTABLE NS_IMETHOD SupportedPlatform(PRBool *_retval NS_OUTPARAM) = 0;

  /* void ASR_Pause (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) = 0;

  /* void ASR_Resume (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) = 0;

  /* void TTS_Pause (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) = 0;

  /* void TTS_Purge (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) = 0;

  /* void TTS_Resume (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) = 0;

  /* void TTS_SetRate (in long x); */
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) = 0;

  /* void TTS_SetVolume (in unsigned short x); */
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) = 0;

  /* void TTS_Speak (in wstring x, in long y); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFireSpox, IFIRESPOX_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFIRESPOX \
  NS_SCRIPTABLE NS_IMETHOD GetASR_Enabled(PRBool *aASR_Enabled); \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Enabled(PRBool *aTTS_Enabled); \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Ready(PRBool *aTTS_Ready); \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x); \
  NS_SCRIPTABLE NS_IMETHOD Start(PRBool enableTTS, PRBool enableASR); \
  NS_SCRIPTABLE NS_IMETHOD Stop(void); \
  NS_SCRIPTABLE NS_IMETHOD SupportedPlatform(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x); \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetASR_Enabled(PRBool *aASR_Enabled) { return _to GetASR_Enabled(aASR_Enabled); } \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Enabled(PRBool *aTTS_Enabled) { return _to GetTTS_Enabled(aTTS_Enabled); } \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Ready(PRBool *aTTS_Ready) { return _to GetTTS_Ready(aTTS_Ready); } \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) { return _to Log(x); } \
  NS_SCRIPTABLE NS_IMETHOD Start(PRBool enableTTS, PRBool enableASR) { return _to Start(enableTTS, enableASR); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD SupportedPlatform(PRBool *_retval NS_OUTPARAM) { return _to SupportedPlatform(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) { return _to ASR_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) { return _to ASR_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) { return _to TTS_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) { return _to TTS_Purge(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) { return _to TTS_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) { return _to TTS_SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) { return _to TTS_SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) { return _to TTS_Speak(x, y); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetASR_Enabled(PRBool *aASR_Enabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetASR_Enabled(aASR_Enabled); } \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Enabled(PRBool *aTTS_Enabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTTS_Enabled(aTTS_Enabled); } \
  NS_SCRIPTABLE NS_IMETHOD GetTTS_Ready(PRBool *aTTS_Ready) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTTS_Ready(aTTS_Ready); } \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) { return !_to ? NS_ERROR_NULL_POINTER : _to->Log(x); } \
  NS_SCRIPTABLE NS_IMETHOD Start(PRBool enableTTS, PRBool enableASR) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(enableTTS, enableASR); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD SupportedPlatform(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->SupportedPlatform(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Purge(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Speak(x, y); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFireSpox
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFIRESPOX

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFireSpox)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* readonly attribute boolean ASR_Enabled; */
NS_IMETHODIMP _MYCLASS_::GetASR_Enabled(PRBool *aASR_Enabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean TTS_Enabled; */
NS_IMETHODIMP _MYCLASS_::GetTTS_Enabled(PRBool *aTTS_Enabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean TTS_Ready; */
NS_IMETHODIMP _MYCLASS_::GetTTS_Ready(PRBool *aTTS_Ready)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Log (in wstring x); */
NS_IMETHODIMP _MYCLASS_::Log(const PRUnichar *x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Start (in boolean enableTTS, in boolean enableASR); */
NS_IMETHODIMP _MYCLASS_::Start(PRBool enableTTS, PRBool enableASR)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Stop (); */
NS_IMETHODIMP _MYCLASS_::Stop()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean SupportedPlatform (); */
NS_IMETHODIMP _MYCLASS_::SupportedPlatform(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ASR_Pause (); */
NS_IMETHODIMP _MYCLASS_::ASR_Pause()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ASR_Resume (); */
NS_IMETHODIMP _MYCLASS_::ASR_Resume()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Pause (); */
NS_IMETHODIMP _MYCLASS_::TTS_Pause()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Purge (); */
NS_IMETHODIMP _MYCLASS_::TTS_Purge()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Resume (); */
NS_IMETHODIMP _MYCLASS_::TTS_Resume()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_SetRate (in long x); */
NS_IMETHODIMP _MYCLASS_::TTS_SetRate(PRInt32 x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_SetVolume (in unsigned short x); */
NS_IMETHODIMP _MYCLASS_::TTS_SetVolume(PRUint16 x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Speak (in wstring x, in long y); */
NS_IMETHODIMP _MYCLASS_::TTS_Speak(const PRUnichar *x, PRInt32 y)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFireSpox_h__ */
