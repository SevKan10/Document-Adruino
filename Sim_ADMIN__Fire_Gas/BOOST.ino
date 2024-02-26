void SimBoost()
{
  lcd.clear(); 
  lcd.setCursor(5,0); lcd.print("Boost OK");
  Serial2.println("AT");
  updateSerial();
  Serial2.println("AT+CMGF=1");
  updateSerial();
  Serial2.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
}
void updateSerial()
{
 delay(500);
 while(Serial.available() > 0) { Serial2.write(Serial.read());}
 while(Serial2.available() > 0) { Serial.write(Serial2.read());}
}
