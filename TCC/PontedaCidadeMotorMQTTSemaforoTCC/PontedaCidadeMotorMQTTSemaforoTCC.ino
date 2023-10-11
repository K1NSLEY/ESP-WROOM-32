#include <DHT11.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

DHT11 dht11(2);

#define portao           02
#define conexaowifi      04
#define conexaomqtt      05

#define WLAN_SSID       "ETEC PC"             // Your SSID
#define WLAN_PASS       "012345789"        // Your password

/********* Adafruit.io Setup ***********/
#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME  "tecnologowillian"
#define AIO_KEY       "aio_MSYm31rTlCSDVjGt4KG0AVxTc92z"

//WIFI CLIENT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe entrada = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/portao");
Adafruit_MQTT_Publish temperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish humidade = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidade");

int estadodeconexao;

void setup() {
  Serial.begin(115200);
  pinMode(portao, OUTPUT);
  pinMode(conexaowifi, OUTPUT);
  pinMode(conexaomqtt, OUTPUT);
  digitalWrite(conexaowifi,0);
  digitalWrite(conexaomqtt,0);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(conexaowifi,0);
    Serial.print(".");
  }
  Serial.println();
  digitalWrite(conexaowifi,1);
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  mqtt.subscribe(&entrada);
  mqtt.publish(temperatura);
  mqtt.publish(humidade);
  }
void MQTT_connect();

void loop() {
int temperature = dht11.readTemperature();
int humidity = dht11.readHumidity();

  Serial.print("temp:");
  Serial.print(temperature);
  Serial.print("  humi:");
  Serial.println(humidity);

  MQTT_connect();
        if (estadodeconexao == LOW){ 
            Serial.println("Tentado de Conectar ao MQTT");
            Serial.println("Tentando novente, Aguarde!");
            MQTT_connect();
       }
        Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &entrada) {
      Serial.print(F("Got: "));
      Serial.println((char *)entrada.lastread);
      int entrada_State = atoi((char *)entrada.lastread);
      digitalWrite(portao, entrada_State);
      delay(1000);
        if (entrada_State == 0){
          digitalWrite(portao,0);
        }
    
    }}
    Adafruit_MQTT_Publish *publish;

    client.publish("/feeds/temperatura", temp);
    client.publish("/feeds/humidade", humi);
    
    }

//---------------------------------------------------------------------
void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 10000000000;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    digitalWrite(conexaomqtt,0);
    estadodeconexao = LOW;
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
    Serial.println("MQTT Connected!");
    digitalWrite(conexaomqtt,1);
    estadodeconexao = HIGH;
  
}
  //---------------------------------------------------------------------