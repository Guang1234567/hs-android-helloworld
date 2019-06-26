package com.zw3rk.helloworld

import android.app.Application
import android.content.Context

class HsApp : Application() {

    companion object {

        //https://stackoverflow.com/questions/49554430/how-to-declare-native-cpp-method-for-which-declared-in-kotlin-companion-object?answertab=votes#tab-top
        @JvmStatic
        external fun hsInit(argv: Array<String>)

        @JvmStatic
        external fun hsExit()

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
            // init RTS
            //https://downloads.haskell.org/ghc/latest/docs/html/users_guide/ffi-chap.html#using-the-ffi-with-ghc
            hsInit(arrayOf("+RTS", "-A32m"))
        }
    }

    override fun attachBaseContext(base: Context?) {
        super.attachBaseContext(base)
    }


    override fun onTerminate() {
        super.onTerminate()
        exitApp()
    }

    fun exitApp() {
        // dispose RTS
        hsExit()
    }
}