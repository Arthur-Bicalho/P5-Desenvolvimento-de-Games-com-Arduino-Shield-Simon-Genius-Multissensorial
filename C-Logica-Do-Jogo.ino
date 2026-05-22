#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>

#define N 10;


int sequence_num[N];
int level=1;

void sequence(){
  srand(analogRead(A0)) // REVISAR SE É REALMENTE A0!!!
  for (int i = 0; i < N; i++) {
    sequence_num[i] = (rand() % 4) + 1;
  }
}

boolean checkDistance(){

}

void setup(){
  Timer1.initialize(1000000);
  MFS.initialize(&Timer1);
  sequence();
  for (int i=0; i < N; i++){
    MFS.write(sequence_num[i]);
    exibirNivel(medirDistancia(),1000);
    delay(500);
  }
}

void loop(){
  if (btn = BUTTON_PRESSED || Timer1 >= 5000000){
    float distace=medirDistancia();
    checkDistance();
    if (checkDistance() == 1)MFS.write(distace);
  }

  /* if user gets right
   * level++
   * -game gets more difficult, adds another number to the sequence
   */
  /* if user gets wrong --> show "wrong!" & restart*/ 
}
