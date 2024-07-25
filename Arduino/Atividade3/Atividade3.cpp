/*Arduino 1*/
#define led 3
#define but1 2
#define but2 4
int leituraBut1 = 0;
int leituraBut2 = 0;
int modob1 = 0;
int modob2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
}

void loop() {
  leituraBut1 = digitalRead(but1);
  leituraBut2 = digitalRead(but2);

  if (leituraBut1 == HIGH) {
    modob1 = 1;
  } else if (leituraBut1 == LOW) {
    modob1 = 0;
  }

  if (leituraBut2 == HIGH) {
    modob2 = 1;
  } else if (leituraBut2 == LOW) {
    modob2 = 0;
  }

  if (modob1 == 0) {
    digitalWrite(led, LOW);
  } else if (modob1 == 1) {
    for (int i = 0; i <= 255; i++) {
      analogWrite(led, i);
      delay(10);
      if (i == 255) {
        Serial.println("Led Aceso");
      }
    }

    for (int i = 255; i >= 0; i--) {
      analogWrite(led, i);
      delay(10);
      if (i == 0) {
        Serial.println("Led Apagado");
      }
    }
  }

  if (modob2 == 0) {
    digitalWrite(led, LOW);
  } else if (modob2 == 1) {
    for (int i = 0; i <= 50; i++) {
      analogWrite(led, i);
      delay(10);
    }

    for (int i = 50; i >= 0; i--) {
      analogWrite(led, i);
      delay(10);
    }
  }
}

/*Arduino 2*/




//LDR

#define ldr A0
#define led 2

int valorLdr = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {

  valorLdr = analogRead(ldr);
  int valorPorcentagem = map(valorLdr, 54, 974, 0, 100);
  
  Serial.print("Luminosidade: ");
  Serial.print(valorPorcentagem);
  Serial.println("%");
  delay(1000);

  if(valorPorcentagem == 0)
  {
    digitalWrite(led, LOW);
  }

  if(valorPorcentagem == 100)
  {
    digitalWrite(led, HIGH);
  }


}