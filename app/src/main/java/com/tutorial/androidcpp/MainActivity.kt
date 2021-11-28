package com.tutorial.androidcpp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.tutorial.androidcpp.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'androidcpp' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        private val instance_ : MainActivity = MainActivity()

        init {
            System.loadLibrary("androidcpp")
        }

        @JvmStatic
        fun getInstance(): MainActivity{
            return instance_;
        }
    }

    private fun onFunctionFirst( intVal: Int, stringVal: String, stringVal2: String, stringVal3: String ){
        TODO()
    }

    private fun onFunctionSecond(  stringVal: String){
        TODO()
    }

    private fun onFunctionThird(  stringVal: String){
        TODO()
    }

    private fun onFunctionFourth( intVal: Int, stringVal: String ){
        TODO()
    }

    private fun onFunctionFifth(){
        TODO()
    }


}