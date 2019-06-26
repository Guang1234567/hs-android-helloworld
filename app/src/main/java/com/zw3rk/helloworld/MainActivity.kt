package com.zw3rk.helloworld

import android.Manifest
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.TextView
import android.widget.Toast
import com.tbruyelle.rxpermissions2.RxPermissions
import io.reactivex.Scheduler
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var rxPermissions: RxPermissions = RxPermissions(this)

        rxPermissions
                .requestEachCombined(Manifest.permission.WRITE_EXTERNAL_STORAGE)
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe({ permission ->
                    // will emit 2 Permission objects
                    if (permission.granted) {
                        // `permission.name` is granted !
                        //Toast.makeText(this@MainActivity, "已成功授予所有权限!", Toast.LENGTH_SHORT).show()
                        doSthAfterAllPermissionGranted()
                    } else if (permission.shouldShowRequestPermissionRationale) {
                        // Denied permission without ask never again
                    } else {
                        // Denied permission with ask never again
                        // Need to go to the settings
                    }
                })
    }

    private fun doSthAfterAllPermissionGranted() {
        // Example of a call to a native method
        val tv = findViewById(R.id.sample_text) as TextView

        Handler(Looper.getMainLooper()).postDelayed(
                {
                    tv.text = stringFromJNI()
                    Log.e("lhg", "--------- begin --------isElfFileFromJNI")
                    Log.w("lhg", "${isElfFileFromJNI("/sdcard/jl.txt")}")
                    Log.w("lhg1", "${matchesGlobFromJNI("foo.c", "f??.c")}")
                    Log.w("lhg2", "${matchesGlobFromJNI("test.c", "t[ea]s*")}")
                    Log.w("lhg3", "${matchesGlobFromJNI("taste.txt", "t[ea]s*")}")
                    Log.w("lhg4", "${namesMatchingJNI("/sdcard/*.txt").joinToString()}}")
                    Log.e("lhg", "---------- end --------isElfFileFromJNI")

                    doSthAfterAllPermissionGranted()
                }
                , 2000)
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun isElfFileFromJNI(path: String): Boolean

    external fun matchesGlobFromJNI(name: String, glob: String): Boolean

    external fun namesMatchingJNI(path: String): Array<String>
}
