#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Pines
const int PIN_SENSOR = A0;
const int PIN_R = 3;
const int PIN_G = 5;
const int PIN_B = 6;

// Calibración básica
const int RAW_SECO   = 200;  // aire
const int RAW_HUMEDO = 536;  // suelo húmedo

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  lcd.setCursor(0,0);
  delay(500);
}

void loop() {
  // Leer sensor y convertir a %
  int raw = analogRead(PIN_SENSOR);
  int humedadPct = map(raw, RAW_SECO, RAW_HUMEDO, 0, 100);
  if(humedadPct < 0) humedadPct = 0;
  if(humedadPct > 100) humedadPct = 100;

  // Mostrar en LCD
  lcd.setCursor(0,0);
  lcd.print("Hum: ");
  lcd.print(humedadPct);
  lcd.print("%   ");

  lcd.setCursor(0,1);
  if(humedadPct < 30) lcd.print("Estado: SECO   ");
  else if(humedadPct <= 70) lcd.print("Estado: OPTIMO ");
  else lcd.print("Estado: HUMEDO ");

  // LED RGB
  if(humedadPct < 30) setRGB(255,0,0);      // seco
  else if(humedadPct <= 70) setRGB(0,255,0);// óptimo
  else setRGB(0,0,255);                     // húmedo

  delay(500);
}

void setRGB(byte r, byte g, byte b){
  analogWrite(PIN_R, r);
  analogWrite(PIN_G, g);
  analogWrite(PIN_B, b);
}
