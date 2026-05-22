//configuração do sensor ultrassônico
/* Alimentação: 5V DC; Alcance: 2cm - 400cm; Precisão: aproximadamente 0.3 cm;
 * Frequência: 40 kHz; Pinos: VCC, TRIG, ECHO, GND; Resistor: 10 kΩ + 20 kΩ; */
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>


//Definição dos pinos
const int trigPin = 9; //pino de disparo (saída)
const int echoPin = 8; //pino de eco (entrada)
const int botaoPin = 7; //botão

//Declaração das variáveis globais
float duracao_micros; //duração do pulso ECHO em microssegundos
float distancia_cm; //Distância calculada em centímetros

float medirDistancia(){
  digitalWrite(trigPin, LOW); //antes de gerar o pulso força o pino para LOW
  delayMicroseconds(2); //aguarda 2 microsegundos para estabilizar
  digitalWrite(trigPin, HIGH); //Inicia o pulso de disparo
  delayMicroseconds(10); //Mantém HIGH por 10 microsegundos
  digitalWrite(trigPin, LOW); //encerra o pulso
  float duracao_us = pulseIn(echoPin, HIGH); //mde a duração do pulso HIGH no pino ECHO
  float distancia_cm = duracao_us * 0.034/2.0; //calculo da distância
  return distancia_cm; //Retorna o resultado para quem chamou a função
}

//setup() - executab ao ligar
void setup(){
  Serial.begin(9600); //Inicia a comunicação serial
  pinMode(trigPin, OUTPUT); //TRIG é SAÍDA: o Arduino envia o pulso
  pinMode(echoPin, INPUT); //ECHO é ENTRADA: o arduino lê o retorno
  pinMode(botaoPin, INPUT_PULLUP);
}
 
//Loop
void loop(){
  if(digitalRead(botaoPin == LOW){ //verifica o estado atual do botão, se botão pressionado: chama a medição
    float distancia = medirDistancia();
    Serial.print("Distância: "); //Exibe o resultado no monitor serial
    Serial.print(distancia); //Imprime o número
    Serial.println(" cm"); //Imprime a unidade e quebra a linha
    delay(300); //Aguarda 300 microssegundos antes de aceitar nova leitura
  }
}


