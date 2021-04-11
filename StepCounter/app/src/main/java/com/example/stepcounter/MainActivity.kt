package com.example.stepcounter

import android.app.Activity
import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.CountDownTimer
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import java.util.*
import kotlin.math.sqrt
import kotlin.system.measureTimeMillis

class MainActivity : AppCompatActivity(), SensorEventListener {
    private var sensorManager : SensorManager? = null
    private var walking = false
    private var stepCount = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
    }

    //El delay controla el intervalo en el que los eventos del sensor se envían a la aplicación a través del método de devolución de llamada
    //decidí usar el delay normal ya que no tengo una especificación o razón para generar un retrazo en el intervalo
    override fun onResume() {
        super.onResume()
        walking = true
        val stepSensor = sensorManager?.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        stepSensor?.let { step ->
            sensorManager?.registerListener(this, step, SensorManager.SENSOR_DELAY_UI)
            Toast.makeText(this, "Se encontraron y registraron los sensores", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onPause(){
        super.onPause()
        walking = false
        sensorManager?.unregisterListener(this)
        Toast.makeText(this, "Se pausaron los sensores", Toast.LENGTH_SHORT).show()
    }

    override fun onSensorChanged(event: SensorEvent?) {
        Toast.makeText(this, "Entro al sensor Changed", Toast.LENGTH_SHORT).show()
        event?.let {
        val notWalkingMessage = "not walking"
        if (walking){

            val x = event!!.values[0]
            val y = event!!.values[1]
            val z = event!!.values[2]

            // Calculate the angular speed of the sample
            var Magnitude = sqrt(x * x + y * y + z * z)

            Toast.makeText(this, "Magnitude: $Magnitude", Toast.LENGTH_SHORT).show()

            if (Magnitude > 13){
                stepCount++
            }
            val textview_data: TextView = findViewById(R.id.textview_data)
            textview_data.text = "${stepCount}"
            //Acá tengo que ver la forma de que si los steps no avanzan, dispare el timer
            /*if (){
                setTimer()
            }*/
        } else {
            setTimer()
            Toast.makeText(this, "$notWalkingMessage", Toast.LENGTH_SHORT).show()
        }
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}

    private fun setTimer() {
        var alertTitle = "Psst!"
        var alertMessage = "El tiempo de descanzo ha finalizado"
        val restMessage = "Se ha reestablecido el tiempo de descanso"
        val alertDialog = AlertDialog.Builder(this)
                .setTitle("$alertTitle")
                .setMessage("$alertMessage")
                .setPositiveButton("Ok"){_, _ ->
                    Toast.makeText(this, "$restMessage", Toast.LENGTH_SHORT).show()
                }
                .create()

        val timer = object: CountDownTimer(20000, 1000) {
            override fun onTick(millisUntilFinished: Long) {}
            override fun onFinish() {
                alertDialog.show()
            }
        }
        if (!walking && !alertDialog.isShowing){
            timer.start()
            Toast.makeText(this, "Entro en el if del timer", Toast.LENGTH_SHORT).show()
        }
        Toast.makeText(this, "No entró en el if del timer", Toast.LENGTH_SHORT).show()
    }
}