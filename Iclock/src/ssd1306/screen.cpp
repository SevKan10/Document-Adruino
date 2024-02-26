#include "Arduino.h"
#include "screen.h"
#include <stdio.h>
#include <string.h>
char _time[3] = "00";
char *Lunar_year_table[] = {"Giap Ty", "At Suu", "Binh Dan", "Dinh Mao", "Mau Thin",
                            "Ky Ty", "Canh Ngo", "Tan Mui", "Nham Than", "Quy Dau",
                            "Giap Tuat", "At Hoi", "Binh Ty", " Dinh Suu", "Mau Dan",
                            "Ky Mao", "Canh Thin", "Tan Ty", "Nham Ngo", "Quy Mui",
                            "Giap Than", "At Dau", "Binh Tuat", "Dinh Hoi", "Mau Ty",
                            "Ky Suu", "Canh Dan", "Tan Mao", "Nham Thin", "Quy Ty",
                            "Giap Ngo", "At Mui", "Binh Than", "Dinh Dau", "Mau Tuat",
                            "Ky Hoi", "Canh Ty", "Tan Suu", "Nham Dan", "Quy Mao",
                            "Giap Thin", "At Ty", "Binh Ngo", " Dinh Mui", "Mau Than",
                            "Ky Dau", "Canh Tuat", "Tan Hoi", "Nham Ty", "Quy Suu",
                            "Giap Dan", "At Mao", "Binh Thin", "Dinh Ty", "Mau Ngo",
                            "Ky Mui", "Canh Than", "Tan Dau", "Nham Tuat", "Quy Hoi"};
void init_screen()
{
    ssd1306_128x64_i2c_init();
    ssd1306_flipVertical(0xC8);
    ssd1306_flipHorizontal(1);
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    ssd1306_clearScreen();
    ssd1306_displayOn();
}
void draw_screen_main(){
    ssd1306_clearScreen();
    ssd1306_drawXBitmap(0,0 , 128, 64, MAIN_bits);
    // ssd1306_setFixedFont(comic_sans_font24x32_123);
    // ssd1306_printFixed2x(0,  0, "Welcome!", STYLE_NORMAL);
}
void turn_off_screen(){
    ssd1306_displayOff();
}

void turn_on_screen(){
    ssd1306_displayOn();
}
void clear_screen(){
    ssd1306_clearScreen();
    ssd1306_displayOn();
}

void display_time(uint8_t hours,uint8_t minutes, uint8_t seconds){
    ssd1306_setFixedFont(comic_sans_font24x32_123);
    _time[0] = '0' + hours / 10;
    _time[1] = '0' + hours % 10;
    ssd1306_printFixed(4,  16, _time, STYLE_NORMAL);
    if (seconds & 1)
    {
        ssd1306_printFixed(50,  16, ":", STYLE_NORMAL);
    }
    else
    {
        ssd1306_printFixed(50,  16, " ", STYLE_NORMAL);
    }
    
    _time[0] = '0' + minutes / 10;
    _time[1] = '0' + minutes % 10;
    ssd1306_printFixed(72,  16, _time, STYLE_NORMAL);

    _time[0] = '0' + seconds / 10;
    _time[1] = '0' + seconds % 10;
    ssd1306_setFixedFont(font);
    ssd1306_printFixed(116,  36, _time, STYLE_NORMAL);

}

void draw_temp(uint8_t temp, uint8_t hum){
    ssd1306_setFixedFont(font);
    ssd1306_drawXBitmap(0,0 , 16, 16, TEMP_bits);
    // ssd1306_drawXBitmap(80,0 , 16, 16, HUM_bits);
    _time[0] = '0' + temp / 10;
    _time[1] = '0' + temp % 10;
    ssd1306_printFixed2x(20,0,_time,STYLE_NORMAL);
    // _time[0] = '0' + hum / 10;
    // _time[1] = '0' + hum % 10;
    // ssd1306_printFixed2x(100,0,_time,STYLE_NORMAL);
}
void draw_date(String wday, uint8_t day_, uint8_t month_){
    ssd1306_setFixedFont(font);
    ssd1306_printFixed(64,0,wday.c_str(),STYLE_NORMAL);
    _time[0] = '0' + day_ / 10;
    _time[1] = '0' + day_ % 10;
    ssd1306_printFixed(88,0,_time,STYLE_NORMAL);
    ssd1306_printFixed(104,0,"/",STYLE_NORMAL); 
    _time[0] = '0' + month_ / 10;
    _time[1] = '0' + month_ % 10;
    ssd1306_printFixed(112,0,_time,STYLE_NORMAL);
}
void draw_lunar_date(uint8_t lunar_day, uint8_t lunar_month, uint8_t lunar_year){
    String al = String(lunar_day)+"/"+String(lunar_month)+" "+String(Lunar_year_table[(((lunar_year) + 2000 - 3)%60)-1]);
    ssd1306_printFixed(48,8,al.c_str(),STYLE_NORMAL);
}
void notify(String mess, uint8_t i){
    String tmp = mess.substring(i)+" "+mess.substring(0,i);
    tmp = "News: "+tmp;
    ssd1306_printFixed_oldStyle(0,56,tmp.c_str(),STYLE_NORMAL);
}
void draw_ota_screen(int per){
    ssd1306_fillScreen(0x00);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_drawProgressBar(per);
}
void draw_string(String txt){
    clear_screen();
    ssd1306_printFixed_oldStyle(0,24,txt.c_str(),STYLE_NORMAL);
}