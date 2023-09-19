#include <ESP32Servo.h>
#include <WiFi.h>

const char* ssid = "Redmi Note 11";
const char* password = "gabrieldasilva";
WiFiServer server(80);
int c;
static const int servo = 18;

class DCMotor {
  int spd = 255, pin1, pin2;

public:
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Speed(int in1) {
    spd = in1;
  }

  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1, Motor2;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
int angulofechar = 180;
int anguloabrir = 10;
int i;

Servo myservo;

void setup() {
  Motor1.Pinout(22, 21);
  Motor2.Pinout(13, 14);
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(18, OUTPUT);
  myservo.attach(servo);
  myservo.write(180);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

int value = 0;

void loop() {
  Motor1.Speed(200);
  Motor2.Speed(200);
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0)
            client.println("HTTP/1.1 200 OK");

          client.println("Content-type:text/html");
          client.println();
          client.print("<html>");
          client.print("<head><meta content=\"width=device-width, initial-scale=1\"; charset=\"UTF-8\">");

          // Styling for the buttons
          client.print("<style> html { margin: 0px auto; text-align: center;}");
          client.print(".Vaga1 { background: #52FF00; border: 3px solid #000000; border-radius: 20px; width: 162px; height: 85px; left: 155px; top: 346px;}");
          client.print(".Vaga1off { background: red; border: 3px solid #000000; border-radius: 20px; width: 162px; height: 85px; left: 165px; top: 346px;}");
          // Define styles for other buttons here...
          client.print("</style>");

          client.print("<body>");
          // Create buttons and links here...
          client.print("</body>");

          client.print("</html>");
          client.println();
          break;
        } else {
          currentLine += c;
        }
      } else if (c != '\r') {
        currentLine += c;
      }

      // Handle HTTP requests here...
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
