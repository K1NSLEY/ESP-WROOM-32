
#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Leiteiro";  // Enter SSID here
const char* password = "kins7215";  //Enter Password here

/* Put IP Address details */ 
IPAddress local_ip(192,168,1,99);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t LED1pin = 13;
bool LED1status = LOW;

uint8_t LED2pin = 12;
bool LED2status = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}



//PRIMEIRO 

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}
//PRIMEIRO



//SEGUNDO
void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}
//SEGUNDO

void handle_NotFound(){
  server.send(404, "text/plain", "ERRADO BURRÃO, VAI NO URL SERTO");
}

String SendHTML(uint8_t led1stat, uint8_t led2stat){
 
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 20px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 100px;background-color: #3498db;border: none;color: white;padding: 8px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #732727;}\n";
  ptr +=".button-on:active {background-color: ##368030;}\n";
  ptr +=".button-off {background-color: #05ff09;}\n";
  ptr +=".button-off:active {background-color: ##c92a1e;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="<meta charset=UTF-8>\n";
  ptr += "<meta http-equiv=\"refresh\" content=\"5\"> <!-- Adicione esta linha -->\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>🚦 Farol da Faixa Automatizada 🚦</h1>\n";
  ptr +="<h3>🚦 Feito por Kinsley Amadi, Luiz Gabriel, Maria luiza, João Gabriel e Gabriel Novais 🚦</h3>\n";
  
  if(led1stat)
  {ptr +="<p>Iluminação 1: LIGADA</p><a class=\"button button-off\" href=\"/led1off\">Apagar</a>\n";}
  else
  {ptr +="<p>Iluminação 1: DESLIGADA</p><a class=\"button button-on\" href=\"/led1on\">Acender</a>\n";}

  if(led2stat)
  {ptr +="<p>Iluminação 2: LIGADA</p><a class=\"button button-off\" href=\"/led2off\">Apagar</a>\n";}
  else
  {ptr +="<p>Iluminação 2: DESLIGADA</p><a class=\"button button-on\" href=\"/led2on\">Acender</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}