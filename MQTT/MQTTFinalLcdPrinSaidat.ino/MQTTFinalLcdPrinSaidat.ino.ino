#define motorEF 11 // Motor ESQUERDO anda para FRENTE
#define motorET 10 // Motor ESQUERDO anda para TRÁS
#define motorDF 3 // Motor DIREITO anda para FRENTE
#define motorDT 5 // Motor DIREITO anda para TRÁS
#define SensorEsquerdo A0 // Pino analógico para o sensor do lado ESQUERDO
#define SensorDireito A1 // Pino analógico para o sensor do lado DIREITO

#define velocidade 250 //Controle de velocidade do PWM
#define branco 100 //Definição da intensidade do branco
#define preto 250 //Definição da intensidade do preto

void setup(){
}

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
void loop(){
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
}