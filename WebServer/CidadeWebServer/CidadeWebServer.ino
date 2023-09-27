#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>

/* Defina o SSID e a senha da sua rede Wi-Fi */
const char* ssid = "Leiteiro";  // Insira o nome da sua rede Wi-Fi
const char* password = "kins7215";  // Insira a senha da sua rede Wi-Fi

/* Configuração do IP da rede Wi-Fi */
IPAddress local_ip(192, 168, 1, 99);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

const int motorPin1 = 14; // Conecte a um dos pinos de controle da ponte H
const int motorPin2 = 15; // Conecte ao outro pino de controle da ponte H
int velocidade = 0;
int incremento = 10;
int direcao = 0; // 0 para parar, 1 para aumentar a velocidade, -1 para diminuir


uint8_t ledPin = 34; // Pino do LED
bool ledStatus = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Configura a rede Wi-Fi em modo de ponto de acesso (AP)
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Configura os tratadores de rota para o botão de controle
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/toggle", HTTP_GET, handle_toggle);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  if (ledStatus = true) {
      direcao = 1; //Comece a aumentar a velocidad
  }
  velocidade += incremento * direcao;
  velocidade = constrain(velocidade, 0, 260);
  analogWrite(motorPin1, velocidade); // Use um dos pinos de controle da ponte H
  digitalWrite(motorPin2, LOW);       // Desligue o outro pino
  Serial.println(velocidade);
  delay(100);
  if (velocidade == 260) {
    direcao = -1;
  }

  // Se a velocidade for 0, pare
  if (velocidade == 0) {
    direcao = 0;
  }


  server.handleClient();
  digitalWrite(ledPin, ledStatus); // Define o estado do LED com base em ledStatus
}

void handle_OnConnect() {
  String status = (ledStatus == HIGH) ? "AGUARDE" : "SOLICITE A PARADA";
  String html = "<html><body style='text-align:center;'>";
  html +="<meta charset=UTF-8>\n";
  html +="<h1>🚦 Farol da Faixa Automatizada 🚦</h1>\n";
  html +="<h3>🚦 Feito por Kinsley Amadi, Luiz Gabriel, Maria luiza, João Gabriel e Gabriel Novais 🚦</h3>\n";
  html += "<p>Pressione o botão para pedir a faixa de pedestres :" + status + "</p>";
  html += "<a href='/toggle' style='";
  html += "display:inline-block; padding:10px 20px; font-size:20px; text-align:center; ";
  html += "text-decoration:none; background-color:#3498db; color:white; border-radius:5px;'>";
  html += "PEDIR FAIXA</a>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handle_toggle() {
  ledStatus = !ledStatus; // Inverte o estado do LED
  handle_OnConnect(); // Redireciona de volta para a página inicial após a ação
}
