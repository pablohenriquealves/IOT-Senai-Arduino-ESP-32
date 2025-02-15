#include <LiquidCrystal_I2C.h> // Incluir a Biblioteca

#define address 0x27
#define colums 16
#define rows 2
LiquidCrystal_I2C lcd(address, colums, rows); // Criando a instância

#define pot 4
int potValue = 0;
#define ldr 14
int ldrValue = 0;


void setup() {
  lcd.init(); //Inicia a comunicação I2C.
  lcd.backlight(); //liga o led de fundo do lcd.
  lcd.clear(); //apagar as informações na tela.

}

void loop() {

  potValue = analogRead(pot);
  
  lcd.clear();
  lcd.print(" Potenciomentro: ");
  lcd.setCursor(0, 1);
  lcd.print("  Valor: ");
  lcd.print(potValue);
  delay(3000);

  ldrValue = analogRead(ldr);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("LDR:");
  lcd.setCursor(0, 1);
  lcd.print("  Valor: ");
  lcd.print(ldrValue);
  delay(3000);
}
