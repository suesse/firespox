#ifndef __FIRESPOX_SAPI_H__
#define __FIRESPOX_SAPI_H__

#include <windows.h>
#include <sphelper.h>
#include "nsIGenericFactory.h"
#include "IFireSpox.h"

#define MY_COMPONENT_CONTRACTID "@firespox.mnsu.edu/FIRESPOX_SAPI;1"
#define MY_COMPONENT_CLASSNAME "FIRESPOX SAPI"
#define MY_COMPONENT_CID \
	{0x8e2a9cb1, 0x72a9, 0x10fa, \
	  { 0x94, 0x3d, 0x8f, 0xb1, 0x57, 0xe3, 0xf9, 0xac }}

class FireSpox_SAPI : public IFireSpox
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_IFIRESPOX

	FireSpox_SAPI();
private:
	~FireSpox_SAPI();

};

#endif /* __FIRESPOX_SAPI_H__ */
