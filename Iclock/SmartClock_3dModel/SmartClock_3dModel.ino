#include <ESP8266WiFi.h>
// Libraries for internet time
#include <WiFiUdp.h>
#include <NTPClient.h> // include NTPClient library
#include <TimeLib.h>   // include Arduino time library
#include <WiFiManager.h>
// Libraries for internet weather
#include <ESP8266HTTPClient.h> // http web access library
#include <ArduinoJson.h>       // JSON decoding library
// Libraries for SSD1306 OLED display
#include <Wire.h> // include wire library (for I2C devices such as the SSD1306 display)


#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

WiFiUDP ntpUDP;
// 'time.nist.gov' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
NTPClient timeClient(ntpUDP, "time.nist.gov", 3600, 60000);

#define BTN_MODE 12
int countMode = 0;

//weather
String Location = "hanoi";
String API_Key = "<>"; // lay API tren trang nay https://openweathermap.org/api
int temp=0;
int humidity=0;

String message = "Hello, I'm donglinhit.hust@gmail.com!";
uint8_t index_mes=0;
//time
int UTC =7;
byte last_second, last_minute, second_, minute_, hour_, wday, day_, month_, year_;
unsigned long unix_epoch;

//am lich
#include "amlich.h"
#include "src/ssd1306/screen.h"

String url="";
String version="0.2";
uint8_t _enable_update =0;

void getDataConfig();
void updateTime();
void configWifi();
void systemDisplay();
void updateWeather();
void settingAmLich();
void displayAmLich();
void parseTime(unsigned long unix_epoch);
String map_wday(uint8_t wday);
unsigned long _times;

const int interruptPin = 14;
volatile uint8_t intfired=0;
ICACHE_RAM_ATTR void handleInterrupt() {    //THE PROBLEM IS THIS LINE! 
  while (digitalRead(interruptPin) ==0);
  intfired++;
}
void update_ota();
void setup(void)
{
    Serial.begin(115200);
    pinMode(interruptPin, INPUT_PULLUP);
  //ICACHE_RAM_ATTR;
    attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
    init_screen();
    delay(1000);
    draw_screen_main();
    delay(1000);
    configWifi();
    delay(100);
    timeClient.begin();
    _times = millis();
    clear_screen();
    // pinMode(3,INPUT_PULLUP)
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED) // check WiFi connection status
    {
        updateTime();
        updateWeather();
        display_time(hour_,minute_,second_);
        draw_temp(temp,humidity);
        draw_date(map_wday(wday),day_,month_);
        if ((unsigned long)(millis() - _times) > 150)
        {
            index_mes++;
            if(index_mes > message.length()) index_mes=0;
            notify(message, index_mes);
            _times = millis();
        }
       
    }
    Serial.println(intfired);
    if (intfired %3 ==1) {
        Serial.println();
        update_ota();
        intfired=false;
    }
    // else
    // {
    // }
}

//--------------------------------------------------------------

void configWifi()
{
    WiFiManager wifiManager;
    wifiManager.autoConnect("IClock");
}
void updateTime()
{
    timeClient.update();
    unix_epoch = timeClient.getEpochTime(); // get UNIX Epoch time
    unix_epoch += (UTC -1) * 3600;         // UTC+7
    second_ = second(unix_epoch);           // get seconds from the UNIX Epoch time
    if (last_second != second_)
    { // update time & date every 1 second
        parseTime(unix_epoch);
    }
}
void parseTime(unsigned long unix_epoch)
{
    second_ = second(unix_epoch);
    minute_ = minute(unix_epoch);    // get minutes (0 - 59)
    hour_ = hour(unix_epoch);        // get hours   (0 - 23)
    wday = weekday(unix_epoch);      // get minutes (1 - 7 with Sunday is day 1)
    day_ = day(unix_epoch);          // get month day (1 - 31, depends on month)
    month_ = month(unix_epoch);      // get month (1 - 12 with Jan is month 1)
    year_ = year(unix_epoch) - 2000; // get year with 4 digits - 2000 results 2 digits year (ex: 2018 --> 18)
    last_second = second_;
}
String map_wday(uint8_t wday)
{
  switch(wday)
  {
    case 1:  return "SUN"; break;
    case 2:  return "MON"; break;
    case 3:  return "TUE"; break;
    case 4:  return "WED"; break;
    case 5:  return "THU"; break;
    case 6:  return "FRI"; break;
    default: return "SAT";
  }
 
}

void updateWeather()
{
    if (last_minute != minute_) // update weather every 1 minute
    {
        HTTPClient http; // declare an object of class HTTPClient
        String request = "http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key;
        http.begin(request);       // !!
        int httpCode = http.GET(); // send the request
        if (httpCode > 0) // check the returning code
        {
            String payload = http.getString(); // get the request response payload
            DynamicJsonBuffer jsonBuffer(512);
            // Parse JSON object
            JsonObject &root = jsonBuffer.parseObject(payload);
            JsonArray &weathers = root["weather"];
            if (!root.success())
            {
                Serial.println(F("Parsing failed!"));
                return;
            }
            temp = (int)(root["main"]["temp"]) - 273.15; // get temperature in °C
        }
        http.end(); // close connection
        last_minute = minute_;
    }
}

void getDataConfig()
{
}
void update_ota(){
    const char* host = "esp";
    MDNS.begin(host);
    httpUpdater.setup(&httpServer);
    httpServer.begin();
    MDNS.addService("http", "tcp", 80);
    String txt = "Hello http://"+WiFi.localIP().toString()+"/update in your browser\n";
    draw_string(txt);
    while (1)
    {
        httpServer.handleClient();
        MDNS.update();
        if (intfired %3 ==2){
            break;
        }
    }
    
}