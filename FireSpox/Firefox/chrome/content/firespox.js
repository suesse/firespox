/* constants */
const IFireSpox = Components.interfaces.IFireSpox;
const nsISupports = Components.interfaces.nsISupports;
const CLASS_ID = Components.ID("{EF652B8D-D397-4E65-AA87-EA8D1DD2D77E}");
const CLASS_NAME = "FIRESPOX SAPI FIREFOX";
const CONTRACT_ID = "@firespox.mnsu.edu/FIRESPOX_SAPI_FIREFOX;1";

function FireSpox() {
  /* Nothing to do. */
}

FireSpox.prototype = {	
  QueryInterface: function(aIID)
  {
	if (!aIID.equals(IFireSpox) && !aIID.equals(nsISupports))
	  throw Componenets.results.NS_ERROR_NO_INTERFACE;
	return this;
  }
};

var FireSpoxFactory = {
  createInstance: function(aOuter, aIID)
  {
	if (aOuter != null)
	  throw Components.results.NS_ERROR_NO_AGGREGATION;
	return (new FireSpox()).QueryInterface(aIID);
  }
};

/* xpcom registration */
 var FireSpoxModule = {  
   registerSelf: function(aCompMgr, aFileSpec, aLocation, aType)  
   {  
	 aCompMgr = aCompMgr.  
		 QueryInterface(Components.interfaces.nsIComponentRegistrar);  
	 aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME,   
		 CONTRACT_ID, aFileSpec, aLocation, aType);  
   },  
   
   unregisterSelf: function(aCompMgr, aLocation, aType)  
   {  
	 aCompMgr = aCompMgr.  
		 QueryInterface(Components.interfaces.nsIComponentRegistrar);  
	 aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);          
   },  
	 
   getClassObject: function(aCompMgr, aCID, aIID)  
   {  
	 if (!aIID.equals(Components.interfaces.nsIFactory))  
	   throw Components.results.NS_ERROR_NOT_IMPLEMENTED;  
   
	 if (aCID.equals(CLASS_ID))  
	   return FireSpoxFactory;  
   
	 throw Components.results.NS_ERROR_NO_INTERFACE;  
   },  
   
   canUnload: function(aCompMgr) { return true; }  
 };
 
 function NSGetModule(aCompMgr, aFileSpec) { return FireSpoxModule; }