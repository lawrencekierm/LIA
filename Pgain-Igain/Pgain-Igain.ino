#include <LiquidCrystal.h>

const int buttonsPin = A4;
int buttonsValue = 0;
int screenState = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int backlightPin = 9; 
int contrast = 70; 

int setPoint = 0;
float gainplus;
float gainminus;
float iGplus;
float iGminus;

int sensor = A1;
int inputPin = A5;
int actuator = 10;
int PV = 0;
int CO = 0;
int Error = 0;
float pGain = 0.01;
float iGain = 0.01;
int integralAction;
unsigned long previousMillis = 0;
const long interval = 100;
unsigned long currentMillis;

float exCO;

void setup() {
  pinMode(actuator, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(backlightPin, OUTPUT);

}

void loop() {
analogWrite(backlightPin, contrast);

  PV = analogRead(sensor);
  setPoint = analogRead(inputPin);
  currentMillis = millis();

if (currentMillis - previousMillis >= interval) {

  previousMillis = currentMillis;
  Error = setPoint-PV;
  integralAction = (integralAction + Error);
  CO = (pGain*Error)+(iGain*integralAction)/100;

  if (CO >255) {
    CO = 255;
  }

    if (CO<0) {
      CO = 0;
    }
  }
  
  
analogWrite(actuator, CO);


if(screenState == 3) {
  if (buttonsValue < 800 && buttonsValue > 750) {
    gainplus = pGain + 0.01;
    pGain = gainplus;
  } else if (buttonsValue < 749 && buttonsValue > 650) {
      gainminus = pGain - 0.01;
      pGain = gainminus;
  }   
}

if(screenState == 2) {
  if (buttonsValue < 800 && buttonsValue > 750) {
    iGplus = iGain + 0.01;
    iGain = iGplus;
  } else if (buttonsValue < 749 && buttonsValue > 650) {
      iGminus = iGain - 0.01;
      iGain = iGminus;
  }   
}


screenSwitch ();
switch(screenState) {
  case 3:
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("PV: ");
    lcd.print(PV);
    lcd.setCursor(8, 0); 
    lcd.print("CO: ");
    lcd.print(CO);

    lcd.setCursor(0, 1); 
    lcd.print("pG:");
    lcd.print(pGain);
    lcd.setCursor(8, 1); 
    lcd.print("Err: ");
    lcd.print(Error);
      break;
  
  case 2:
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("PV: ");
    lcd.print(PV);
    lcd.setCursor(8, 0); 
    lcd.print("CO: ");
    lcd.print(CO);

    lcd.setCursor(0, 1); 
    lcd.print("iG:");
    lcd.print(iGain);
    lcd.setCursor(8, 1); 
    lcd.print("Err: ");
    lcd.print(Error);
      break;

}

/*
Serial.print("SP = ");
Serial.print(setPoint);
Serial.print("\t PV = ");
Serial.print(PV);
Serial.print("\t CO = ");
Serial.print(CO);
Serial.print("\t P Gain = ");
Serial.print(pGain);
Serial.print("\t I gain = ");
Serial.print(iGain);
Serial.println();
*/

Serial.print(setPoint);
Serial.print(",");
Serial.print(PV);
Serial.print(",");
Serial.print(CO);
Serial.print(",");
Serial.print(pGain);
Serial.print(",");
Serial.print(iGain);
Serial.println();

delay(100);

}



void screenSwitch () {
  buttonsValue = analogRead(buttonsPin);

  if (buttonsValue < 649 && buttonsValue > 425) {
    screenState = 2;
    //delay(100);
  }

  if (buttonsValue < 425 && buttonsValue >= 0) {
    screenState = 3;
    //delay(100);
  }
 

 
}
