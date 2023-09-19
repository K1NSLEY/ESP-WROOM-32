#include <DHT.h>
#include <WiFi.h>
#include <WebServer.h>
/* Put your SSID & Password */
const char* ssid = "ESP32-Manu";  // Enter SSID here
const char* password = "0123456789";  //Enter Password here
/* Put IP Address details */
IPAddress local_ip(192,168,9,1);
IPAddress gateway(192,168,9,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t LED1pin = 4;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

uint8_t LED3pin = 23;
bool LED3status = LOW;
uint8_t LED4pin = 22;
bool LED4status = LOW;
uint8_t LED5pin = 21;
bool LED5status = LOW;
uint8_t LED6pin = 19;
bool LED6status = LOW;
uint8_t LED7pin = 18;
bool LED7status = LOW;
#define DHTPIN 13 // Change this to the appropriate pin
#define DHTTYPE DHT11 // Change this to DHT22 if you're using a DHT22 sensor
float temperature;
float humidity;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);
  pinMode(LED5pin, OUTPUT);
  pinMode(LED6pin, OUTPUT);
  pinMode(LED7pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(500);
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);
  server.on("/led5on", handle_led5on);
  server.on("/led5off", handle_led5off);
  server.on("/led6on", handle_led6on);
  server.on("/led6off", handle_led6off);
  server.on("/led7on", handle_led7on);
  server.on("z", handle_led7off);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(ssid);
}
void loop() {
  server.handleClient();
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}

 if(LED3status)
  {digitalWrite(LED3pin, HIGH);}
  else
  {digitalWrite(LED3pin, LOW);}
   if(LED4status)
  {digitalWrite(LED4pin, HIGH);}
  else
  {digitalWrite(LED4pin, LOW);}
   if(LED5status)
  {digitalWrite(LED5pin, HIGH);}
  else
  {digitalWrite(LED5pin, LOW);}
   if(LED6status)
  {digitalWrite(LED6pin, HIGH);}
  else
  {digitalWrite(LED6pin, LOW);}
   if(LED7status)
  {digitalWrite(LED7pin, HIGH);}
  else
  {digitalWrite(LED7pin, LOW);}
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  LED4status = LOW;
  LED5status = LOW;
  LED6status = LOW;
  LED7status = LOW;
  float temperature= dht.readTemperature();
  float humidity= dht.readHumidity();
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF | GPIO23 Status: OFF | GPIO22 Status: OFF | GPIO21 Status: OFF | GPIO19 Status: OFF | GPIO18 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led3on() {
  LED3status = HIGH;
  Serial.println("GPIO23 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led3off() {
  LED3status = LOW;
  Serial.println("GPIO23 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false,LED4status,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led4on() {
  LED4status = HIGH;
  Serial.println("GPIO22 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,true,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led4off() {
  LED4status = LOW;
  Serial.println("GPIO22 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,false,LED5status,LED6status,LED7status,temperature,humidity)); 
}

void handle_led5on() {
  LED5status = HIGH;
  Serial.println("GPIO21 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,true,LED6status,LED7status,temperature,humidity)); 
}

void handle_led5off() {
  LED5status = LOW;
  Serial.println("GPIO21 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,false,LED6status,LED7status,temperature,humidity)); 
}

void handle_led6on() {
  LED6status = HIGH;
  Serial.println("GPIO19 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status,true,LED7status,temperature,humidity)); 
}

void handle_led6off() {
  LED6status = LOW;
  Serial.println("GPIO19 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status,false,LED7status,temperature,humidity)); 
}

void handle_led7on() {
  LED7status = HIGH;
  Serial.println("GPIO18 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status,LED6status,true,temperature,humidity)); 
}

void handle_led7off() {
  LED7status = LOW;
  Serial.println("GPIO18 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status,LED5status,LED6status,false,temperature,humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat,uint8_t led4stat,uint8_t led5stat,uint8_t led6stat,uint8_t led7stat,float temperature,float humidity){
 //uint8_t - é usado para variaveis que são lidadas apenas como 0 e 1. Float - variavel para numeros com virgula
  String ptr = "<!DOCTYPE html> <html>\n";// indicar que o código a seguir será do tipo HTML
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
   ptr += "<meta http-equiv=\"refresh\" content=\"2\">\n";//atualiza a pagina web de dois em dois segundos
  ptr +="<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr +="<title>ManuJURCK</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-pair { display: flex; flex-direction: row; justify-content: space-between; }\n";
  ptr += ".button-container { flex: 1; margin: 0 5px; }\n";

  /*
  estas duas funções acima servem para alinhar os botões lado a lado mehorando a interface.Dentro de seus parametros 
  é definido que serão objetos "flex" (flexiveis), isso fará eles se adptarem conforme o tamanho da tela, empurrando sempre
  os objetos para as laterais. Os objetos que queremos comtemplar com esta função devem ser adptados utilizando respectivas "DIVs"
  */
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="h2 {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +=".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr +=".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  ptr +=".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".humidity{font-weight: 300;font-size: 40px;color: #3498db;}\n";
  ptr +=".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr +=".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".temperature{font-weight: 300;font-size: 40px;color: #f39c12;}\n";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr +=".data{padding: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 ManuJURCK</h1>\n";
  ptr +="<h3>CONTROLE DE ACESSO</h3>\n";
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side temperature-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
  ptr +="width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
   ptr +="c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
   ptr +="c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
   ptr +="c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
   ptr +="c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side temperature-text\">Temperatura</div>\n";
   ptr +="<div class=\"side-by-side temperature\">";
  ptr +="<temperature>" + String(temperature) + " &deg;C</h2>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side humidity-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
   ptr +="c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side humidity-text\">Umidade</div>\n";
   ptr +="<div class=\"side-by-side humidity\">";
    ptr +="<humidity>" + String(humidity) + " %</h2>\n";
   ptr +="</div>\n";
 ptr += "<div class=\"button-pair\">\n";//para colocar botoes lado a lado
   if(led1stat)
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (1) <br> Status : ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (1) <br> Status : OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a></div>\n";}

  if(led2stat)
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (2) <br> Status : ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (2) <br> Status : OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a></div>\n";}
 ptr += "</div>\n";//fechando div para formar pares de botoes 
 ptr += "<div class=\"button-pair\">\n";//para colocar botoes lado a lado
 if(led3stat)
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (3) <br> Status : ON</p><a class=\"button button-off\" href=\"/led3off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Circuito lampadas (3) <br> Status : OFF</p><a class=\"button button-on\" href=\"/led3on\">ON</a></div>\n";}

  if(led4stat)
  {ptr +="<div class=\"button-container\"><p>Ventilador (1) <br> Status: ON</p><a class=\"button button-off\" href=\"/led4off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Ventilador (1) <br> Status: OFF</p><a class=\"button button-on\" href=\"/led4on\">ON</a></div>\n";}
  ptr += "</div>\n";//fechando div para formar pares de botoes 
  ptr += "<div class=\"button-pair\">\n";//para colocar botoes lado a lado
  if(led5stat)
  {ptr +="<div class=\"button-container\"><p>Ventilador (2) <br> Status: ON</p><a class=\"button button-off\" href=\"/led5off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Ventilador (2) <br> Status: OFF</p><a class=\"button button-on\" href=\"/led5on\">ON</a></div>\n";}
  if(led6stat)
  {ptr +="<div class=\"button-container\"><p>Cortinas (1) <br> Status: ON</p><a class=\"button button-off\" href=\"/led6off\">OFF</a></div>\n";}
  else
  {ptr +="<div class=\"button-container\"><p>Cortinas (1) <br> Status: OFF</p><a class=\"button button-on\" href=\"/led6on\">ON</a></div>\n";}
  ptr += "</div>\n";//fechando div para formar pares de botoes 
  if(led7stat)
  {ptr +="<p>Cortinas (2) <br> Status: ON</p><a class=\"button button-off\" href=\"/led7off\">OFF</a>\n";}
  else
  {ptr +="<p>Cortinas (2) <br> Status: OFF</p><a class=\"button button-on\" href=\"/led7on\">ON</a>\n";}
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
