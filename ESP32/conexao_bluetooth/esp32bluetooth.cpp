
#include "BluetoothSerial.h" 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define Address 0x27
#define col 16
#define lin 2

#define DHTPin 4
#define DHTType DHT11

BluetoothSerial bt;
LiquidCrystal_I2C lcd(Address, col, lin);
DHT dht(DHTPin, DHTType);

#define lamp1 14
#define lamp2 13

String deviceName = "esp32_0101";
int lampState1 = 1;
int lampState2 = 1;
float temp = 0.0;
float umid = 0.0;

byte grau[8] = 
{
  0b00000,
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte gota[8] = 
{
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

void setup()
{
  Serial.begin(115200);//inicia comunicação serial
  bt.begin(deviceName);//inicia comunicação bluetooth
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, grau);
  lcd.createChar(1, gota);
  lcd.createChar(2, termometro);
  
  dht.begin();
  pinMode(lamp1, OUTPUT);
  digitalWrite(lamp1, lampState1);
  pinMode(lamp2, OUTPUT);
  digitalWrite(lamp2, lampState2);
}

void sensoresBluetooth()
{
  bt.println(lampState1);
  bt.println(lampState2);
  bt.println(temp);
  bt.println(umid);

}

void atuadoresBluetooth()
{
  if(bt.available() > 0)
  {
    String l = bt.readString();

    if (l == "L1") lampState1 = !lampState1;
    if (l == "L2") lampState2 = !lampState2;
  }
  digitalWrite(lamp1, lampState1);
  digitalWrite(lamp2, lampState2);

}


bool readDHT()
{
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  if(isnan(temp) || isnan(umid))
  {
    Serial.println("Falha no sensor");
    lcd.clear();
    lcd.print("Falha no sensor");
    return false;
  }

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Umidade: ");
  Serial.print(umid);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("");
  lcd.write(0);
  lcd.print("C");
  lcd.write(2);
  lcd.setCursor(1,1);
  lcd.print("Umid: ");
  lcd.print(umid);
  lcd.print(" %");
  lcd.write(1);
  delay(500);

  return true;
}

void loop()
{
  if(!readDHT()) return;
  sensoresBluetooth();
  atuadoresBluetooth();
  delay(500);
}
