#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <ArduinoJson.h>
#include <TelegramCertificate.h>
#include <UniversalTelegramBot.h>

/* https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
 *  Esa es la librería que estamos usando para incluir el bot
 https://github.com/bblanchon/ArduinoJson
 Esta para arduino JSON*/

/*Con estas variables los que hacemos es guardar el nombre
 * y la contraseña de nuestra red wifi para que el node 
 * pueda conectarse
 */
const char* SSID = "TuRed";
const char* password = "TuContraseña";

/*Y con estas lo que hacemos es poner el token y el id de  nuestro bot
El id es mas que nada para que no cualquiera use nuestro bot
el token lo obtuvimos de botfather y el id lo obtuvimos de IDboy*/
#define BOTtoken "1894485690:AAGf_g8XQXcz-NIRdbsw18Ohpl9jkGCnQzs" 
#define CHAT_ID "919787618" 
/*Nes te recomiendo aca que te crees una cuenta en telegram
 * y que consigas un id escribiendole al bot IDBot (y lo cargues en esta variable
 * al momento de subirla al node, porque sino va a ignorar todos los mensajes
 * este id es de mi cuenta)
 */

// acá creamos un nuevo cliente wifi
WiFiClientSecure client;

/*Y acá creamos/instanciamos el nuevo bot con 
nuestro token y nuestro cliente de wifi*/
UniversalTelegramBot bot(BOTtoken, client);

/*Con estas variables revisamos los mensajes de telegram,
 * seteamos un delay con 5000ms y va a chequear el bot cuando
 * termine el periodo.
 */
int botRequestDelay = 5000;
unsigned long lastTimeBotRan;

//Con esta funcion mandamos mensajes a nuestro bot
bool sendMessage(String chat_id, String text, String parse_mode = "")

//Creamos ua funcion para accionar cuando recibimos un mensaje
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  /*Dentro del for, obtenemos el id de cada mensaje
    Y si es diferente al que seteamos arriba, ignoramos el mensaje
    y esperamos uno nuevo, porque significa que alguien más
    tiene nuestro bot, entonces ignoramos el mensaje.
    Si tiene nuestro id, guardamos el mensaje en una variable de texto
    a la que llamamos mensaje*/
  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    String message = bot.messages[i].text;
    Serial.println(message);
    String from_name = bot.messages[i].from_name; //Aca tenemos el nombre de quién lo mandó
    //Si el mensaje es /start
    if (text == "/start") {
      /*en esta variable wellcome le damos la bienvenida al usuario
       * que nos escribio y le indicamos los comandos validos
       * para manejar el led del node, esto es más que nada para probar que
       * funque el bot
       */
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }
    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }
    if (text == "/state") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "LED is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
    }
    /*Con los 3 ifs anteriores vemos dependiendo del mensaje que recibimos
     * Led_on y Led_off manda un mensaje con como se seteó el led
     * y enciende y apaga el led respectivamente
     * state devuelve un mensaje con el estado de cada led
     * esto es únicamente código de ejemplo, podemos usarlo para probarlo y
     * cambiarlo luego por el estado de la puerta
     * agregar un contador para ver si hubo alguna entrada no autorizada
     * o algo por el estilo
     */
  }


}



void setup() {
  //Acá conectamos el wifi con la cuenta de red y la contraseña de la misma
  //que definimos más arriba
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");

}

void loop() {
  //Y aca adentro revisamos un mensaje nuevo cada segundo
  //Si la cantidad de milisegundos es mayor a la ultima vez
  //que se ejecuto el bot + el delay del request, le sumamos
  // uno al numero de mensajes que obtenemos del bot
  //y cada vez que ese valor tenga algo, vamos a loggear un 
  // got response, vamos a hacer el handle de ese mensaje en el metodo de arriba
  //y vamos a sumar numero a ese numero de mensajes
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  /*
   * deberíamos acá buscar la forma de que cada vez que haya un ingreso no autorizado y se 
   * el sensor capte que se abrió la puerta, mande un mensaje
   */
}
