
//Define diferentes níveis de distâncias 
/*Nível 1: 0 a 10 cm
 * Nível 2: 10 a 20 cm
 * Nível 3: 20 a 30 cm
 * Nível 4: 30 a 40 cm
 */
const int R = 9, G = 6, B = 5;
const int BUZZER = 4;
const int trigPin = 9; echoPin = 8;

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
void loop(){ // 2 VOID LOOPS???
  float distancia = medirDistancia();
  int nivel = mapearNivel(distancia);

  if(nivel == 0){
      Serial.println("Fora do alcance");
      } else{
        Serial.print("Nível: ");
        }
      delay(200);
}

// Estrutura e tabela de níveis
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

void setup(){
  Serial.begin(9600);
  pinMode(trigPint, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(R, OUTPUT); pinMode(g, OUTPUT); pinMode(B, OUTPUT);
  pinMode(BUZZER, OUTPUT)
}

void loop(){
  float distancia = medirDistancia();
  int nivel = mapearNivel(distancia);

  Serial.print("Dist: "); Serial.print(distancia);
  Serial.print(" cm -> Nivel: "); Serial.println(nivel);

  exibirNivel(nivel, 400); //mosta cor + toca som por 400 ms
  delay(100);
}




