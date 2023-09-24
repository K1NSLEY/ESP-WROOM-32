#include <Arduino.h>

// Defina os pinos da ponte H
const int motorPin1 = 14; // Conecte a um dos pinos de controle da ponte H
const int motorPin2 = 15; // Conecte ao outro pino de controle da ponte H

// Velocidade inicial e incremento de velocidade
int velocidade = 0;
int incremento = 10;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  // Aumente a velocidade gradativamente
  if (velocidade < 255) {
    velocidade += incremento;
  }

  // Controle do motor usando a ponte H
  analogWrite(motorPin1, velocidade); // Use um dos pinos de controle da ponte H
  digitalWrite(motorPin2, LOW);       // Desligue o outro pino
  Serial.print(velocidade);

  // Aguarde um curto período de tempo para a aceleração ser visível
  delay(100);

  // Você pode adicionar mais lógica aqui para controlar a desaceleração ou parar o motor

  // Aguarde um pouco antes de aumentar a velocidade novamente
  delay(1000);
}
