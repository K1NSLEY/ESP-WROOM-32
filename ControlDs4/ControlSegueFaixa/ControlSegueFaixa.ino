#include <Bluepad32.h>
static int RemoteLink = 0;
int SegueD;
int SegueE;
int motorDirFrente= 25;
int motorDirTraz= 26;

int motorEsqFrente= 27;
int motorEsqTraz= 14;




#define SensorEsquerdo 32 // Pino analógico para o sensor do lado ESQUERDO
#define SensorDireito 33 // Pino analógico para o sensor do lado DIREITO
#define branco 80 //Definição da intensidade do branco
#define preto 200 //Definição da intensidade do preto

GamepadPtr myGamepads[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedGamepad(GamepadPtr gp) {
  bool encontrouSlotVazio = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myGamepads[i] == nullptr) {
      Serial.printf("CHAMADA DE RETORNO: Gamepad conectado, índice=%d\n", i);
      // Além disso, você pode obter certas propriedades do gamepad, como:
      // Modelo, VID, PID, BTAddr, flags, etc.
      GamepadProperties propriedades = gp->getProperties();
      Serial.printf("Modelo do Gamepad: %s, VID=0x%04x, PID=0x%04x\n",
                    gp->getModelName().c_str(), propriedades.vendor_id,
                    propriedades.product_id);
      myGamepads[i] = gp;
      encontrouSlotVazio = true;
      break;
    }
  }
  if (!encontrouSlotVazio) {
    Serial.println(
        "CHAMADA DE RETORNO: Gamepad conectado, mas não encontrou slot vazio");
  }
}

void onDisconnectedGamepad(GamepadPtr gp) {
  bool foundGamepad = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myGamepads[i] == gp) {
      Serial.printf("CALLBACK: Gamepad is disconnected from index=%d\n", i);
      myGamepads[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }

  if (!foundGamepad) {
    Serial.println(
        "CALLBACK: Gamepad disconnected, but not found in myGamepads");
  }
}

// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(115200);
  const uint8_t *addr = BP32.localBdAddress();
  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
  BP32.forgetBluetoothKeys();
}

void loop() {
  int valorSenDir = analogRead(SensorDireito);
  int valorSenEsq = analogRead(SensorEsquerdo);
  if((valorSenEsq < branco ) && (valorSenDir < branco)){
  frente();
  }
  else if((valorSenEsq > preto ) && (valorSenDir < branco)){
  esquerda();
  }
  else if((valorSenEsq < branco) && (valorSenDir > preto)){
  direita();
  }
  else if((valorSenEsq > branco) && (valorSenDir > preto)){
  tras();
  }

  BP32.update();
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    GamepadPtr myGamepad = myGamepads[i];
    if (myGamepad && myGamepad->isConnected()) {







      if (myGamepad->a()) {
        RemoteLink = (RemoteLink + 1) % 2; // Limita o valor a 0 ou 1

        switch (RemoteLink) {
          case 0:
            myGamepad->setColorLED(255, 255, 255);
            Serial.println(RemoteLink);
            SegueFaixa();
            break;
          case 1:
            // Green
            myGamepad->setColorLED(255, 0, 255);
            Serial.println(RemoteLink);
            break;
            delay(5000);
        }
      }


      if (myGamepad->b()) {
        myGamepad->disconnect();
      }
    }
  }
  delay(150);
}

void SegueFaixa(){
}

void tras(void) // Ambos motores são acionados reversamente, o robô anda para TRÁS
{
}
void frente(void) // Ambos motores são acionados, o robô anda para FRENTE
{
}
void esquerda(void) // Apenas o motor direito é acionado, virando para ESQUERDA
{
}
void direita(void) // Apenas o motor esquerdo é acionado, virando para DIREITA
{
}
void para(void) // Todos motores ficam parados
{
}