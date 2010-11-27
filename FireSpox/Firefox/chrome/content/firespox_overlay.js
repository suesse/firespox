/* Global Variables */
var cClasses = Components.classes;
var cInterfaces = Components.interfaces;
var consoleService = cClasses["@mozilla.org/consoleservice;1"].getService(cInterfaces.nsIConsoleService);
var application = cClasses["@mozilla.org/fuel/application;1"].getService(cInterfaces.fuelIApplication);
var windowWatcher = cClasses["@mozilla.org/embedcomp/window-watcher;1"].getService(cInterfaces.nsIWindowWatcher);
var eventListener = cClasses["@mozilla.org/eventlistenerservice;1"].getService(cInterfaces.nsIEventListenerService);

var command;

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

/* TODO: Think about moving this into the dll */
var observer = new function () {
    var observerService;

    this.init = function () {
        debug("~observer | initializing");
        observerService = cClasses["@mozilla.org/observer-service;1"].getService(cInterfaces.nsIObserverService);
        this.register();
        debug("~observer | done initializing");
    };

    this.destroy = function () {
        observerService = null;
        this.unregister();
    }

    this.observe = function (subject, topic, data) {
        debug("~observer ? Data: " + data);
    };

    this.register = function () {
        observerService.addObserver(this, "BrowserCallback", false);
        debug("~observer | registered");
    };

    this.unregister = function () {
        observerService.removeObserver(this, "BrowserCallback");
    };
}; 

/* Class: FireSpoxExtension */
var FireSpoxExtension = {

    spox: cClasses["@firespox.mnsu.edu/FIRESPOX_SAPI;1"].createInstance().QueryInterface(cInterfaces.IFireSpox),
    prefs: Cc["@mozilla.org/preferences-service;1"].getService(Ci.nsIPrefService).getBranch("extensions.firespox."),

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
        debug("HasSAPI: " + FireSpoxExtension.spox.HasSAPI());
        if (FireSpoxExtension.isWinNT()) {
            /* TODO: check FireSpoxExtension.spox.HasSAPI() */
            debug('~onLoad | commencing loading...');
            observer.init();

            /* TODO: Check prefs to determine what to actually start. */
            FireSpoxExtension.spox.TTS_Load();
            FireSpoxExtension.spox.ASR_Load();
            FireSpoxExtension.spox.ASR_Listen(command);

            debug('~onLoad | loaded');
        }
        else {
            debug('~onLoad | platform not supported, exiting...');
            return;
        }
        debug('~onLoad | exit');
    }, /* end onLoad */

    onUnload: function () {
        debug('~onUnload | enter');
        /* TODO: Save Prefs */
        FireSpoxExtension.spox.TTS_Unload();
        FireSpoxExtension.spox.ASR_Unload();
        debug('~onUnload | exit');
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
window.addEventListener("unload", function (e) { FireSpoxExtension.onUnload(); }, false);