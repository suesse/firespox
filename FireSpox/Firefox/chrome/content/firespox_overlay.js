/* Global Variables */
var cClasses = Components.classes;
var cInterfaces = Components.interfaces;
var consoleService = cClasses["@mozilla.org/consoleservice;1"].getService(cInterfaces.nsIConsoleService);
var application = cClasses["@mozilla.org/fuel/application;1"].getService(cInterfaces.fuelIApplication);
var windowWatcher = cClasses["@mozilla.org/embedcomp/window-watcher;1"].getService(cInterfaces.nsIWindowWatcher);
var eventListener = cClasses["@mozilla.org/eventlistenerservice;1"].getService(cInterfaces.nsIEventListenerService);
var threadMgr = cClasses["@mozilla.org/thread-manager;1"].getService(cInterfaces.nsIThreadManager);
var mainThread = cClasses["@mozilla.org/thread-manager;1"].getService().mainThread;
var spox = cClasses["@firespox.mnsu.edu/FIRESPOX_SAPI;1"].createInstance().QueryInterface(cInterfaces.IFireSpox);
var spoxThread = threadMgr.newThread(0);

function debug (aMessage) {
    FireSpoxExtension.log(aMessage);
}

/* TODO: Think about moving this into the dll */
var observer = new function () {
    var observerService;

    this.init = function () {
        //debug("~observer | initializing");
        observerService = cClasses["@mozilla.org/observer-service;1"].getService(cInterfaces.nsIObserverService);
        this.register();
        //debug("~observer | done initializing");
    };

    this.destroy = function () {
        observerService = null;
        this.unregister();
    }

    this.observe = function (subject, topic, data) {
        debug("~observer ? Data: " + data);
        //FireSpoxExtension.executeCommand(data);
    };

    this.register = function () {
        observerService.addObserver(this, "BrowserCallback", false);
        debug("~observer | registered");
    };

    this.unregister = function () {
        observerService.removeObserver(this, "BrowserCallback");
    };
};

/* Class Thread */
var Thread = function () { };

Thread.prototype = {
    run: function () {
        debug('~Thread.prototype | spox.start');
        spox.Start();
        debug('~Thread.prototype | spox.done');
    },

    QueryInterface: function (iid) {
        if (iid.equals(Components.interfaces.nsIRunnable) ||
        iid.equals(Components.interfaces.nsISupports)) {
            return this;
        }
        throw Components.results.NS_ERROR_NO_INTERFACE;
    }
};

//FireSpoxTask = {
//    run: function () {
//        debug("~FireSpoxTask | start");
//        FireSpoxExtension.spox.Start();
//    }
//}

/* Class: FireSpoxExtension */
var FireSpoxExtension = {


    prefs: Cc["@mozilla.org/preferences-service;1"].getService(Ci.nsIPrefService).getBranch("extensions.firespox."),

    isWinNT: function () {
        var os = cClasses["@mozilla.org/xre/app-info;1"].getService(Ci.nsIXULRuntime).OS;
        debug("~isWinNT ? '" + os + "'");
        return (os == "WINNT");
    }, /* end isWinNT */

    log: function (aMessage) {
        consoleService.logStringMessage(aMessage);
    },

    runThreadASync: function (func, state) {
        FireSpoxExtension.main.dispatch(new Thread(func, state), FireSpoxExtension.mainThread.DISPATCH_NORMAL);
    },

    onLoad: function () {
        debug('~onLoad | enter');
        if (FireSpoxExtension.isWinNT()) {
            /* TODO: check spox.HasSAPI() */
            observer.init();

            /* TODO: Check prefs to determine what to actually start. */
            spox.Load(true, true);
            debug('~onLoad | dispatching main thread');

            spoxThread.dispatch(new Thread(), cInterfaces.nsIThread.DISPATCH_NORMAL);
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
        spoxThread.shutdown();
        spox.Stop();
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

    /* TODO: auto scroll */
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
    },

    executeCommand: function (cmd) {
        switch (cmd) {
            case "browser_back":
                goDoCommand('Browser:Back');
                break;
            case "browser_forward":
                goDoCommand('Browser:Forward');
                break;
            case "browser_refresh":
                break;
            case "browser_stop":
                break;
            case "browser_home":
                goDoCommand('Browser:Home');
                break;
            case "browser_exit":
                goDoCommand('cmd_quit');
                break;
            case "browser_history":
                break;
            case "browser_bookmarks":
                break;
            case "browser_list":
                break;
            case "tts_pause":
                spox.TTS_Pause();
                break;
            case "tts_resume":
                spox.TTS_Resume();
                break;
        }
    }

};

window.addEventListener("load", function (e) { FireSpoxExtension.onLoad(); }, false);
window.addEventListener("unload", function (e) { FireSpoxExtension.onUnload(); }, false);