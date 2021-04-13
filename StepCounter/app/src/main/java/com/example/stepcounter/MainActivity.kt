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
    private var isTimer = false
    private var stepCount = 0
    private var magAccumulator = 0f
    private var magnitude = 0f
    private var previousMagnitude = 0f

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
    }

    //El delay controla el intervalo en el que los eventos del sensor se envían a la aplicación a través del método de devolución de llamada
    //decidí usar el delay normal ya que no tengo una especificación o razón para generar un retrazo en el intervalo
    override fun onResume() {
        super.onResume()
        val welcome = "Bienvenido"
        val beggin = "¿Comenzar jornada?"
        //Decidí instanciar el sensor y registrarlo dentro del botón de Ok del primer cartel para controlar el inicio en el que empiezo a recibir eventos
        val welcomeAlert = AlertDialog.Builder(this)
                .setTitle("$welcome")
                .setMessage("$beggin")
                .setPositiveButton("Ok"){_, _ ->
                    isTimer = false
                    walking = true
                    val stepSensor = sensorManager?.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
                    stepSensor?.let { step ->
                        sensorManager?.registerListener(this, step, SensorManager.SENSOR_DELAY_UI)
                        //Este toast no es necesario, pero me gusta dejarlo para que se vea cuándo se registra
                        Toast.makeText(this, "Se encontraron y registraron los sensores", Toast.LENGTH_SHORT).show()
                    }
                    setTimer()
                }
                .create()
        welcomeAlert.show()
    }

    override fun onPause(){
        super.onPause()
        walking = false
        sensorManager?.unregisterListener(this)
        //Idem el toast de registro
        Toast.makeText(this, "Se pausaron los sensores", Toast.LENGTH_SHORT).show()
    }

    override fun onSensorChanged(event: SensorEvent?) {
        event?.let {
            if (walking) {
                val x = event!!.values[0]
                val y = event!!.values[1]
                val z = event!!.values[2]

                // Calcula la velocidad del accelerometro
                magnitude = sqrt(x * x + y * y + z * z)
                checkMagnitude()
                magAccumulator = magnitude - previousMagnitude
                previousMagnitude = magnitude
                //Lo que hice acá es calcular que si una persona camina 5km/h
                //Caminaría 1,38889 m/s, pero al tomar la velocidad de la magnitud del acelerómetro, lo que hice fue ir corriendo la coma
                //dentro del valor (ya que al calcularlo con 1,3 al moverme contaba demasiados pasos)
                //No estoy segura de que esté correcto
                if (magnitude > 13.8) {
                    stepCount++
                }
                val textview_data: TextView = findViewById(R.id.textview_data)
                textview_data.text = "$stepCount"
            }
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}

    private fun checkMagnitude() {
        if (previousMagnitude == magnitude) {
            isTimer = true
            setTimer()
        }
    }

    private fun setTimer() {
        val alertTitle = "Psst!"
        val alertMessage = "El tiempo de descanzo ha finalizado"
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
                isTimer = false
            }
        }
        if (isTimer){
            timer.start()
        }
    }
}