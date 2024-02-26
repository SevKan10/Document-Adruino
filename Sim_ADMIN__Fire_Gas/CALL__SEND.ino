void send_SMS(String sdt,String Content)
{
 Serial.println("Đang Gửi Tin Nhắn");
 Serial2.println("AT+CMGF=1");
 updateSerial();
 Serial2.println("AT+CMGS=\"+84"+sdt+"\"");
 updateSerial();
 Serial2.print(Content);
 updateSerial();
 Serial.println();
 Serial.println(Content);
 Serial2.write(26);
 delay(8000);
 Serial.println("Send OK");
}

void call(String sdt)
{
 Serial2.print(F("ATD"));
 updateSerial();
 Serial.println("Đang Thực Hiện Cuộc Gọi");
 Serial2.print("0"+sdt);
 updateSerial();
 Serial2.print(F(";\r\n"));
 delay(20000);
 Serial2.print(F("ATH"));
 updateSerial();
 Serial2.print(F(";\r\n"));
 updateSerial();
 delay(1000);
 Serial.println("CALL OK");
 lcd.clear();
  lcd.setCursor(4,0); lcd.print("ADMIN OK"); 
  lcd.setCursor(3,1); lcd.print("0"+SDT);
  digitalWrite(Buzz,LOW);   
  dem = 0;
}
