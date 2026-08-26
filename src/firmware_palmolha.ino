// PROJETO PALMILHA INTELIGENTE - Etec Ary do Camargo Pedroso
// Integrantes: Donizete, Arao, Aureo, Bruno, Guilherme

const int PINO_FSR_ADC = 1;     // Entrada Analogica do Sensor FSR-402 / Potenciometro
const int PINO_MOSFET_PWM = 2;  // Saida PWM para acionamento do MOSFET / LED

const int LIMIAR_MINIMO = 150;  // Filtro de ruido para pisada leve
const int ADC_MAXIMO = 4095;    // Resolucao de 12 bits do ESP32-C3

void setup() {
  Serial.begin(115200);
  pinMode(PINO_FSR_ADC, INPUT);
  pinMode(PINO_MOSFET_PWM, OUTPUT);
  analogWrite(PINO_MOSFET_PWM, 0);
  
  Serial.println("=== SISTEMA DE AMORTECIMENTO MAGNETICO INICIALIZADO ===");
}

void loop() {
  int leituraADC = analogRead(PINO_FSR_ADC);
  int pwmSaida = 0;

  if (leituraADC > LIMIAR_MINIMO) {
    pwmSaida = map(leituraADC, LIMIAR_MINIMO, ADC_MAXIMO, 0, 255);
    pwmSaida = constrain(pwmSaida, 0, 255);
  } else {
    pwmSaida = 0;
  }

  analogWrite(PINO_MOSFET_PWM, pwmSaida);

  Serial.print("Leitura FSR (ADC): ");
  Serial.print(leituraADC);
  Serial.print(" | Intensidade Amortecimento (PWM): ");
  Serial.print(pwmSaida);
  Serial.print(" | Status: ");
  
  if (pwmSaida > 0) {
    Serial.println("ATUANDO (Repulsa Magnetica)");
  } else {
    Serial.println("REPOUSO");
  }

  delay(100);
}