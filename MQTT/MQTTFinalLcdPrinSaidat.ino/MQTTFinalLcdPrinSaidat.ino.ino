#include <Wire.h> // Library used to manage communication between devices using the I2C protocol
#include <LiquidCrystal_I2C.h> // Library for controlling an I2C LCD display
#include "WiFi.h" // Library for configuring and connecting to Wi-Fi
#include <PubSubClient.h> // Library for using the MQTT protocol
LiquidCrystal_I2C lcd(0x27, 16, 2); // Initializing an object for the LCD display with address 0x27, 16 columns, and 2 rows.
int ledPin = 15;
// Wi-Fi connection parameters
const char* ssid = "SSID"; // Wi-Fi network name
const char* password = "PASSWORD"; // Wi-Fi network password

// MQTT Broker
const char *mqtt_broker = "mqtt-dashboard.com"; // MQTT broker host
const char *topic = "YOURTOPIC"; // Topic to subscribe to and publish
const char *mqtt_username = ""; // MQTT username
const char *mqtt_password = ""; // MQTT password
const int mqtt_port = 1883; // MQTT port

// Variables
bool mqttStatus = 0;

// Objects
WiFiClient espClient;
PubSubClient client(espClient);

// Function prototypes
bool connectMQTT();
void callback(char *topic, byte * payload, unsigned int length);

void setup(void)
{
  pinMode(ledPin, OUTPUT);
  lcd.init(); // Initializes communication with the connected display
  lcd.clear(); // Clears the display screen
  lcd.backlight(); // Turns on the backlight of the display
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Waiting for connection
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Send IP over UART
  Serial.println(WiFi.localIP());

  mqttStatus = connectMQTT();

}

void loop() {
  static long long pooling = 0;
  client.loop();
}

bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  do {
    String client_id = "BOBSIEN-";
    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connection successful:");
      Serial.printf("Client %s connected to the broker\n", client_id.c_str());
    } else {
      Serial.print("Failed to connect: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Attempt: ");
      Serial.println(tentativa);
      delay(2000);
    }
    tentativa++;
  } while (!client.connected() && tentativa < 5);

  if (tentativa < 5) {
    // Publish and subscribe
    client.publish(topic, "Conectado ao Broker");
    client.subscribe(topic);
    return 1;
  } else {
    Serial.println("Not connected");
    return 0;
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  int value = atoi((char*)payload);
  Serial.println(topic);
  for (unsigned int i = 0; i < length; i++) {
    lcd.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  lcd.setCursor(0, 1);
  if (value == 10) {
    digitalWrite(ledPin, HIGH); // Acende o LED
    lcd.backlight();
  } else if (value == 9) {
    digitalWrite(ledPin, LOW); // Apaga o LED
    lcd.noBacklight();
  }
  delay(5000);
  lcd.clear();
}
