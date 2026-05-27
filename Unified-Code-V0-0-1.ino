#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <stdlib.h>
#include <time.h>

#define TRIG_PIN A4
#define ECHO_PIN A5

#define LED_R 3
#define LED_G 5
#define LED_B 6

#define BUZZER_PIN 3
#define BTN_PIN 2

#define N 10;
#define TIMEOUT_seg 5000


/*=========================Global Variables=========================*/
int sequence_num[N];
int seq_size=1;
int level=1;
/*============================Struct============================*/
struct Level {int r, g, b, frequence;};                         // Revisar isso aqui,
                                                                // será que precisa ser struct?
const Level LEVELS[] = {                                        // as vezes usar uma matriz seria melhor (ver referencia):
                                                                // Nota (Hz) e cor RGB para cada nível 1-4
  {255, 0, 0, 262}, //Nível 1 -- Vermelho/Dó                    // const int  NOTA[5] = { 0, 262, 294, 330, 392 }; // Dó Ré Mi Sol
  {0, 255, 0, 294}, //Nível 2 -- Verde/Ré                       // const byte COR_R[5] = { 0, 255,   0,   0, 255 };
  {0, 0, 255, 330}, //Nível 3 -- Azul/Mí                        // const byte COR_G[5] = { 0,   0, 255,   0, 255 };
  {255, 150, 0, 349}, //Nível 4 -- Amarelo / Fá                 // const byte COR_B[5] = { 0,   0,   0, 255,   0 };
                                                                // Nível:              0    1    2    3    4
                                                                // Cor:                -  Verm  Verd Azul  Amar

  };

/*============================Functions============================*/
void sequence(){
  srand(analogRead(A0)) // REVISAR SE É REALMENTE A0!!!
  for (int i = 0; i < N; i++) {
    sequence_num[i] = (rand() % 4) + 1;
  }
}

float get_distance(){
  digitalWrite(TRIG_PIN, LOW); //antes de gerar o pulso força o pino para LOW
  delayMicroseconds(2); //aguarda 2 microsegundos para estabilizar
  digitalWrite(TRIG_PIN, HIGH); //Inicia o pulso de disparo
  delayMicroseconds(10); //Mantém HIGH por 10 microsegundos
  digitalWrite(TRIG_PIN, LOW); //encerra o pulso
  float duration = pulseIn(ECHO_PIN, HIGH); //mde a duração do pulso HIGH no pino ECHO
  if(duration == 0) return 0;
  float cm = duration * 0.034/2.0; //calculo da distância
  return cm; //Retorna o resultado para quem chamou a função
}

int map_level(float distance){
  if (distance <= 10) return 1;
  else if (distance <= 20) return 2;
  else if (istance <= 30) return 3;
  else if (distance <= 40) return 4;
  else return 0;
}

void set_color(int r, int g, int b){
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

void show_level(int level, int duration){
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

bool checkDistance(){

}

bool right_wrong(){
  l
}

/*============================Start============================*/
void setup(){
  Serial.begin(9600);

  Timer1.initialize(1000000);
  MFS.initialize(&Timer1);

  pinMode(TRIG_PIN, OUTPUT); //TRIG é SAÍDA: o Arduino envia o pulso
  pinMode(ECHO_PIN, INPUT); //ECHO é ENTRADA: o arduino lê o retorno
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  MFS.beep(); // beep de inicialização
  delay(1000);
}
/*============================Loop============================*/
void loop(){
  sequence();
  int buttonvalue = 0;

  byte btn = MFS.getButton();

  for (int i=0; i < N; i++){
    MFS.write(sequence_num[i]);
show_level(sequence_num[i],1000);
    delay(500);
  }

  if (btn == BUTTON_1_PRESSED || btn == BUTTON_2_PRESSED || btn == BUTTON_3_PRESSED || /*tempo >= 5seg passados*/) {
    float distance = get_distance();
    checkDistance();
    if (checkDistance() == 1)MFS.write(distance);
    delay(300);
  }

  int level = map_level(distance);
  
  if(level == 0) MFS.write("0000");
  else{
    MFS.write(level);
    delay(200);}

  show_level(level, 1000); //mosta cor + toca som por 400 ms
  delay(100);

  /* if user gets right
   * level++
   * -game gets more difficult, adds another number to the sequence
   */
  /* if user gets wrong --> show "wrong!" & restart*/ 
}



/*====================Claude Code Gen For Reference==========================
 * // LEDs do Shield associados a cada nível (LED_1..LED_4)
const byte LED_MFS[5] = { 0, LED_1, LED_2, LED_3, LED_4 };


int  sequencia[SEQ_MAX];
int  seqTamanho    = 1;
int  velApres      = 1000;   // ms por item na apresentação
const int VEL_MIN  = 300;
const int VEL_DECR = 50;

// ── Protótipos ──────────────────────────────────────────────
void setLED(byte r, byte g, byte b);
void acenderNivel(int n);
void apagarLED();
void apresentarSequencia();
bool lerResposta(int esperado);
int  lerNivel();
void sinalizarErro();
void sinalizarVitoria();
void efeitoArcoIris();
// ════════════════════════════════════════════════════════════
void loop() {

  seqTamanho = 1;
  velApres   = 1000;

  while (seqTamanho <= SEQ_MAX) {

    MFS.write(seqTamanho);   // mostra fase no display
    delay(800);

    apresentarSequencia();

    // Jogador reproduz a sequência item a item
    bool acertou = true;
    for (int i = 0; i < seqTamanho; i++) {
      MFS.write(i + 1);      // posição atual

      if (!lerResposta(sequencia[i])) {
        acertou = false;
        break;
      }
      delay(300);
    }

    if (!acertou) {
      sinalizarErro();
      delay(2000);
      return;                // reinicia tudo
    }

    if (seqTamanho % 5 == 0) efeitoArcoIris();
    else                     sinalizarVitoria();

    seqTamanho++;
    if (velApres - VEL_DECR >= VEL_MIN) velApres -= VEL_DECR;
    delay(800);
  }

  // Zerou o jogo!
  MFS.write("WIN");
  efeitoArcoIris();
  efeitoArcoIris();
  delay(3000);
}

// ════════════════════════════════════════════════════════════
//  Apresenta os primeiros seqTamanho itens ao jogador
// ════════════════════════════════════════════════════════════
void apresentarSequencia() {
  delay(400);
  for (int i = 0; i < seqTamanho; i++) {
    int n = sequencia[i];

    acenderNivel(n);
    MFS.writeLeds(LED_MFS[n], ON);   // LED do Shield

    // Beep proporcional à duração atual
    // parâmetros: ms_on, ms_off, ciclos, loops, pausa_loops
    int ciclos = velApres / 100;
    MFS.beep(ciclos, 1, 1, 1, 1);   // tom ativo por ~velApres ms
    tone(LED_R - LED_R + 3,          // reutiliza pino 3 como saída de tom
         NOTA[n], velApres);         // tom real no buzzer externo (opcional)
    // Para buzzer do Shield use só MFS.beep — tone() é alternativa com RGB

    delay(velApres);
    apagarLED();
    MFS.writeLeds(LED_MFS[n], OFF);
    delay(400);
  }
}

// ════════════════════════════════════════════════════════════
//  Aguarda o jogador confirmar com BUTTON_1 (ou timeout 5 s)
// ════════════════════════════════════════════════════════════
bool lerResposta(int esperado) {
  unsigned long t0 = millis();

  // Feedback visual em tempo real
  while (millis() - t0 < TIMEOUT_MS) {
    int n = lerNivel();
    if (n > 0) acenderNivel(n); else apagarLED();

    if (MFS.getButton() == BUTTON_1_PRESSED) break;
  }

  apagarLED();

  int lido = lerNivel();
  MFS.write(lido);                     // exibe nível lido no display

  if (lido == esperado) {
    MFS.writeLeds(LED_MFS[lido], ON);
    MFS.beep(2, 1, 1, 1, 1);          // bip curto de acerto
    delay(400);
    MFS.writeLeds(LED_MFS[lido], OFF);
    return true;
  }
  return false;
}

// ════════════════════════════════════════════════════════════
//  Controle do LED RGB externo
// ════════════════════════════════════════════════════════════
void setLED(byte r, byte g, byte b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void acenderNivel(int n) {
  if (n < 1 || n > 4) return;
  setLED(COR_R[n], COR_G[n], COR_B[n]);
}

void apagarLED() { setLED(0, 0, 0); }

// ════════════════════════════════════════════════════════════
//  Sinaliza erro: display "Err", 3 bips, LED vermelho
// ════════════════════════════════════════════════════════════
void sinalizarErro() {
  MFS.write("Err");
  MFS.blinkDisplay(DIGIT_ALL, ON);
  MFS.beep(3, 3, 3, 1, 1);          // 3 bips rápidos × 3
  for (int i = 0; i < 3; i++) {
    setLED(255, 0, 0); delay(300);
    apagarLED();       delay(150);
  }
  MFS.blinkDisplay(DIGIT_ALL, OFF);
}

// ════════════════════════════════════════════════════════════
//  Sinaliza vitória de rodada: sequência de LEDs + bips
// ════════════════════════════════════════════════════════════
void sinalizarVitoria() {
  MFS.write("GooD");
  for (int n = 1; n <= 4; n++) {
    MFS.writeLeds(LED_MFS[n], ON);
    acenderNivel(n);
    MFS.beep(2, 1, 1, 1, 1);
    delay(220);
    MFS.writeLeds(LED_MFS[n], OFF);
    apagarLED();
  }
}

// ════════════════════════════════════════════════════════════
//  Efeito arco-íris (desafio adicional — a cada 5 rodadas)
// ════════════════════════════════════════════════════════════
void efeitoArcoIris() {
  MFS.write("Arc");
  MFS.blinkLeds(LED_ALL, ON);

  for (int h = 0; h < 360; h += 6) {
    float c = 1.0, x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
    float r1, g1, b1;
    if      (h <  60) { r1 = c; g1 = x; b1 = 0; }
    else if (h < 120) { r1 = x; g1 = c; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = c; b1 = x; }
    else if (h < 240) { r1 = 0; g1 = x; b1 = c; }
    else if (h < 300) { r1 = x; g1 = 0; b1 = c; }
    else              { r1 = c; g1 = 0; b1 = x; }
    setLED(r1 * 255, g1 * 255, b1 * 255);
    delay(18);
  }

  MFS.blinkLeds(LED_ALL, OFF);
  MFS.writeLeds(LED_ALL, OFF);
  apagarLED();
}
*/
