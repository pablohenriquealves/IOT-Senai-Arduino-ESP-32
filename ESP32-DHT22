
#pragma region Biblotecas
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#pragma endregion

#pragma region LCD
#define address 0x27
#define colunas 16
#define linhas 2
LiquidCrystal_I2C lcd(address, colunas, linhas);
#pragma endregion

#pragma region DHT
#define DHTPIN 18
#define DHTTYPE DHT22
#pragma endregion

#pragma region LDR
#define LDR A0
 int ldrValue = 0;
 int percLuz = 0;
#pragma endregion



float temp = 0.0;
float umid = 0.0;

byte grau[8] = {
  0b00000,
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte gota[8] = {
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};
byte termometro[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b11111,
  0b01110
};

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, grau);
  lcd.createChar(1, gota);
  lcd.createChar(2, termometro);

  dht.begin();

  Iniciar();
}

void loop() {

 if(!readDHT()){
   MS_ErrorDHT();
   return;
 }


// MS_Termometro();
readLDR();
MS_Luz();
}


void MS_Termometro(){
  lcd.clear();
  cursor(1,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" ");
  lcd.write(0);
  lcd.print("C ");
  lcd.write(2);

  cursor(0,1);
  lcd.print("Umid: ");
  lcd.print(umid);
  lcd.print("  % ");
  lcd.write(1);

  delay(500);
}

void Iniciar(){
  
  lcd.clear();
  cursor(3, 0);
  lcd.print("CARREGANDO");
  cursor(0, 1);
  for(int i = 0; i < 16; i++)
  {
    lcd.write(255);
    delay(250);
  }
  lcd.clear();
  lcd.print("Modulo iniciado!");
  delay(1000);


}


void MS_ErrorDHT(){
    lcd.clear();
    lcd.print("Falha no sensor!");
    delay(500);
}

bool readDHT(){
  
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  if(isnan(temp) || isnan(umid))
  {
    return false;
  }else{
    return true;
  }
}


void cursor(int bit1, int bit2)
{
  lcd.setCursor(bit1, bit2);
}

void readLDR()
{
  ldrValue = analogRead(LDR);
  percLuz = map(ldrValue, 32, 4063, 100, 0);
}

void MS_Luz()
{
  lcd.clear();
  lcd.print("  Lumin.: ");
  lcd.print(percLuz);
  lcd.print("  %");
  cursor(0,1);

  if(percLuz >= 0 && percLuz < 50)
  { 
    lcd.print("   BOA NOITE!");
  }else if(percLuz >= 50 && percLuz < 80){
    lcd.print("   BOA TARDE!");
  }
  else{
    lcd.print("    BOM DIA!");
  }
  delay(250);
}





