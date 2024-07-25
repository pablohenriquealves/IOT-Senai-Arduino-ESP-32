#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <WebServer.h>
#include <DHT.h>


#define SSID "Galaxy S10 Lt"
#define senha "ph123456"

#define address 0x27
#define colums 16
#define rows 2

#define DHTPin 4
#define DHTType DHT11


#define lamp1 14
#define lamp2 13

#define portWeb 80

int lampState1 = 1;
int lampState2 = 1;
float temperatura = 0.0;
float umidade = 0.0;

DHT dht(DHTPin, DHTType);

WebServer server(portWeb);

LiquidCrystal_I2C lcd(address, colums, rows);

String WebPage() {
  String webPage = "<!DOCTYPE html><html>"; // Inicia o HTML da página web
  webPage += "<head><title>Leitura do Sensor DHT11</title>";
  webPage += "<meta charset='UTF-8' http-equiv='refresh' content='3'>"; // Atualiza a página a cada 3 segundos
  webPage += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"; // Meta tag para responsividade
  webPage += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css'>"; // Inclui a biblioteca de ícones Font Awesome
  webPage += "<style>";
  webPage += "body {font-family: Arial; margin: 0; padding: 0;}";
  webPage += ".container {max-width: 600px; margin: 20px auto; padding: 20px; border: 2px solid #ccc; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); background-color: #fff;}";
  webPage += "h1 {color: #333;}";
  webPage += "p {font-size: 1.2em;}";
  webPage += "button {padding: 10px 20px; margin: 5px; font-size: 1em; background-color: #007bff; color: #fff; border: none; border-radius: 5px; cursor: pointer;}";
  webPage += "button:hover {background-color: #0056b3;}";
  webPage += ".icon {margin-right: 5px;}";
  webPage += "@media screen and (max-width: 600px) {"; // Media query para ajustes em dispositivos menores
  webPage += ".container {margin: 10px;}";
  webPage += "}";
  webPage += "</style>";
  webPage += "</head><body>";
  webPage += "<div class='container'>";
  webPage += "<h1>Leitura do Sensor DHT11</h1>";
  webPage += "<p><i class='fas fa-thermometer-half icon'></i>Temperatura: " + String(temperatura) + " °C</p>"; // Mostra a temperatura com ícone de termômetro
  webPage += "<p><i class='fas fa-tint icon'></i>Umidade: " + String(umidade) + " %</p>"; // Mostra a umidade com ícone de gota
  webPage += "<button onclick=\"location.href='/toggle1'\">"; // Botão para alternar a lâmpada 1
  webPage += lampState1 ? "<i class='fas fa-toggle-on icon'></i>Ligar Lâmpada" : "<i class='fas fa-toggle-off icon'></i>Desligar Lâmpada"; // Texto do botão baseado no estado da Lâmpada 1
  webPage += "</button>";
  webPage += "<button onclick=\"location.href='/toggle2'\">"; // Botão para alternar a lâmpada 2
  webPage += lampState2 ? "<i class='fas fa-toggle-on icon'></i>Ligar Lâmpada" : "<i class='fas fa-toggle-off icon'></i>Desligar Lâmpada"; // Texto do botão baseado no estado da Lâmpada 2
  webPage += "</button>";
  webPage += "</div></body></html>";

  return webPage;
}

bool conexaoWiFi(){
  WiFi.begin(SSID, senha);
  lcd.clear();
  lcd.print("Conectando a rede: ");
  lcd.setCursor(0,1);
  lcd.print(SSID);

  
  Serial.print("Conectando a rede: ");
  Serial.println(SSID);

  while(WiFi.status() != WL_CONNECTED)
  {
    lcd.write(255);
    Serial.print(".");
  }
  Serial.println("Wifi conectado");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print("Wifi conectado");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(2000);
  ServerInit();
  return true;
}

bool DHTRead()
{
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  if(isnan(umidade) || isnan(temperatura))
  {
    Serial.println("Falha no sensor!");
    server.send(500, "text/plain", "Erro ao ler o sensor DHT");
    return false;
  }
  return true;
}

void handleRoot(){
  if(!DHTRead()) return;
  server.send(200, "text/html", WebPage());
  Serial.println("Página web enviada.");
}

void handleToggleLamp1(){
  lampState1 = !lampState1;
  digitalWrite(lamp1, lampState1);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggleLamp2(){
  lampState2 = !lampState2;
  digitalWrite(lamp2, lampState2);
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleDHTRead(){
  if(!DHTRead()) return;
  String json = "{\"temperatura\":" + String(temperatura) + ",\"umidade\":" + String(umidade) + "}";
  server.send(200, "application/json", json);
  Serial.println("Dados do sensor enviados com sucesso.");
}

void ServerInit(){
  server.on("/", handleRoot);
  server.on("/toggle1", handleToggleLamp1);
  server.on("/toggle2", handleToggleLamp2);
  server.on("/dht", handleDHTRead);
  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

void setup() {
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  digitalWrite(lamp1, lampState1);
  digitalWrite(lamp2, lampState2);
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.home();
}

void loop() {
  while(WiFi.status() != WL_CONNECTED) conexaoWiFi();
  
  server.handleClient();

}

