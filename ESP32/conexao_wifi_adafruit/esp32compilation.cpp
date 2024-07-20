//biblioteca utilizadas 
// wifimanager
// pubsubclients
// adafruitioarduino
// LiquidCrystal_I2C
// dht
// adafruitio_wifi
// wifi

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "AdafruitIO_WiFi.h"

#define SSID "Cat"
#define senha "senai@2024"

#define USER  "Catarina_gbps"
#define KEY       "aio_YXjW63fncMwWdEsvtaP37diqQAT4"

AdafruitIO_WiFi io(USER, KEY, SSID, senha);

AdafruitIO_Feed *F_L1 = io.feed("iotsenai.lamp1");
AdafruitIO_Feed *F_L2 = io.feed("iotsenai.lamp2");
AdafruitIO_Feed *F_Umid = io.feed("iotsenai.umidade");
AdafruitIO_Feed *F_Temp = io.feed("iotsenai.temperatura");

#define address 0x27
#define col 16
#define lin 2

LiquidCrystal_I2C lcd(address, col, lin);//Instância do display


#define DHTPin 4
#define DHTType DHT11
DHT dht(DHTPin, DHTType);

#define lamp1 14
#define lamp2 13
int lampState1 = 1;
int lampState2 = 1;
float umidade = 0.0;
float temperatura = 0.0;
float tempoLeitura = 0.0;

byte grau[8] = {                       // Define um caractere customizado para o símbolo de grau.
  0b00000,
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte gota[8] = {                       // Define um caractere customizado para o símbolo de gota.
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};
byte termometro[8] = {                 // Define um caractere customizado para o símbolo de termômetro.
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b11111,
  0b01110
};


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.createChar(0, grau);
  lcd.createChar(1, gota);
  lcd.createChar(0, termometro);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  digitalWrite(lamp1, lampState1);
  digitalWrite(lamp2, lampState2);
  dht.begin();

  while(!connectWifi()) return;
  while(!connectBroker()) return;

}

bool connectWifi()
{
  WiFi.begin(SSID, senha);
  lcd.clear();
  lcd.print("Conectando a rede:");
  lcd.setCursor(0,1);
  lcd.print(SSID);

  Serial.print("Conectando a rede: ");
  Serial.println(SSID);
  delay(1000);
  while(WiFi.status() != WL_CONNECTED)
  {
    lcd.write(255);
    Serial.print(".");
  }

  Serial.println("Wifi conectado");
  lcd.clear();
  lcd.print("Wifi conectado");
  delay(2000);
  return true;
}

bool connectBroker()
{
  Serial.print("Conectando ao Broker");
  lcd.clear();
  lcd.print("Conectando Broker");
  lcd.setCursor(0,1);
  io.connect();
  while(io.status() < AIO_CONNECTED)
  {
    Serial.println(".");
    lcd.write(255);
    delay(500);
    io.networkStatus();
  }
  lcd.clear();
  Serial.println();
  Serial.println("Conectado com sucesso");
  lcd.print("   Conectado");
  lcd.setCursor(2,1);
  lcd.print("com sucesso!");
  delay(1000);

  F_L1 -> onMessage(handleLamp1);
  F_L1 -> get();

  F_L2 -> onMessage(handleLamp2);
  F_L2 -> get();

  return true;
}

void publishSensor()
{
  if((millis() - tempoLeitura) > 5000)
  {
    F_Temp -> save(temperatura);
    F_Umid -> save(umidade);
    tempoLeitura = millis();
  }
}

void DHTRead() {
  umidade = dht.readHumidity(); // Lê a umidade do sensor DHT
  temperatura = dht.readTemperature(); // Lê a temperatura do sensor DHT

  // Verificação de erro na leitura do sensor
  if (isnan(umidade) || isnan(temperatura)) {
    return;
  }
  publishSensor();

  lcd.clear();
  lcd.print("Umid: ");
  lcd.print(umidade);
  lcd.print("% ");
  lcd.write(1);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print("");
  lcd.write(0);
  lcd.print("C ");
  lcd.write(2);
  delay(500);
}

void handleLamp1(AdafruitIO_Data *payload)
{
  if(payload ->isTrue())
  {
    lampState1 = HIGH;
  }
  else {
    lampState1 = LOW;
  }
  digitalWrite(lamp1, lampState1);
}

void handleLamp2(AdafruitIO_Data *payload)
{
  if(payload ->isTrue())
  {
    lampState2 = HIGH;
  }
  else {
    lampState2 = LOW;
  }
  digitalWrite(lamp2, lampState2);
}

void loop() {
  byte state = io.run();
  if(state == AIO_NET_DISCONNECTED | state == AIO_DISCONNECTED)
  {
    while(!connectWifi());
    while(!connectBroker());
  }
  DHTRead();
}