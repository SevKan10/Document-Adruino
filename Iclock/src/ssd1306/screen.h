#ifndef _SCREEN_H
#define _SCREEN_H

#include "Arduino.h"
#include "icon.h"
#include "font.h"
#include "ssd1306.h"
#define ADDRESS_OLED 0x3C
#define SCL_PIN A5
#define SDA_PIN A4

#define TIME_OFF_SCREEN 10000

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128


enum _INDEX_PAGE {
    MAIN_SCREEN =0,
    DOWNLOAD_SCREEN =1,
    INFO_SCREEN =2,
    FLASHING_SCREEN =111,
    CONNECT_PC_SCREEN =4,
    LIST_FIRMWARE_SCREEN =11,
    CHIP_INFO =14,
    ERROR_FLASHING_SCREEN =114,
    DETAIL_HELP_INFO_SCREEN = 22,
    ERASING_FLASH = 5,
};

void init_screen();
void turn_off_screen();
void turn_on_screen();
void clear_screen();
void display_time(uint8_t hours,uint8_t minutes, uint8_t seconds);
void draw_temp(uint8_t temp, uint8_t hum);
void draw_date(String wday, uint8_t day_, uint8_t month_);
void draw_lunar_date(uint8_t lunar_day, uint8_t lunar_month, uint8_t lunar_year);
void notify(String mess, uint8_t i);
void draw_screen_main();
void draw_ota_screen(int per);
void draw_string(String txt);
#endif