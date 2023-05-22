#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int backlightPin = 9; 
int contrast = 70; 


int sensor = A1;
int inputPin = A5;
int actuator = 10;
int PV = 0;
int inputValue = 0;
int CO = 0;

void setup() {
  pinMode(backlightPin, OUTPUT);
  lcd.begin(16, 2);

  pinMode(actuator, OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  //LCD
  analogWrite(backlightPin, contrast);



  PV = analogRead(sensor);
  inputValue = analogRead(inputPin);
  CO =map(inputValue, 15, 1000, 0 ,255);
analogWrite(actuator, CO);

Serial.print("\t PV = ");
Serial.print(PV);
Serial.print("\t input = ");
Serial.print(inputValue);
Serial.print("\t CO = ");
Serial.print(CO);
Serial.print("\t PV = ");
Serial.print(PV);
Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("PV: ");
    lcd.print(PV);
    lcd.setCursor(8, 0); 
    lcd.print("CO: ");
    lcd.print(CO);

    lcd.setCursor(0, 1); 
    lcd.print("Input: ");
    lcd.print(inputValue);

}