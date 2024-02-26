/* 
smartchair.2022@gmail.com
123456789A@
*/

//ESP ĐỂ TRUYỀN DỮ LIỆU LÊN INTERNET
//ESP TO TRANSFER DATA ON THE INTERNET
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D2, D3); // RX, TX // CHÂN GIAO TIẾP VỚI ARDUINO - COMMUNICATION WITH ARDUINO
String myString; 
char rdata; 
int firstVal, secondVal, thirdVal, fourtVal;  // sensors 
//----------------------------------------
#include <ESP8266WiFi.h>         
#include <PubSubClient.h>

//KHỞI TẠO KẾT NỐI ĐẾN CLOUD MQTT - Initialize CONNECTION TO CLOUD MQTT
const char* ssid = "tháng 3";
const char* password = "jzbel.27";
const char* mqtt_server = "driver.cloudmqtt.com";
const char* mqtt_user = "fkcedhjn";
const char* mqtt_pass = "f871mlRLfSG3";   
WiFiClient espClient;
PubSubClient client(espClient);
String inData;
//----------------------------------------

//ID CỦA GOOGLE SHEET -  Initialize GOOGLE SHEET ID, TOKEN,...
#include <WiFiClientSecure.h>
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure clients;  //https
String GAS_ID = "AKfycbxgBt-xeZrWXUUcOXrGloYXQwBR0oE5H_pvaOl1xNmQsqC3B8glYs00wQOiX_8hOgUo"; 
int value1, value2, value3, value4;
//----------------------------------------
void setup() {
  Serial.begin(9600);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
  clients.setInsecure();

  pinMode(BUILTIN_LED, OUTPUT);     
  setup_wifi();
  client.setServer(mqtt_server, 18943); // KẾT NỐI ĐẾN SERVER MQTT - CONNECT TO MQTT SERVER
  client.setCallback(callback);
  mySerial.begin(9600);
}

void loop() {

  if (!client.connected()) { reconnect(); }
  client.loop();
  digitalWrite(BUILTIN_LED, HIGH); 
  if (mySerial.available() > 0 ) // NHẬN GIÁ TRỊ CÁC CẢM BIẾN TỪ ARDUNO - GET SENSOR VALUES FROM ARDUINO
  {
      rdata = mySerial.read(); 
      myString = myString+ rdata; 
      if( rdata == '\n')
      {
        String l = getValue(myString, ',', 0);
        String m = getValue(myString, ',', 1);
        String n = getValue(myString, ',', 2); 
        String o = getValue(myString, ',', 3); 
   
        firstVal  = l.toInt();
        secondVal = m.toInt();
        thirdVal  = n.toInt();
        fourtVal  = o.toInt();
        
        value1 = firstVal;      char nd1[16];     itoa(value1, nd1, 10);
        value2 = secondVal;     char nd2[16];     itoa(value2, nd2, 10);
        value3 = thirdVal;      char nd3[16];     itoa(value3, nd3, 10);
        value4 = fourtVal;      char nd4[16];     itoa(value4, nd4, 10);

        //GỬI GIÁ TRỊ LÊN CLOUD CỦA MQTT - SEND VALUE TO MQTT's CLOUD
        client.publish("DATA1", nd1); 
        client.publish("DATA2", nd2);
        client.publish("DATA3", nd3);
        client.publish("DATA4", nd4);
        
        sendData(value1, value2, value3, value4); // HÀM NÀY ĐỂ GHI GIÁ TRỊ VÀO Spreadsheet - THIS FUNCTION TO WRITE VALUES into the Spreadsheet
        digitalWrite(BUILTIN_LED, LOW); delay(100); digitalWrite(BUILTIN_LED, HIGH);   
        myString  = "";
      }
   }
  
}
