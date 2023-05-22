#include <LiquidCrystal.h>

const int buttonsPin = A4;
int buttonsValue = 0;
int screenState = 0;


int setPoint = 0;

int HYSplus;
int HYSminus;
int setPointplus;
int setPointminus;

int sensor = A1;
int inputPin = A5;
int actuator = 10;
int PV = 0;
int inputValue = 0;
int CO = 0;
int HYS = 30;


//LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int backlightPin = 9; 
int contrast = 70; 



void setup() {
  pinMode(backlightPin, OUTPUT);
  pinMode(actuator, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);

}



void loop() {


  //LCD
  analogWrite(backlightPin, contrast);




  PV = analogRead(sensor);

  if (PV <= setPoint - HYS)
  {
    CO = 255;
    
  }
  else if (PV >= setPoint + HYS)
  { 
    CO = 0;
    
  }

analogWrite(actuator, CO);



if(screenState == 3) {
  if (buttonsValue < 800 && buttonsValue > 750) {
    HYSplus = HYS + 5;
    HYS = HYSplus;
  } else if (buttonsValue < 749 && buttonsValue > 650) {
      HYSminus = HYS - 5;
      HYS = HYSminus;
  }   
}

if(screenState == 2) {
  if (buttonsValue < 800 && buttonsValue > 750) {
    setPointplus = setPoint + 5;
    setPoint = setPointplus;
  } else if (buttonsValue < 749 && buttonsValue > 650) {
      setPointminus = setPoint - 5;
      setPoint = setPointminus;
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
    lcd.print("HYS: ");
    lcd.print(HYS);
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
    lcd.print("SP: ");
    lcd.print(setPoint);
      break;

}

 

    

Serial.print("SP = ");
Serial.print(setPoint);
Serial.print("\t PV = ");
Serial.print(PV);
Serial.print("\t CO = ");
Serial.print(CO);
Serial.print("\t HYS = ");
Serial.print(HYS);
Serial.println();

 
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

