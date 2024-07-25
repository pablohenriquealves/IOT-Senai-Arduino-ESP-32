#define led 2
#define but 4

int butState = 0;
int butStateAnt = 0;

int ledState = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(but, INPUT);
  Serial.begin(115200);
}
int i = 0;
void loop() {

#pragma region Metodo Simples
  /*
      ==== Metodo Simples ===== 
  butState = digitalRead(but);
  ledState = butState;

  if(ledState) Serial.println("LED Ligado!!");
  else Serial.println("LED Desligado!!");
  
  digitalWrite(led, ledState);
  delay(1000);*/
#pragma endregion
#pragma region Metodo Médio
  /*
  butState = digitalRead(but);

  if (butState != butStateAnt) {
    butStateAnt = butState;
    ledState = butState;
    i ++;
    Serial.println(i);
    if (ledState) Serial.println("LED Ligado!!");
    else Serial.println("LED Desligado!!");

    digitalWrite(led, ledState);
    delay(10);
  }
  */
#pragma endregion

  butState = digitalRead(but);

  if (butState != butStateAnt) {
    butStateAnt = butState;

    if (butState) {
      ledState = !ledState;
      i++;
      Serial.println(i);
      if (ledState) Serial.println("LED Ligado!!");
      else Serial.println("LED Desligado!!");

      digitalWrite(led, ledState);
      delay(10);
    }
  }
}
