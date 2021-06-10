#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); 
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//Defino los piezo que voy a usar como sensores
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

int volPiezo = 0; 
int volBase = 35;

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
    delay(5);
    volPiezo = sensorReadingTom1/volBase;
    myDFPlayer.volume(volPiezo);
    Serial.println(volPiezo);
    myDFPlayer.playFolder(1, 1);
    // Lo updateamos y le seteamos un volumen
    //myDFPlayer.volume(30);

  }

////////////// Tom 2 /////////////////

  if (sensorReadingTom2 >= sensTom2) {
    Serial.println("Tom 2");
    Serial.println(sensorReadingTom2);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingTom2/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 2);
  }

////////////// Crash /////////////

  if (sensorReadingCrash >= sensCrash) {
    Serial.println("Crash");
    Serial.println(sensorReadingCrash);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingCrash/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 3);
  }

////////////// Ride /////////////

  if (sensorReadingRide >= sensRide) {
    Serial.println("Ride");
    Serial.println(sensorReadingRide);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingRide/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 4);
  }

////////////// Bombo /////////////

  if (sensorReadingBombo >= sensBombo) {
    Serial.println("Bombo");
    Serial.println(sensorReadingBombo);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingBombo/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 5);
  }

////////////// HitHat /////////////

  if (sensorReadingHitHat >= sensHitHat) {
    Serial.println("HitHat");
    Serial.println(sensorReadingHitHat);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingHitHat/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 6);
  }
////////////// Caja /////////////

  if (sensorReadingCaja >= sensCaja) {
    Serial.println("Caja");
    Serial.println(sensorReadingCaja);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingCaja/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 7);
  }
  
////////////// TomBase /////////////

  if (sensorReadingTomBase >= sensTomBase) {
    Serial.println("Tom Base");
    Serial.println(sensorReadingTomBase);
    Serial.println("Volumen");
    delay(5);
    volPiezo = sensorReadingTomBase/volBase; 
    Serial.println(volPiezo);
    myDFPlayer.volume(volPiezo);
    myDFPlayer.playFolder(1, 8);
  }
}
/* Aca contemplamos y notificamos las detecciones y estados del modulo DFPlayer
 *  En caso de que no encuentre la pista, haya algún error u otros
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
