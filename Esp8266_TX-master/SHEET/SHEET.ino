//============================================================================== void sendData

// HÀM ĐỂ GHI DỮ LIỆU VÀO Spreadsheet
// FUNCTION TO WRITE DATA to Spreadsheet
void sendData(int Environ , int Temp, int Heart, int Oxy) {
  if (!clients.connect(host, httpsPort)) { return; }
  
  String string_Environ =  String(Environ);
  String string_Temp    =  String(Temp);  
  String string_Heart   =  String(Heart);
  String string_Oxy     =  String(Oxy); 
  
  String url = "/macros/s/" + GAS_ID + "/exec?value1=" + string_Environ + "&value2=" + string_Temp + "&value3=" + string_Heart + "&value4=" + string_Oxy;
  clients.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
} 
//==============================================================================    
