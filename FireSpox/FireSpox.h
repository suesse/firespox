/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM FireSpox.idl
 */

#ifndef __gen_FireSpox_h__
#define __gen_FireSpox_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    FireSpox */
#define FIRESPOX_IID_STR "8e2a9cb1-72a9-10fa-943d-8fb157e3f9ac"

#define FIRESPOX_IID \
  {0x8e2a9cb1, 0x72a9, 0x10fa, \
    { 0x94, 0x3d, 0x8f, 0xb1, 0x57, 0xe3, 0xf9, 0xac }}

class NS_NO_VTABLE NS_SCRIPTABLE FireSpox : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(FIRESPOX_IID)

  /* void Init (); */
  NS_SCRIPTABLE NS_IMETHOD Init(void) = 0;

  /* void Shutdown (); */
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) = 0;

  /* void Speak (in wstring x, in long y); */
  NS_SCRIPTABLE NS_IMETHOD Speak(const PRUnichar *x, PRInt32 y) = 0;

  /* void PauseSpeech (); */
  NS_SCRIPTABLE NS_IMETHOD PauseSpeech(void) = 0;

  /* void ResumeSpeech (); */
  NS_SCRIPTABLE NS_IMETHOD ResumeSpeech(void) = 0;

  /* void PurgeSpeech (); */
  NS_SCRIPTABLE NS_IMETHOD PurgeSpeech(void) = 0;

  /* void SetRate (in long x); */
  NS_SCRIPTABLE NS_IMETHOD SetRate(PRInt32 x) = 0;

  /* void SetVolume (in unsigned short x); */
  NS_SCRIPTABLE NS_IMETHOD SetVolume(PRUint16 x) = 0;

  /* boolean ReadyToSpeak (); */
  NS_SCRIPTABLE NS_IMETHOD ReadyToSpeak(PRBool *_retval NS_OUTPARAM) = 0;

  /* void PauseReco (); */
  NS_SCRIPTABLE NS_IMETHOD PauseReco(void) = 0;

  /* void ResumeReco (); */
  NS_SCRIPTABLE NS_IMETHOD ResumeReco(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(FireSpox, FIRESPOX_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_FIRESPOX \
  NS_SCRIPTABLE NS_IMETHOD Init(void); \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void); \
  NS_SCRIPTABLE NS_IMETHOD Speak(const PRUnichar *x, PRInt32 y); \
  NS_SCRIPTABLE NS_IMETHOD PauseSpeech(void); \
  NS_SCRIPTABLE NS_IMETHOD ResumeSpeech(void); \
  NS_SCRIPTABLE NS_IMETHOD PurgeSpeech(void); \
  NS_SCRIPTABLE NS_IMETHOD SetRate(PRInt32 x); \
  NS_SCRIPTABLE NS_IMETHOD SetVolume(PRUint16 x); \
  NS_SCRIPTABLE NS_IMETHOD ReadyToSpeak(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD PauseReco(void); \
  NS_SCRIPTABLE NS_IMETHOD ResumeReco(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_FIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(void) { return _to Init(); } \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) { return _to Shutdown(); } \
  NS_SCRIPTABLE NS_IMETHOD Speak(const PRUnichar *x, PRInt32 y) { return _to Speak(x, y); } \
  NS_SCRIPTABLE NS_IMETHOD PauseSpeech(void) { return _to PauseSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD ResumeSpeech(void) { return _to ResumeSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD PurgeSpeech(void) { return _to PurgeSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD SetRate(PRInt32 x) { return _to SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD SetVolume(PRUint16 x) { return _to SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD ReadyToSpeak(PRBool *_retval NS_OUTPARAM) { return _to ReadyToSpeak(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD PauseReco(void) { return _to PauseReco(); } \
  NS_SCRIPTABLE NS_IMETHOD ResumeReco(void) { return _to ResumeReco(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_FIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(); } \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } \
  NS_SCRIPTABLE NS_IMETHOD Speak(const PRUnichar *x, PRInt32 y) { return !_to ? NS_ERROR_NULL_POINTER : _to->Speak(x, y); } \
  NS_SCRIPTABLE NS_IMETHOD PauseSpeech(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PauseSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD ResumeSpeech(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ResumeSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD PurgeSpeech(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PurgeSpeech(); } \
  NS_SCRIPTABLE NS_IMETHOD SetRate(PRInt32 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD SetVolume(PRUint16 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD ReadyToSpeak(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReadyToSpeak(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD PauseReco(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PauseReco(); } \
  NS_SCRIPTABLE NS_IMETHOD ResumeReco(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ResumeReco(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public FireSpox
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_FIRESPOX

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, FireSpox)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void Init (); */
NS_IMETHODIMP _MYCLASS_::Init()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Shutdown (); */
NS_IMETHODIMP _MYCLASS_::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Speak (in wstring x, in long y); */
NS_IMETHODIMP _MYCLASS_::Speak(const PRUnichar *x, PRInt32 y)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PauseSpeech (); */
NS_IMETHODIMP _MYCLASS_::PauseSpeech()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ResumeSpeech (); */
NS_IMETHODIMP _MYCLASS_::ResumeSpeech()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PurgeSpeech (); */
NS_IMETHODIMP _MYCLASS_::PurgeSpeech()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetRate (in long x); */
NS_IMETHODIMP _MYCLASS_::SetRate(PRInt32 x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetVolume (in unsigned short x); */
NS_IMETHODIMP _MYCLASS_::SetVolume(PRUint16 x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean ReadyToSpeak (); */
NS_IMETHODIMP _MYCLASS_::ReadyToSpeak(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PauseReco (); */
NS_IMETHODIMP _MYCLASS_::PauseReco()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ResumeReco (); */
NS_IMETHODIMP _MYCLASS_::ResumeReco()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_FireSpox_h__ */
