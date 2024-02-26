#include "EEPROM.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27  ,128,64);
//--------------------------------------
#define Buzz 2
#define ResetADMIN 15
#define Call_SEND 13
#define Gas  35
#define Fire 34
//---------------------------------------
String SDT;
int dem;
long TIme;
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  EEPROM.begin(10);
  pinMode(Buzz,OUTPUT);
  pinMode(ResetADMIN,INPUT_PULLUP);
  pinMode(Call_SEND,INPUT_PULLUP);
  pinMode(Gas,INPUT);
  pinMode(Fire,INPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
//-------------------------------------
  for(int i = 15; i >+ 0; i--) { lcd.clear(); lcd.setCursor(0,0); lcd.print("WAITING: "); lcd.print(i); delay(1000); }
   SimBoost();
//-------------------------------------  Check ADMIN
  for(int i = 1; i< 10; i++)
     { char A = EEPROM.read(i);
       SDT += String(A);
       while(SDT == "0" or SDT == "")
       { resetAD(); } delay(200);
     }
  lcd.clear();
  lcd.setCursor(4,0); lcd.print("ADMIN OK"); 
  lcd.setCursor(3,1); lcd.print("0"+SDT);   
}

void loop() {
  while(digitalRead(ResetADMIN) == 0) 
  { if(millis() - TIme >= 4000)
     { lcd.clear(); Serial.println("Reset ADMIN"); dem = 3; delay(200); }}  
  if(digitalRead(Call_SEND)  == 0) { lcd.clear(); lcd.setCursor(6,0); digitalWrite(Buzz,HIGH); lcd.print("SOS"); dem = 1;}
  if(analogRead(Fire) <= 1000 ) { lcd.clear(); lcd.setCursor(4,0); digitalWrite(Buzz,HIGH); lcd.print("HAVE FIRE"); dem = 5;}
  if(analogRead(Gas)  >= 1200 ) { lcd.clear(); lcd.setCursor(4,0); digitalWrite(Buzz,HIGH); lcd.print("HAVE GAS");  dem = 4;}
  if(dem == 1) {send_SMS(SDT,"SOS");  dem = 2;}
  if(dem == 4) {send_SMS(SDT,"HAVE GAS"); dem = 2;}
  if(dem == 5) {send_SMS(SDT,"HAVE FIRE");dem = 2;}
  if(dem == 2) {call(SDT);}
  if(dem == 3) 
  {  for(int i = 0; i < 10; i++)
       { EEPROM.write(i,0); EEPROM.commit();}
        SDT =""; resetAD();
  }
  TIme = millis();
}

//-------------------------------------------
String splitString(String inputString, String delim, uint16_t pos)
{ String tmp = inputString;
  for(int i = 0; i < pos; i++)
    { tmp = tmp.substring(tmp.indexOf(delim)+1);
      if(tmp.indexOf(delim) == -1 and i != pos-1) return "";
    }
  return tmp.substring(0,tmp.indexOf(delim));
}
