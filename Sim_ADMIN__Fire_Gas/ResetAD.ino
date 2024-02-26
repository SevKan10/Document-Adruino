void resetAD()
{
 String Readstr; 
 lcd.setCursor(5,1); lcd.print("NO ADMIN");
 while(Serial2.available() > 0)
     { Readstr = Serial2.readString(); SDT += String(Readstr); }
    if(splitString(SDT,"#",1) == "ADMIN")
     {
      SDT = splitString(SDT,"\"",1);
      SDT = splitString(SDT,"+",1);
       for(int i = 2; i < 11; i++) 
       {EEPROM.write(i-1,SDT[i]); EEPROM.commit(); Serial.println(SDT[i]);}
       SDT =""; return resetAd();
     }
  Readstr ="";
}
//---------------------------------------
void resetAd()
{ 
 for(int i = 1; i<10; i++)
   { char A = EEPROM.read(i);
     SDT += String(A); 
     while (SDT =="0" or SDT =="")
      {resetAD();}
   }
  Serial.println(SDT);
  Serial.println("Reset OK");
  digitalWrite(Buzz,LOW);
  send_SMS(SDT,"Hello ADMIN");
    ESP.restart();   
}
