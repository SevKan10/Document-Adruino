String ADMIN = "0949748546";            //Số ĐT ADMIN

void setup() {
  Serial.begin(9600);
  Serial.println("Test Module SIM800L"); 
  for(int i=15; i>0; i--){Serial.println(i); delay(1000);}
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  while(Serial2.available())
  {
    String inputString;
    while(Serial2.available()){inputString = Serial2.readString();}
    Serial.println(inputString);
  }

  while(Serial.available())
  {
    Serial2.println(Serial.readString());
  }
  
}