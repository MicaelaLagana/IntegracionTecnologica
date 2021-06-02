#include <SD.h>  
#include <SPI.h>
#include <TMRpcm.h>  


#define pinSD 53    // pin CS  MEGA 53                     
TMRpcm tmrpcm;              
                                                                                                                                                                                                         
const int sensorTom1 = A0;
const int sensorTom2 = A1;
const int sensorCrash = A2;
const int sensorRide = A3;
const int sensorBombo = A4;
const int sensorHithat = A5;
const int sensorCaja = A6;
const int sensorTomBase = A7;

                                                                              //  volumen--
/*
Acá vamos a ver la sensibilidad o el threshold del piezo, cuanto más bajo lo ponemos, 
es más sensible, así que vamos a tener que ser cudadosos con el tema de pegarle a un piezo 
y que el que esté al lado tome el golpe, esto lo tenemos que probar cuando esté armado e ir probando. 
Lo dejo en 100 como standar porque era el thresh que tenía el knock ejemplo con le que probamos los piezos y parecía funcar
*/

int senseTom1 = 100;
int senseTom1 = 100;
int senseCrash = 100;
int senseRide = 100;
int senseBombo = 100;
int senseHitHat = 100;
int senseCaja = 100;
int senseTomBase = 100;

int tiempoMaxReproduccion = 30; // lo que va a durar como maximo cada sonido.
//Lo seteé en 30 segundos porque vamos a tener sonidos cortos (bombos, toms y caja) y para los platillos, dudo que necesitemos para el proyecto que un platillo dure más de 30s ahora)

int tom1 = 100;
int tom2 = 100;
int crash = 100;
int ride = 100;
int bombo = 100;
int hithat = 100;
int caja = 100;
int tomBase = 100;

// define el sonido por defecto en los pads al iniciar el programa, se pueden cambiar para guardar un set.
/*Con esto vamos a seleccionar los sonidos*/
int selectTom1 = 1;
int selectTom2 = 1;
int selectCrash = 1;
int selectRide = 1;
int selectBombo = 1;
int selectHithat = 1;
int selectCaja = 1;
int selectTomBase = 1;

/*Acá vamos a manejar el volumen de cada pad, 
me parece medio al vicio porque no creo que lleguemos a manejar sensibilidad, 
pero por las dudas hasta que probemos bien todo, le mandemos con esto*/
int volumenTom1 = 1;
int volumenTom2 = 1;
int volumenCrash = 1;
int volumenRide = 1;
int volumenBombo = 1;
int volumenHithat = 1;
int volumenCaja = 1;
int volumenTomBase = 1;

/*Esto define el pin 3 para el botón, que creo que es para reproducir el audio*/
boolean selection = 3;

/*Estuve viendo que el bool de volumen lo usa para ver el tema de la sensibilidad del golpe. Yo esta linea la sacaría, es medio un chino y estamos justos de tiempo. */
/*define el pin, pero es para la sensibildad, no sé si vamos a usarlo*/
boolean volumen = 4 ;
int volSensor = 3;

void setup(){
  pinMode (seleccion, INPUT );
   pinMode (volumen, INPUT );
  tmrpcm.speakerPin = 9; // define el pin en el que está conectado el altavoz (audio output) (Creo que aca podemos ver lo de la conección del modulo)
  Serial.begin(9600);    

  if (!SD.begin(pinSD)) {  // verifica la coneccion de la tarjeta sd:
    Serial.println("No es posible reconocer tarjeta SD");  
    return;  
  }
}

void loop(){  
  /* COMENTAR CON // LA LINEA DE UN PAD SI NO ESTA CONECTADO, PARA QUE NO SE DISPARE SOLO! */
  
   //tmrpcm.setVolume(4); esto es opcional, si queremos manejar el volumen
    tom1 = analogRead(sensorTom1);
    tom2 = analogRead(sensorTom2);
    crash = analogRead(sensorCrash);
    ride = analogRead(sensorRide);
    bombo = analogRead(sensorBombo);
    hithat = analogRead(sensorHithat);
    caja = analogRead(sensorCaja);
    tomBase = analogRead(sensorTomBase);

   
//tom1////////////////////////
 if (tom1 > senseTom1){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenTom1);   
    if (digitalRead (selection) == HIGH){
      if (tom1 > senseTom1) {
        selectTom1 ++;
        if (selectTom1 == 7){
          selectTom1 = 1;
        }
      }
    }
    if (selectTom1 == 1){
      tmrpcm.play("Tom1.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (tom1 > senseTom1) {
        volumenTom1 ++;
        if (volumenTom1 == 5){
          volumenTom1 = 0;
        }  
      } 
    }
 }
//tom2////////////////////////
 if (tom2 > senseTom2){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenTom2);   
    if (digitalRead (selection) == HIGH){
      if (tom2 > senseTom2) {
        selectTom2 ++;
        if (selectTom2 == 7){
          selectTom2 = 1;
        }
      }
    }
    if (selectTom2 == 1){
      tmrpcm.play("Tom2.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (tom2 > senseTom2) {
        volumenTom2 ++;
        if (volumenTom2 == 5){
          volumenTom2 = 0;
        }  
      } 
    }
 }
//crash////////////////////////
 if (crash > senseCrash){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenCrash);   
    if (digitalRead (selection) == HIGH){
      if (crash > senseCrash) {
        selectCrash ++;
        if (selectCrash == 7){
          selectCrash = 1;
        }
      }
    }
    if (selectCrash == 1){
      tmrpcm.play("Crash.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (crash > senseCrash) {
        volumenCrash ++;
        if (volumenCrash == 5){
          volumenCrash = 0;
        }  
      } 
    }
 }
 //Ride////////////////////////
 if (ride > senseRide){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenRide);   
    if (digitalRead (selection) == HIGH){
      if (ride > senseRide) {
        selectRide ++;
        if (selectRide == 7){
          selectRide = 1;
        }
      }
    }
    if (selectRide == 1){
      tmrpcm.play("Ride.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (ride > senseRide) {
        volumenRide ++;
        if (volumenRide == 5){
          volumenRide = 0;
        }  
      } 
    }
 }

 //Bombo////////////////////////
 if (bombo > senseBombo){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenBombo);   
    if (digitalRead (selection) == HIGH){
      if (bombo > senseBombo) {
        selectBombo ++;
        if (selectBombo == 7){
          selectBombo = 1;
        }
      }
    }
    if (selectBombo == 1){
      tmrpcm.play("Bombo.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (bombo > senseBombo) {
        volumenBombo ++;
        if (volumenBombo == 5){
          volumenBombo = 0;
        }  
      } 
    }
 }

 //Hithat////////////////////////

 //Acá tenemos que ver como hacemos que para al precionar el switch, reproduzca el sonido del hithat cerrado (Este pad tendría 2 sonidos)
 if (hithat > senseHithat){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenHithat);   
    if (digitalRead (selection) == HIGH){
      if (hithat > senseHithat) {
        selectHithat ++;
        if (selectHithat == 7){
          selectHithat = 1;
        }
      }
    }
    if (selectHithat == 1){
      tmrpcm.play("Hithat.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (hithat > senseHithat) {
        volumenHithat ++;
        if (volumenHithat == 5){
          volumenHithat = 0;
        }  
      } 
    }
 }
 //caja////////////////////////
 if (caja > senseCaja){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenCaja);   
    if (digitalRead (selection) == HIGH){
      if (caja > senseCaja) {
        selectCaja ++;
        if (selectCaja == 7){
          selectCaja = 1;
        }
      }
    }
    if (selectCaja == 1){
      tmrpcm.play("Caja.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (caja > senseCaja) {
        volumenCaja ++;
        if (volumenCaja == 5){
          volumenCaja = 0;
        }  
      } 
    }
 }
 //tomBase////////////////////////
 if (tomBase > senseTomBase){
 //Aca podemos meter unos pares de logs para chequear que esté tomando todos los pads
    tmrpcm.setVolume(volumenTomBase);   
    if (digitalRead (selection) == HIGH){
      if (tomBase > senseTomBase) {
        selectTomBase ++;
        if (selectTomBase == 7){
          selectTomBase = 1;
        }
      }
    }
    if (selectTomBase == 1){
      tmrpcm.play("TomBase.wav");  // nombre de archivo a reproducir guardado en la sd.
      delay(tiempo);
    }
      
    if (digitalRead (volumen) == HIGH){
      if (tomBase > senseTomBase) {
        volumenTomBase ++;
        if (volumenTomBase == 5){
          volumenTomBase = 0;
        }  
      } 
    }
 }

}
  
  
