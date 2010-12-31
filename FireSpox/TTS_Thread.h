/* Windows includes */
#include <Windows.h>
#include <sphelper.h>

/* XPCOM includes */
#include "nsCOMPtr.h"
#include "nsIDOMWindowInternal.h"
#include "nsIServiceManager.h"
#include "nsIWindowMediator.h"

#define TTS_PREF 0xF100

#define TTS_PREF_RATE 0xF101
#define TTS_PREF_VOLUME 0xF102

struct TTS_Status {
	HANDLE thread;
	bool enabled; // TODO: really need this attribute?
	bool ready;
};

DWORD WINAPI TTS_Thread(LPVOID);
TTS_Status TTS_GetStatus(HANDLE thread);