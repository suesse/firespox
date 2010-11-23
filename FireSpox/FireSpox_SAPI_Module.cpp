/* Required to export to Mozilla */
/* To build use:  */
#include "nsIGenericFactory.h"
#include "FireSpox_SAPI.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(FireSpox_SAPI)

static nsModuleComponentInfo components[] =
{
    {
       MY_COMPONENT_CLASSNAME, 
       MY_COMPONENT_CID,
       MY_COMPONENT_CONTRACTID,
       FireSpox_SAPIConstructor,
    }
};

NS_IMPL_NSGETMODULE("FireSpox_SAPI_Module", components) 