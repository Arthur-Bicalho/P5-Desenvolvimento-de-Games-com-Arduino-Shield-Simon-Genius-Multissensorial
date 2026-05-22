#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>


#define N 10; //C

/* PIN Def */ //A
const int trigPin = 9; //pino de disparo (saída)
const int echoPin = 8; //pino de eco (entrada)
const int botaoPin = 7; //botão

/* Global Variables*/
int sequence_num[N]; //C
int level=1; //C
const int R = 9, G = 6, B = 5; //B
const int BUZZER = 4; //B
const int trigPin = 9; echoPin = 8; //B

/* Struct */ //B
struct Level {int r, g, b, frequence;};

const Level LEVELS[] = {
  {255, 0, 0, 262}, //Nível 1 -- Vermelho/Dó
  {0, 255, 0, 294}, //Nível 2 -- Verde/Ré
  {0, 0, 255, 330}, //Nível 3 -- Azul/Mí
  {255, 150, 0, 349}, //Nível 4 -- Amarelo / Fá
  };

void set_color(int r, int g, int b){
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

/* Functions*/
void sequence(){ //C
  srand(analogRead(A0)) // REVISAR SE É REALMENTE A0!!!
  for (int i = 0; i < N; i++) {
    sequence_num[i] = (rand() % 4) + 1;
  }
}

int map_level(float distance){ //B
  if (distance > 0 && distance <= 10) return 1;
  else if (distance > 10 && distance <= 20) return 2;
  else if (distance > 20 && distance <= 30) return 3;
  else if (distance > 30 && distance <= 40) return 4;
  else return 0;
}

void show_level(int level, int duration){ //B
  if (level < 1 || level > 4){
    set_color(0, 0, 0);
    noTone(BUZZER);
    return;
    }

  Level n = LEVELS[level - 1];
  tone(BUZZER, n.frequence, duration);
  delay(duration);
  set_color(0, 0, 0);
  noTone(BUZZER);
}

float get_distance(){ //A
  digitalWrite(trigPin, LOW); //antes de gerar o pulso força o pino para LOW
  delayMicroseconds(2); //aguarda 2 microsegundos para estabilizar
  digitalWrite(trigPin, HIGH); //Inicia o pulso de disparo
  delayMicroseconds(10); //Mantém HIGH por 10 microsegundos
  digitalWrite(trigPin, LOW); //encerra o pulso
  float duration_us = pulseIn(echoPin, HIGH); //mde a duração do pulso HIGH no pino ECHO
  float distance_cm = duration_us * 0.034/2.0; //calculo da distância
  return distance_cm; //Retorna o resultado para quem chamou a função
}

boolean checkDistance(){ //C

}

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //TRIG é SAÍDA: o Arduino envia o pulso //A
  pinMode(echoPin, INPUT); //ECHO é ENTRADA: o arduino lê o retorno //A 
  pinMode(botaoPin, INPUT_PULLUP); //A

  pinMode(trigPint, OUTPUT); //B
  pinMode(echoPin, INPUT); //B 
  pinMode(R, OUTPUT); pinMode(g, OUTPUT); //B
  pinMode(B, OUTPUT); //B
  pinMode(BUZZER, OUTPUT); //B


  Timer1.initialize(1000000); //C
  MFS.initialize(&Timer1); //C
  sequence(); //C
  for (int i=0; i < N; i++){ //C
    MFS.write(sequence_num[i]); //C
    show_level(get_distance(),1000); //C
    delay(500); //C
  }
}

void loop(){
  //A
  if(digitalRead(botaoPin == LOW){ //verifica o estado atual do botão, se botão pressionado: chama a medição
    float distance = get_distance();
    Serial.print("Distância: "); //Exibe o resultado no monitor serial
    Serial.print(distance); //Imprime o número
    Serial.println(" cm"); //Imprime a unidade e quebra a linha
    delay(300); //Aguarda 300 microssegundos antes de aceitar nova leitura
  }

  float distance = get_distance(); //B
  int level = map_level(distance); //B
  if(level == 0) MFS.write("Fora do alcance"); //B
  else{ //B
    MFS.write("Nível: ");
    delay(200);}

  Serial.print("Dist: "); Serial.print(distance); //B 
  Serial.print(" cm -> Nivel: "); Serial.println(level); //B
  show_level(level, 400); //mosta cor + toca som por 400 ms / B
  delay(100); //B


  if (btn = BUTTON_PRESSED || Timer1 >= 5000000){ //C
    float distance=get_distance();
    checkDistance();
    if (checkDistance() == 1)MFS.write(distance); //C
  }

  /* if user gets right
   * level++
   * -game gets more difficult, adds another number to the sequence
   */
  /* if user gets wrong --> show "wrong!" & restart*/ 
}
