// Definindo os pinos dos LEDs
#define lVermelho 2 // LED vermelho conectado ao pino 2
#define lAmarelo 3 // LED amarelo conectado ao pino 3
#define lVerde 4   // LED verde conectado ao pino 4

void setup() {
  // Configurando os pinos dos LEDs como saída
  pinMode(lVermelho, OUTPUT); // Define o pino 2 como saída
  pinMode(lAmarelo, OUTPUT);  // Define o pino 3 como saída
  pinMode(lVerde, OUTPUT);    // Define o pino 4 como saída
}

void loop() {
  // Ciclo do semáforo: Verde -> Amarelo -> Vermelho

  // Acende o LED verde e apaga o LED vermelho
  digitalWrite(lVermelho, LOW); // Apaga o LED vermelho
  digitalWrite(lVerde, HIGH);   // Acende o LED verde
  // Aguarda 2 segundos
  delay(2000); // Pausa por 2000 milissegundos (2 segundos)

  // Apaga o LED verde e acende o LED amarelo
  digitalWrite(lVerde, LOW);   // Apaga o LED verde
  digitalWrite(lAmarelo, HIGH); // Acende o LED amarelo
  // Aguarda 1 segundo
  delay(1000); // Pausa por 1000 milissegundos (1 segundo)

  // Apaga o LED amarelo e acende o LED vermelho
  digitalWrite(lAmarelo, LOW);   // Apaga o LED amarelo
  digitalWrite(lVermelho, HIGH); // Acende o LED vermelho
  // Aguarda 3 segundos
  delay(3000); // Pausa por 3000 milissegundos (3 segundos)
}
