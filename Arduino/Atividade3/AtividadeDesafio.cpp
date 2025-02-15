/*
Atividade 1
#define led 5 

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  for(int i = 0; i <= 255; i++)
  {    
    analogWrite(led, i);
    delay(10);
  }
  
  for(int i = 255; i >= 0; i--)
  {
  	analogWrite(led, i);
      delay(10);
  }
  
 }
 */



/* 
Atividade 3
#define led 5

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Comunicação estabelecida");
}

void loop()
{
  if(Serial.available() > 0)
  {
    String caractere = " ";
    caractere = Serial.readString();
    caractere.toUpperCase();
    Serial.print("O caractere digitado foi: ");
    Serial.println(caractere);

    if (caractere == "L")
    {
      digitalWrite(led, HIGH);
      Serial.print("Led ligado!");

    }
    else if(caractere == "D")
    {
      digitalWrite(led, LOW);
      Serial.print("Led desligado!");
    }
  }
}

*/


/*Atividade 3

#define pot A0
#define led 5
float potValue = 0;
float tensao = 0.0;
int ledBrilho = 0;
float percBrilho = 0.0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  potValue = analogRead(pot);

  Serial.print("Potenciometro: ");
  Serial.println(potValue);
  delay(200);
  tensao = (potValue * 5) / 1023;
  Serial.print("Tensao: ");
  Serial.print(tensao);
  Serial.println("v");
  
  ledBrilho = map(potValue, 0, 1023, 0, 255);
  percBrilho = map(ledBrilho, 0, 255, 0, 100);
  analogWrite(led, ledBrilho);
  
  Serial.print("Brilho do led: ");
  Serial.print(percBrilho);
  Serial.println(" %");
  delay(200);
}
*/



/* Atividade 4 */
#define ldr A1
#define led 5
int ldrValue = 0;
int ldrBrilho = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Comunicação serial inicializada!");
}

void loop() {
  ldrValue = analogRead(ldr);
  ldrBrilho = map(ldrValue, 6, 679, 0, 100);
  if (ldrBrilho >= 6) {
    analogWrite(led, ldrBrilho);
  }



  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.println("");

  Serial.print("Brilho LDR: ");
  Serial.print(ldrBrilho);
  Serial.println(" %");
  delay(500);
}