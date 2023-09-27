#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>

const char* ssid = "Leiteiro";
const char* password = "kins7215";

IPAddress local_ip(192, 168, 1, 99);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

int rele1 = 25;
int rele2 = 2;
int rele3 = 4;
int rele11 = 5;
int rele22 = 18;
int rele33 = 19;
const int motorPin1 = 14;
const int motorPin2 = 15;
int velocidade = 0;
int incremento = 10;
int direcao = 0;
int ativa;


uint8_t ledPin = 34;
bool ledStatus = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele11, OUTPUT);
  pinMode(rele22, OUTPUT);
  pinMode(rele33, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/toggle", HTTP_GET, handle_toggle);

  server.begin();
  Serial.println("Servidor HTTP iniciado");

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Redirecionar para a página inicial ("/") ao conectar ao Wi-Fi
  server.on("/wifi_connected", HTTP_GET, []() {
    server.sendHeader("Location", "/");
    server.send(301, "text/plain", "");
  });

  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/toggle", HTTP_GET, handle_toggle);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  semaforo();
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, HIGH);

  digitalWrite(rele11, LOW);
  digitalWrite(rele22, LOW);
  digitalWrite(rele33, HIGH);
  server.handleClient();
  digitalWrite(ledPin, ledStatus);
}

void handle_OnConnect() {
  String status = (ledStatus == HIGH) ? "AGUARDE" : "SOLICITE A PARADA";
  String html = "<html><body style='text-align:center;'>";
  html +="<meta charset=UTF-8>\n";
  html +="<h1>🚦 Farol da Faixa Automatizada 🚦</h1>\n";
  html +="<h3>🚦 Feito por Kinsley Amadi, Luiz Gabriel, Maria Luiza, João Gabriel e Gabriel Novais 🚦</h3>\n";
  html += "<p>Pressione o botão para pedir a faixa de pedestres :" + status + "</p>";
  html += "<a href='/toggle' style='";
  html += "display:inline-block; padding:10px 20px; font-size:20px; text-align:center; ";
  html += "text-decoration:none; background-color:#3498db; color:white; border-radius:5px;'>";
  html += "PEDIR FAIXA</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handle_toggle() {
  ledStatus = !ledStatus;
  mto();
    delay(100);
  handle_OnConnect();
}

void mto(){
  Serial.println(0);
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  delay(100);
  Serial.println(1);
  analogWrite(motorPin1, 1);
  analogWrite(motorPin2, 1);
  delay(100);
  Serial.println(2);
  analogWrite(motorPin1, 2);
  analogWrite(motorPin2, 2);
  delay(100);
  Serial.println(3);
  analogWrite(motorPin1, 3);
  analogWrite(motorPin2, 3);
  delay(100);
  Serial.println(4);
  analogWrite(motorPin1, 4);
  analogWrite(motorPin2, 4);
  delay(100);
  Serial.println(5);
  analogWrite(motorPin1, 5);
  analogWrite(motorPin2, 5);
  delay(100);
  Serial.println(7);
  analogWrite(motorPin1, 7);
  analogWrite(motorPin2, 7);
  delay(100);
  Serial.println(10);
  analogWrite(motorPin1, 10);
  analogWrite(motorPin2, 10);
  delay(100);
  Serial.println(15);
  analogWrite(motorPin1, 15);
  analogWrite(motorPin2, 15);
  delay(100);
  Serial.println(20);
  analogWrite(motorPin1, 20);
  analogWrite(motorPin2, 20);
  delay(100);
  Serial.println(25);
  analogWrite(motorPin1, 25);
  analogWrite(motorPin2, 25);
  delay(100);
  Serial.println(30);
  analogWrite(motorPin1, 30);
  analogWrite(motorPin2, 30);
  delay(100);
  Serial.println(40);
  analogWrite(motorPin1, 40);
  analogWrite(motorPin2, 40);
  delay(100);
  Serial.println(50);
  analogWrite(motorPin1, 50);
  analogWrite(motorPin2, 50);
  delay(100);
  Serial.println(60);
  analogWrite(motorPin1, 60);
  analogWrite(motorPin2, 60);
  delay(100);
  Serial.println(70);
  analogWrite(motorPin1, 70);
  analogWrite(motorPin2, 70);
  delay(100);
  Serial.println(80);
  analogWrite(motorPin1, 80);
  analogWrite(motorPin2, 80);
  delay(100);
  Serial.println(90);
  analogWrite(motorPin1, 90);
  analogWrite(motorPin2, 90);
  delay(100);
  Serial.println(100);
  analogWrite(motorPin1, 100);
  analogWrite(motorPin2, 100);
  delay(100);
  Serial.println(120);
  analogWrite(motorPin1, 120);
  analogWrite(motorPin2, 120);
  delay(100);
  Serial.println(130);
  analogWrite(motorPin1, 130);
  analogWrite(motorPin2, 130);
  delay(100);
  Serial.println(140);
  analogWrite(motorPin1, 140);
  analogWrite(motorPin2, 140);
  delay(100);
  Serial.println(150);
  analogWrite(motorPin1, 150);
  analogWrite(motorPin2, 150);
  delay(100);
  Serial.println(160);
  analogWrite(motorPin1, 160);
  analogWrite(motorPin2, 160);
  delay(100);
  Serial.println(200);
  analogWrite(motorPin1, 200);
  analogWrite(motorPin2, 200);
  delay(100);
  Serial.println(230);
  analogWrite(motorPin1, 230);
  analogWrite(motorPin2, 230);
  delay(100);
  Serial.println(235);
  analogWrite(motorPin1, 235);
  analogWrite(motorPin2, 235);
  delay(100);
  Serial.println(237);
  analogWrite(motorPin1, 237);
  analogWrite(motorPin2, 237);
  delay(100);
  Serial.println(240);
  analogWrite(motorPin1, 240);
  analogWrite(motorPin2, 240);
  delay(100);
  Serial.println(250);
  analogWrite(motorPin1, 250);
  analogWrite(motorPin2, 250);
  delay(100);
  Serial.println(255);
  analogWrite(motorPin1, 255);
  analogWrite(motorPin2, 255);
  delay(6000);
  Serial.println(240);
  analogWrite(motorPin1, 240);
  analogWrite(motorPin2, 240);
  delay(100);
  Serial.println(245);
  analogWrite(motorPin1, 245);
  analogWrite(motorPin2, 245);
  delay(100);
  Serial.println(230);
  analogWrite(motorPin1, 230);
  analogWrite(motorPin2, 230);
  delay(100);
  Serial.println(220);
  analogWrite(motorPin1, 220);
  analogWrite(motorPin2, 220);
  delay(100);
  Serial.println(215);
  analogWrite(motorPin1, 215);
  analogWrite(motorPin2, 215);
  delay(100);
  Serial.println(200);
  analogWrite(motorPin1, 200);
  analogWrite(motorPin2, 200);
  delay(100);
  Serial.println(190);
  analogWrite(motorPin1, 190);
  analogWrite(motorPin2, 190);
  delay(100);
  Serial.println(180);
  analogWrite(motorPin1, 180);
  analogWrite(motorPin2, 180);
  delay(100);
  Serial.println(170);
  analogWrite(motorPin1, 170);
  analogWrite(motorPin2, 170);
  delay(100);
  Serial.println(160);
  analogWrite(motorPin1, 160);
  analogWrite(motorPin2, 160);
  delay(100);
  Serial.println(150);
  analogWrite(motorPin1, 150);
  analogWrite(motorPin2, 150);
  delay(100);
  Serial.println(140);
  analogWrite(motorPin1, 140);
  analogWrite(motorPin2, 140);
  delay(100);
  Serial.println(130);
  analogWrite(motorPin1, 130);
  analogWrite(motorPin2, 130);
  delay(100);
  Serial.println(120);
  analogWrite(motorPin1, 120);
  analogWrite(motorPin2, 120);
  delay(100);
  Serial.println(110);
  analogWrite(motorPin1, 110);
  analogWrite(motorPin2, 110);
  delay(100);
  Serial.println(100);
  analogWrite(motorPin1, 100);
  analogWrite(motorPin2, 100);
  delay(100);
  Serial.println(90);
  analogWrite(motorPin1, 90);
  analogWrite(motorPin2, 90);
  delay(100);
  Serial.println(80);
  analogWrite(motorPin1, 80);
  analogWrite(motorPin2, 80);
  delay(100);
  Serial.println(70);
  analogWrite(motorPin1, 70);
  analogWrite(motorPin2, 70);
  delay(100);
  Serial.println(60);
  analogWrite(motorPin1, 60);
  analogWrite(motorPin2, 60);
  delay(100);
  Serial.println(50);
  analogWrite(motorPin1, 50);
  analogWrite(motorPin2, 50);
  delay(100);
  Serial.println(45);
  analogWrite(motorPin1, 45);
  analogWrite(motorPin2, 45);
  delay(100);
  Serial.println(40);
  analogWrite(motorPin1, 40);
  analogWrite(motorPin2, 40);
  delay(100);
  Serial.println(35);
  analogWrite(motorPin1, 35);
  analogWrite(motorPin2, 35);
  delay(100);
  Serial.println(30);
  analogWrite(motorPin1, 30);
  analogWrite(motorPin2, 30);
  delay(100);
  Serial.println(25);
  analogWrite(motorPin1, 25);
  analogWrite(motorPin2, 25);
  delay(100);
  Serial.println(20);
  analogWrite(motorPin1, 20);
  analogWrite(motorPin2, 20);
  delay(100);
  Serial.println(15);
  analogWrite(motorPin1, 15);
  analogWrite(motorPin2, 15);
  delay(100);
  Serial.println(10);
  analogWrite(motorPin1, 10);
  analogWrite(motorPin2, 10);
  delay(100);
  Serial.println(5);
  analogWrite(motorPin1, 7);
  analogWrite(motorPin2, 7);
  delay(100);
  Serial.println(5);
  analogWrite(motorPin1, 5);
  analogWrite(motorPin2, 5);
  delay(100);
  Serial.println(3);
  analogWrite(motorPin1, 3);
  analogWrite(motorPin2, 3);
  delay(100);
  Serial.println(2);
  analogWrite(motorPin1, 2);
  analogWrite(motorPin2, 2);
  delay(100);
  Serial.println(1);
  analogWrite(motorPin1, 1);
  analogWrite(motorPin2, 1                                                                                                         );
  delay(100);
}

void semaforo(){
  // Set verde 1°
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, LOW);
  
  digitalWrite(rele11, LOW);
  digitalWrite(rele22, LOW);
  digitalWrite(rele33, HIGH);
  delay(1000);

  // Set verde 2°
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, LOW);

  digitalWrite(rele11, LOW);
  digitalWrite(rele22, LOW);
  digitalWrite(rele33, HIGH);
  delay(1000);

  // Set Mid State 3°
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, HIGH);

  digitalWrite(rele11, HIGH);
  digitalWrite(rele22, LOW);
  digitalWrite(rele33, LOW);
  delay(1000);

  // Set verde 4°
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, HIGH);

  digitalWrite(rele11, LOW);
  digitalWrite(rele22, HIGH);
  digitalWrite(rele33, LOW);
  delay(1000);

  // Set verde 5°
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
  digitalWrite(rele3, HIGH);

  digitalWrite(rele11, LOW);
  digitalWrite(rele22, LOW);
  digitalWrite(rele33, HIGH);
  delay(1000);}
