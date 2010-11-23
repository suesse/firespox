/* Global Variables */
var cClasses = Components.classes;
var cInterfaces = Components.interfaces;
var consoleService = cClasses["@mozilla.org/consoleservice;1"].getService(cInterfaces.nsIConsoleService);
var application = cClasses["@mozilla.org/fuel/application;1"].getService(cInterfaces.fuelIApplication);
var windowWatcher = cClasses["@mozilla.org/embedcomp/window-watcher;1"].getService(cInterfaces.nsIWindowWatcher);

function debug (aMessage) {
    FireSpoxExtension.log(aMessage);
}

/* Class: SpoxThread */
var SpoxThread = function (aFunc, aState) {
    this.aFunc = aFunc;
    this.aState = aState;
};

SpoxThread.prototype = {
    run: function () {
        this.aFunc(this.aState);
    },

    QueryInterface: function (aIID) {
        if (!aIID.equals(IFireSpox) && !aIID.equals(nsISupports))
            throw Componenets.results.NS_ERROR_NO_INTERFACE;
        return this;
    }
};

/* Class: FireSpoxExtension */
var FireSpoxExtension = {

    spox: cClasses["@firespox.mnsu.edu/FIRESPOX_SAPI;1"].createInstance().QueryInterface(cInterfaces.IFireSpox),

    isWinNT: function () {
        var os = cClasses["@mozilla.org/xre/app-info;1"].getService(Ci.nsIXULRuntime).OS;
        debug("~isWinNT ? '" + os + "'");
        return (os == "WINNT");
    }, /* end isWinNT */

    log: function (aMessage) {
        consoleService.logStringMessage(aMessage);
    },

    onLoad: function () {
        debug('~onLoad | enter');
        if (FireSpoxExtension.isWinNT()) {

        }
        debug('~onLoad | exit');
    }, /* end onLoad */

    onUnload: function () {
        //debug('~onUnload | enter');
        /* TODO: Save Prefs */
        spox.TTS_Unload();
        spox.ASR_Unload();
        //debug('~onUnload | exit');
    }, /* end onUnload */

    openTTSOptions: function () {
        debug('~openTTSOptions | enter');
        var left = (screen.width / 2) - (150);
        var top = (screen.height / 2) - (75);
        window.open("chrome://firespox/content/tts_options.xul", "Text to Speech Options", "chrome,dialog,width=300,height=150,top=" + top + ",left=" + left);
        debug('~openTTSOptions | exit');
    },

    openASROptions: function () {
        debug('~openASROptions | enter');
        var left = (screen.width / 2) - (150);
        var top = (screen.height / 2) - (75);
        window.open("chrome://firespox/content/asr_options.xul", "Speech Recognition Options", "chrome,dialog,width=300,height=150,top=" + top + ",left=" + left);
        debug('~openASROptions | exit');
    },

    /* TODO: auto scroll? */
    lineScroll: function (direction) {
        if (direction == Ci.nsIDirection.down)
            goDoCommand('cmd_scrollLineDown');
        else 
            goDoCommand('cmd_scrollLineUp');
    },

    pageScroll: function (direction) {
        if (direction == Ci.nsIDirection.down)
            goDoCommand('cmd_scrollPageDown');
        else 
            goDoCommand('cmd_scrollPageUp');
    }

};

window.addEventListener("load", function (e) { FireSpoxExtension.onLoad(); }, false);
window.addEventListener("unload", function (e) { FirespoxExtension.onUnload(); }, false);