#ifndef __FIRESPOX_SAPI_H__
#define __FIRESPOX_SAPI_H__

#pragma warning (disable:4995)

#include <windows.h>
#include <sphelper.h>

#include "nsCOMPtr.h"
#include "nsIComponentManager.h"
#include "nsIDOMWindowInternal.h"
#include "nsIGenericFactory.h"
#include "nsIObserverService.h"
#include "nsIServiceManager.h"
#include "nsIThreadManager.h"
#include "nsIWindowMediator.h"
#include "nsThreadUtils.h"
#include "xpccomponents.h"

#include "ASR_Commands.h"
#include "IFireSpox.h"
#include "resource.h"

#define MY_COMPONENT_CONTRACTID "@firespox.mnsu.edu/FIRESPOX_SAPI;1"
#define MY_COMPONENT_CLASSNAME "FIRESPOX SAPI"
#define MY_COMPONENT_CID \
	{0x8e2a9cb1, 0x72a9, 0x10fa, \
	  { 0x94, 0x3d, 0x8f, 0xb1, 0x57, 0xe3, 0xf9, 0xac }}

#define WM_RECOEVENT	WM_APP
#define TIMEOUT			12000

/* Global Functions */
LRESULT CALLBACK SPWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT ProcessRecoEvent();

class FireSpox_SAPI : public IFireSpox
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_IFIRESPOX

	FireSpox_SAPI();
private:
	~FireSpox_SAPI();
	HRESULT ASR_Load();
	HRESULT ASR_Unload();
	HRESULT TTS_Load();
	HRESULT TTS_Unload();
};

#endif /* __FIRESPOX_SAPI_H__ */
