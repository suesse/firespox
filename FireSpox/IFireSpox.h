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

  /* boolean TTS_isEnabled (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_isEnabled(PRBool *_retval NS_OUTPARAM) = 0;

  /* void TTS_Load (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Load(void) = 0;

  /* void TTS_Speak (in wstring x, in long y); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) = 0;

  /* void TTS_Pause (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) = 0;

  /* void TTS_Resume (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) = 0;

  /* void TTS_Purge (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) = 0;

  /* void TTS_SetRate (in long x); */
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) = 0;

  /* void TTS_SetVolume (in unsigned short x); */
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) = 0;

  /* boolean TTS_Ready (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Ready(PRBool *_retval NS_OUTPARAM) = 0;

  /* void TTS_Unload (); */
  NS_SCRIPTABLE NS_IMETHOD TTS_Unload(void) = 0;

  /* boolean ASR_isEnabled (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_isEnabled(PRBool *_retval NS_OUTPARAM) = 0;

  /* void ASR_Listen (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Listen(void) = 0;

  /* void ASR_Load (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Load(void) = 0;

  /* void ASR_Pause (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) = 0;

  /* void ASR_Resume (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) = 0;

  /* void ASR_Unload (); */
  NS_SCRIPTABLE NS_IMETHOD ASR_Unload(void) = 0;

  /* boolean hasSAPI (); */
  NS_SCRIPTABLE NS_IMETHOD HasSAPI(PRBool *_retval NS_OUTPARAM) = 0;

  /* void log (in wstring x); */
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFireSpox, IFIRESPOX_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFIRESPOX \
  NS_SCRIPTABLE NS_IMETHOD TTS_isEnabled(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Load(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void); \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x); \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Ready(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD TTS_Unload(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_isEnabled(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Listen(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Load(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void); \
  NS_SCRIPTABLE NS_IMETHOD ASR_Unload(void); \
  NS_SCRIPTABLE NS_IMETHOD HasSAPI(PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD TTS_isEnabled(PRBool *_retval NS_OUTPARAM) { return _to TTS_isEnabled(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Load(void) { return _to TTS_Load(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) { return _to TTS_Speak(x, y); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) { return _to TTS_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) { return _to TTS_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) { return _to TTS_Purge(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) { return _to TTS_SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) { return _to TTS_SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Ready(PRBool *_retval NS_OUTPARAM) { return _to TTS_Ready(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Unload(void) { return _to TTS_Unload(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_isEnabled(PRBool *_retval NS_OUTPARAM) { return _to ASR_isEnabled(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Listen(void) { return _to ASR_Listen(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Load(void) { return _to ASR_Load(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) { return _to ASR_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) { return _to ASR_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Unload(void) { return _to ASR_Unload(); } \
  NS_SCRIPTABLE NS_IMETHOD HasSAPI(PRBool *_retval NS_OUTPARAM) { return _to HasSAPI(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) { return _to Log(x); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFIRESPOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD TTS_isEnabled(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_isEnabled(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Load(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Load(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Speak(const PRUnichar *x, PRInt32 y) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Speak(x, y); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Pause(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Resume(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Purge(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Purge(); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetRate(PRInt32 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_SetRate(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_SetVolume(PRUint16 x) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_SetVolume(x); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Ready(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Ready(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TTS_Unload(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->TTS_Unload(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_isEnabled(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_isEnabled(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Listen(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Listen(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Load(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Load(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Pause(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Pause(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Resume(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Resume(); } \
  NS_SCRIPTABLE NS_IMETHOD ASR_Unload(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ASR_Unload(); } \
  NS_SCRIPTABLE NS_IMETHOD HasSAPI(PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->HasSAPI(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Log(const PRUnichar *x) { return !_to ? NS_ERROR_NULL_POINTER : _to->Log(x); } 

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

/* boolean TTS_isEnabled (); */
NS_IMETHODIMP _MYCLASS_::TTS_isEnabled(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Load (); */
NS_IMETHODIMP _MYCLASS_::TTS_Load()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Speak (in wstring x, in long y); */
NS_IMETHODIMP _MYCLASS_::TTS_Speak(const PRUnichar *x, PRInt32 y)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Pause (); */
NS_IMETHODIMP _MYCLASS_::TTS_Pause()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Resume (); */
NS_IMETHODIMP _MYCLASS_::TTS_Resume()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Purge (); */
NS_IMETHODIMP _MYCLASS_::TTS_Purge()
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

/* boolean TTS_Ready (); */
NS_IMETHODIMP _MYCLASS_::TTS_Ready(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TTS_Unload (); */
NS_IMETHODIMP _MYCLASS_::TTS_Unload()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean ASR_isEnabled (); */
NS_IMETHODIMP _MYCLASS_::ASR_isEnabled(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ASR_Listen (); */
NS_IMETHODIMP _MYCLASS_::ASR_Listen()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ASR_Load (); */
NS_IMETHODIMP _MYCLASS_::ASR_Load()
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

/* void ASR_Unload (); */
NS_IMETHODIMP _MYCLASS_::ASR_Unload()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean hasSAPI (); */
NS_IMETHODIMP _MYCLASS_::HasSAPI(PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void log (in wstring x); */
NS_IMETHODIMP _MYCLASS_::Log(const PRUnichar *x)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFireSpox_h__ */
