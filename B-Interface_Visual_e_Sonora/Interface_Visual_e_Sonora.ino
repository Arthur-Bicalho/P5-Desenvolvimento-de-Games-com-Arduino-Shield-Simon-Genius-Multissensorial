
//Define diferentes níveis de distâncias 
/*Nível 1: 0 a 10 cm
 * Nível 2: 10 a 20 cm
 * Nível 3: 20 a 30 cm
 * Nível 4: 30 a 40 cm
 */
const int R = 9, G = 6, B = 5;
const int BUZZER = 4;
const int trigPin = 9; echoPin = 8;

int mapearNivel(float distancia){
  if (distancia > 0 && distancia <= 10) return 1;
  else if (distancia > 10 && distancia <= 20) return 2;
  else if (distancia > 20 && distancia <= 30) return 3;
  else if (distancia > 30 && distancia <= 40) return 4;
  else return 0;
}

void loop(){
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
struct Nivel {int r, g, b, frequencia;};

const Nivel NIVEIS[] = {
  {255, 0, 0, 262}, //Nível 1 -- Vermelho/Dó
  {0, 255, 0, 294}, //Nível 2 -- Verde/Ré
  {0, 0, 255, 330}, //Nível 3 -- Azul/Mí
  {255, 150, 0, 349}, //Nível 4 -- Amarelo / Fá
  };

void definirCor(int r, int g, int b){
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

// Função principal: aplica cor + som de um nível
void exibirNível(int nível, int duracao){
  if (nivel < 1 || nivel> 4){
    definirCor(0, 0, 0);
    noTone(BUZZER);
    return;
    }

  Nivel n = NIVEIS[nivel - 1];
  tone(BUZZER, n.frequencia, duracao);
  delay(duracao);
  definirCor(0, 0, 0);
  noTone(BUZZER);
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




