int carroVerde = 8;
int carroAmarelo = 7;
int carroVermelho = 6;
int pedestreVerde = 9;
int pedestreVermelho = 10;
int botao = 5;

void setup() {
  pinMode(carroVerde, OUTPUT);
  pinMode(carroAmarelo, OUTPUT);
  pinMode(carroVermelho, OUTPUT);
  pinMode(pedestreVerde, OUTPUT);
  pinMode(pedestreVermelho, OUTPUT);
  pinMode(botao, INPUT);

  digitalWrite(carroVerde, LOW);
  digitalWrite(carroAmarelo, LOW);
  digitalWrite(carroVermelho, LOW);
  digitalWrite(pedestreVerde, LOW);
  digitalWrite(pedestreVermelho, LOW);

}

int state = !digitalRead(botao);

void loop() 
{
  while (state == !(digitalRead(botao)))
{
  digitalWrite(carroVerde, HIGH);
  digitalWrite(pedestreVermelho, HIGH);
}

  digitalWrite(carroVerde, LOW);
  digitalWrite(carroAmarelo, LOW);
  delay(3000);
  digitalWrite(carroAmarelo, LOW);
  digitalWrite(carroVermelho, HIGH);
  delay(1000);
  digitalWrite(pedestreVermelho, LOW);
  digitalWrite(pedestreVerde, HIGH);
  delay(5000);
  digitalWrite(pedestreVerde, LOW);

  for(int i=0 ; i<5 ; i++)
{
    digitalWrite(pedestreVermelho, !(digitalRead(pedestreVermelho)));
    delay(500);
}

delay(1000);
digitalWrite(pedestreVerde, LOW);
digitalWrite(carroVermelho, LOW);

}