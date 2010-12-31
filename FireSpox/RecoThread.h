/* Windows includes */
#include <Windows.h>
#include <sphelper.h>

/* Project includes */
#include "ASR_Commands.h"
#include "resource.h"

/* XPCOM includes */
#include "nsCOMPtr.h"
#include "nsIDOMWindowInternal.h"
#include "nsIServiceManager.h"
#include "nsIWindowMediator.h"

DWORD WINAPI ASR_Thread(LPVOID);
