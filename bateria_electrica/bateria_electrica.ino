#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//Definimos los piezos que vamos a usar como sensores
const int sensorTom1 = A0;
const int sensorTom2 = A1;
const int sensorCrash = A2;
const int sensorRide = A3;
const int sensorBombo = A4;
const int sensorHitHat = A5;
const int sensorCaja = A6;
const int sensorTomBase = A7;

//Configuramos la sensibilidad de cada piezo
int sensTom1 = 350;
int sensTom2 = 350;
int sensCrash = 350;
int sensRide = 350;
int sensBombo = 350;
int sensHitHat = 350;
int sensCaja = 350;
int sensTomBase = 350;

int volPiezo = 10;  // Con este valor decidimos cuando el sonido se considera un knock o no

int sensorReadingTom1 = 0; 
int sensorReadingTom2 = 0; 
int sensorReadingCrash = 0; 
int sensorReadingRide = 0; 
int sensorReadingBombo = 0; 
int sensorReadingHitHat = 0; 
int sensorReadingCaja = 0; 
int sensorReadingTomBase = 0; 

void setup() {
  // put your setup code here, to run once:

  //DFPLAYER
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
   Serial.println(F("DFPlayer Mini online."));

}

void loop() {
  // put your main code here, to run repeatedly:

   if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }

//Leo los piezo
 sensorReadingTom1 = analogRead(sensorTom1);
 sensorReadingTom2 = analogRead(sensorTom2);
 sensorReadingCrash = analogRead(sensorCrash);
 sensorReadingRide = analogRead(sensorRide);
 sensorReadingBombo = analogRead(sensorBombo);
 sensorReadingHitHat = analogRead(sensorHitHat);
 sensorReadingCaja = analogRead(sensorCaja);
 sensorReadingTomBase = analogRead(sensorTomBase);

//////////////// Tom1 /////////////////

  if (sensorReadingTom1>= sensTom1){
    Serial.println("Tom 1");
    Serial.println(sensorReadingTom1);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingTom1/30;
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 14);

  }

////////////// Tom 2 /////////////////

  if (sensorReadingTom2 >= sensTom2) {
    Serial.println("Tom 2");
    Serial.println(sensorReadingTom2);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingTom2/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 20);
  }

////////////// Crash /////////////

  if (sensorReadingCrash >= sensCrash) {
    Serial.println("Crash");
    Serial.println(sensorReadingCrash);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingCrash/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 6);
  }

////////////// Ride /////////////

  if (sensorReadingRide >= sensRide) {
    Serial.println("Ride");
    Serial.println(sensorReadingRide);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingRide/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 22);
  }

////////////// Bombo /////////////

  if (sensorReadingBombo >= sensBombo) {
    Serial.println("Bombo");
    Serial.println(sensorReadingBombo);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingBombo/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 9);
  }

////////////// HitHat /////////////

  if (sensorReadingHitHat >= sensHitHat) {
    Serial.println("HitHat");
    Serial.println(sensorReadingHitHat);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingHitHat/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 5);
  }
////////////// Caja /////////////

  if (sensorReadingCaja >= sensCaja) {
    Serial.println("Caja");
    Serial.println(sensorReadingCaja);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingCaja/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 4);
  }
  
////////////// TomBase /////////////

  if (sensorReadingTomBase >= sensTomBase) {
    Serial.println("Tom Base");
    Serial.println(sensorReadingTomBase);
    Serial.println("Volumen");
    delay(3);
    volPiezo = sensorReadingTomBase/30; 
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 3);
  }
}
/* Aca contemplamos y notificamos las detecciones y estados del modulo DFPlayer
 *  En caso de que no encuentre la pista, haya algún error u otros
 *  No es algo crucial para la funcionalidad de la batería, pero nos sirve
 *  para ver logs y cómo puede estar fincionando la batería.
 */
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("TimeOut!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
