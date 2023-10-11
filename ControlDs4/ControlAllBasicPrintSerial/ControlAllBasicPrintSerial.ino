#include <Bluepad32.h>

#define motorEF 18 // Motor ESQUERDO anda para FRENTE
#define motorET 19 // Motor ESQUERDO anda para TRÁS
#define motorDF 13 // Motor DIREITO anda para FRENTE
#define motorDT 12 // Motor DIREITO anda para TRÁS
#define SensorEsquerdo 36 // Pino analógico para o sensor do lado ESQUERDO
#define SensorDireito 39 // Pino analógico para o sensor do lado DIREITO
#define velocidade 250 //Controle de velocidade do PWM
#define branco 100 //Definição da intensidade do branco
#define preto 250 //Definição da intensidade do preto
void tras(void) // Ambos motores são acionados reversamente, o robô anda para TRÁS
{
analogWrite(motorEF, velocidade);
analogWrite(motorET, 0);
analogWrite(motorDF, velocidade);
analogWrite(motorDT, 0);
}
void frente(void) // Ambos motores são acionados, o robô anda para FRENTE
{
analogWrite(motorEF, 0);
analogWrite(motorET, velocidade);
analogWrite(motorDF, 0);
analogWrite(motorDT, velocidade);
}
void esquerda(void) // Apenas o motor direito é acionado, virando para ESQUERDA
{
analogWrite(motorEF, 0);
analogWrite(motorET, 0);
analogWrite(motorDF, 0);
analogWrite(motorDT, velocidade);
}
void direita(void) // Apenas o motor esquerdo é acionado, virando para DIREITA
{
analogWrite(motorEF, 0);
analogWrite(motorET, velocidade);
analogWrite(motorDF, 0);
analogWrite(motorDT, 0);
}
void para(void) // Todos motores ficam parados
{
analogWrite(motorEF, 0);
analogWrite(motorET, 0);
analogWrite(motorDF, 0);
analogWrite(motorDT, 0);
}

GamepadPtr meuControle = nullptr; 
GamepadPtr meusGamepads[BP32_MAX_GAMEPADS];

void aoConectarGamepad(GamepadPtr gp) {
  bool encontrouSlotVazio = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (meusGamepads[i] == nullptr) {
      Serial.printf("CHAMADA DE RETORNO: Gamepad conectado, índice=%d\n", i);
      // Além disso, você pode obter certas propriedades do gamepad, como:
      // Modelo, VID, PID, BTAddr, flags, etc.
      GamepadProperties propriedades = gp->getProperties();
      Serial.printf("Modelo do gamepad: %s, VID=0x%04x, PID=0x%04x\n",
                    gp->getModelName().c_str(), propriedades.vendor_id,
                    propriedades.product_id);
      meusGamepads[i] = gp;
      encontrouSlotVazio = true;
      break;
    }
  }
  if (!encontrouSlotVazio) {
    Serial.println(
        "CHAMADA DE RETORNO: Gamepad conectado, mas não foi encontrado um slot vazio");
  }
}

void aoDesconectarGamepad(GamepadPtr gp) {
  bool encontrouGamepad = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (meusGamepads[i] == gp) {
      Serial.printf("CHAMADA DE RETORNO: Gamepad desconectado do índice=%d\n", i);
      meusGamepads[i] = nullptr;
      encontrouGamepad = true;
      break;
    }
  }

  if (!encontrouGamepad) {
    Serial.println(
        "CHAMADA DE RETORNO: Gamepad desconectado, mas não encontrado em meusGamepads");
  }
}

// Função de configuração do Arduino. Executada na CPU 1
void setup() {
  Serial.begin(115200);
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t *addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2],
                addr[3], addr[4], addr[5]);

  // Configura os callbacks do Bluepad32
  BP32.setup(&aoConectarGamepad, &aoDesconectarGamepad);

  // "forgetBluetoothKeys()" deve ser chamado quando o usuário realizar
  // uma "redefinição de fábrica" do dispositivo, ou algo semelhante.
  // Chamando "forgetBluetoothKeys" em setup() apenas como um exemplo.
  // Esquecer as chaves Bluetooth impede que os gamepads "pareados" se reconectem.
  // Mas também pode corrigir alguns problemas de conexão/reconexão.
  BP32.forgetBluetoothKeys();
}

// Função de loop do Arduino. Executada na CPU 1
void loop() {
  
int valorSenDir = analogRead(SensorDireito);
int valorSenEsq = analogRead(SensorEsquerdo);
if((valorSenEsq < branco ) && (valorSenDir < branco)) {
  frente();
}
else if((valorSenEsq > preto ) && (valorSenDir < branco)) {
  esquerda();
}
else if((valorSenEsq < branco) && (valorSenDir > preto)) {
  direita();
 }
  // Esta chamada obtém todas as informações do gamepad do módulo NINA (ESP32).
  // Basta chamar esta função em seu loop principal.
  // Os ponteiros dos gamepads (aqueles recebidos nas chamadas de retorno) são atualizados
  // automaticamente.
  BP32.update();

  // É seguro sempre fazer isso antes de usar a API do gamepad.
  // Isso garante que o gamepad seja válido e esteja conectado.
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    GamepadPtr meuGamepad = meusGamepads[i];

    if (meuGamepad && meuGamepad->isConnected()) {
      // Existem diferentes maneiras de verificar se um botão está pressionado.
      // Verificando cada botão individualmente:
      //  a(), b(), x(), y(), l1(), etc...
      if (meuGamepad->a()) {
        static int indiceCor = 0;
        // Alguns gamepads como DS4 e DualSense suportam a alteração da cor do LED.
        // É possível alterá-lo chamando:
        switch (indiceCor % 3) {
        case 0:
          analogWrite(motorET, velocidade);
          break;
        case 1:
          // Verde
          meuGamepad->setColorLED(0, 255, 255);
          break;
        case 2:
          // Azul
          meuGamepad->setColorLED(255, 0, 255);
          break;
        }
        indiceCor++;
      }

      if (meuGamepad->b()) {
        // Acende os 4 LEDs. Cada bit representa um LED.
        static int led = 0;
        led++;
        // Alguns gamepads como o DS3, DualSense, Nintendo Wii, Nintendo Switch
        // suportam a alteração dos "Player LEDs": aqueles 4 LEDs que normalmente
        // indicam o "assento do gamepad". É possível alterá-los chamando:
        meuGamepad->setPlayerLEDs(led & 0x0f);
      }

      if (meuGamepad->x()) {
        // Duração: 255 é aproximadamente 2 segundos
        // Força: intensidade
        // Alguns gamepads como DS3, DS4, DualSense, Switch, Xbox One S suportam
        // vibração (rumble).
        // É possível definir isso chamando:
        meuGamepad->setRumble(250,150);
      }

      // Outra maneira de verificar os botões é chamando buttons() ou
      // miscButtons() que retornam um bitmask.
      // Alguns gamepads também têm DPAD, eixos e outros.
      Serial.printf(
          "índice=%d, dpad: 0x%02x, botões: 0x%04x, eixo L: %4d, %4d, eixo R: "
          "%4d, %4d, freio: %4d, acelerador: %4d, misc: 0x%02x\n",
          i,                        // Índice do Gamepad
          meuGamepad->dpad(),        // DPAD
          meuGamepad->buttons(),     // bitmask dos botões pressionados
          meuGamepad->axisX(),       // (-511 - 512) eixo X esquerdo
          meuGamepad->axisY(),       // (-511 - 512) eixo Y esquerdo
          meuGamepad->axisRX(),      // (-511 - 512) eixo X direito
          meuGamepad->axisRY(),      // (-511 - 512) eixo Y direito
          meuGamepad->brake(),       // (0 - 1023): botão de freio
          meuGamepad->throttle(),    // (0 - 1023): botão do acelerador
          meuGamepad->miscButtons() // bitmask dos botões "misc" pressionados
      );

      // Você pode verificar os eixos e outras propriedades também. Veja Gamepad.h
      // Para todas as funções disponíveis.
    }
  }

  // O loop principal deve ter algum tipo de evento de "yield para tarefa de prioridade mais baixa".
  // Caso contrário, o watchdog será acionado.
  // Se o seu loop principal não tiver um, basta adicionar um simples `vTaskDelay(1)`.
  // Informações detalhadas aqui:
  // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

  // vTaskDelay(1);
  delay(150);
}