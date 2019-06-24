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

external fun initHS()

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
                        Toast.makeText(this@MainActivity, "已成功授予所有权限!", Toast.LENGTH_SHORT).show()
                        doSthAfterAllPermissionGranted()
                    } else if (permission.shouldShowRequestPermissionRationale) {
                        // Denied permission without ask never again
                    } else {
                        // Denied permission with ask never again
                        // Need to go to the settings
                    }
                })

        doSthAfterAllPermissionGranted()
    }

    private fun doSthAfterAllPermissionGranted() {
        // Example of a call to a native method
        val tv = findViewById(R.id.sample_text) as TextView
        tv.text = stringFromJNI()

        Handler(Looper.getMainLooper()).postDelayed(
                {
                    Log.e("lhg", "-----------------1111")
                    Log.w("lhg", "${isElfFileFromJNI("/sdcard/jl.txt")}")
                    Log.e("lhg", "-----------------2222")
                }
                , 2000)
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun isElfFileFromJNI(path: String): Boolean

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
            initHS()
        }
    }
}
