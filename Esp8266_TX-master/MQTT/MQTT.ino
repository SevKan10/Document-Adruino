// CÁC HÀM LIÊN QUAN ĐẾN VIỆC ĐƯA DỮ LIỆU LÊN MQTT
// FUNCTIONS RELATED TO TRANSFER DATA TO MQTT
void setup_wifi() {
//  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {digitalWrite(BUILTIN_LED, HIGH); delay(250); digitalWrite(BUILTIN_LED, LOW); delay(250); }
  randomSeed(micros());
  clients.setInsecure();
}
//----------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    inData += (char)payload[i];
    String outData = inData+","; 
    mySerial.print(outData);
    inData = "";
  }
}
//----------------------------------------
void reconnect() {    
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) 
    {
      client.publish("DATA1", "Start");
      client.publish("DATA2", "Start");
      client.publish("DATA3", "Start");
      client.publish("DATA4", "Start");
      client.subscribe("DEVICE");
    } 
    else {digitalWrite(BUILTIN_LED, HIGH); delay(5000); }
  }
}
