#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>

#define TRIG_PIN   12
#define ECHO_PIN   13

#define LED_R       9
#define LED_G      10
#define LED_B      11

#define BUZZER_PIN  3
#define BTN_PIN     2

#define N 10; //C

/*=========================Global Variables=========================*/
int sequence_num[N]; //C
int level=1; //C

/*============================Struct ============================*/ //B
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

/*============================Functions============================*/
void sequence(){ //C
  srand(analogRead(A0)) // REVISAR SE É REALMENTE A0!!!
  for (int i = 0; i < N; i++) {
    sequence_num[i] = (rand() % 4) + 1;
  }
}


float get_distance(){ //A
  digitalWrite(TRIG_PIN, LOW); //antes de gerar o pulso força o pino para LOW
  delayMicroseconds(2); //aguarda 2 microsegundos para estabilizar
  digitalWrite(TRIG_PIN, HIGH); //Inicia o pulso de disparo
  delayMicroseconds(10); //Mantém HIGH por 10 microsegundos
  digitalWrite(TRIG_PIN, LOW); //encerra o pulso
  float duration_us = pulseIn(ECHO_PIN, HIGH); //mde a duração do pulso HIGH no pino ECHO
  float distance_cm = duration_us * 0.034/2.0; //calculo da distância
  return distance_cm; //Retorna o resultado para quem chamou a função
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
    noTone(BUZZER_PIN);
    return;
    }

  Level n = LEVELS[level - 1];
  tone(BUZZER_PIN, n.frequence, duration);
  delay(duration);
  set_color(0, 0, 0);
  noTone(BUZZER_PIN);
}

boolean checkDistance(){ //C

}


/*============================Start============================*/
void setup(){
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT); //TRIG é SAÍDA: o Arduino envia o pulso //A
  pinMode(ECHO_PIN, INPUT); //ECHO é ENTRADA: o arduino lê o retorno //A 
  pinMode(BTN_PIN, INPUT_PULLUP); //A

  pinMode(TRIG_PIN, OUTPUT); //B
  pinMode(ECHO_PIN, INPUT); //B 
  pinMode(R, OUTPUT); pinMode(g, OUTPUT); //B
  pinMode(B, OUTPUT); //B
  pinMode(BUZZER_PIN, OUTPUT); //B

  Timer1.initialize(1000000); //C
  MFS.initialize(&Timer1); //C
}

void loop(){
  sequence(); //C
  int buttonvalue = 0;

  byte btn = MFS.getButton();

  for (int i=0; i < N; i++){ //C
    MFS.write(sequence_num[i]); //C
show_level(sequence_num[i],1000); //C
    delay(500); //C
  }

  if (btn == BUTTON_1_PRESSED || btn == BUTTON_2_PRESSED || btn == BUTTON_3_PRESSED || /*tempo >= 5seg passados*/) { //C
    float distance = get_distance();
    checkDistance();
    if (checkDistance() == 1)MFS.write(distance);
    delay(300); //C
  }

  int level = map_level(distance); //B 
  
  if(level == 0) MFS.write("0000"); //B
  else{ //B
    MFS.write(level);
    delay(200);}

  /*Serial.print("Dist: "); Serial.print(distance); //B 
  Serial.print(" cm -> Nivel: "); Serial.println(level); //B*/
  show_level(level, 1000); //mosta cor + toca som por 400 ms / B
  delay(100); //B

  /* if user gets right
   * level++
   * -game gets more difficult, adds another number to the sequence
   */
  /* if user gets wrong --> show "wrong!" & restart*/ 
}
