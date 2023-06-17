#include "menu.h"



char display[17];
static uint32_t pageInitTick = 0;
menuStat_t menuStat = menu_mainPage;

void menu_init(void){
    // LCD_Clear();
    set_menu(menu_starting);
}
menuStat_t get_menuStat(void){
    return menuStat;
}
void set_menu(menuStat_t menu){
    menuStat = menu;
    menu_initPage(menu);
}
void menu_initPage(menuStat_t stat){
    LCD_Clear();

    switch(stat){
        case menu_starting:
            LCD_Init();
            
            heart_beat_init(500);

            keypad_init(FALLING_EDGE);

            mq5_init(200);
            dht11_init(250);

            // RTC_Init();

            // uart_init();
            _delay_ms(100);
            
            LCD_String_xy(0, 0, "Starting...");
            pageInitTick = get_currentTick();
            break;
        case menu_mainPage:
            sprintf(display, "1.Stat   2.Timer");
            LCD_String_xy(0, 0, display);
            sprintf(display, "3.SetUp");
            LCD_String_xy(1, 0, display);
            break;
        case menu_mainPage_Stat:
            sprintf(display, "T:  %c   H:  %c   ", 223, 37);
            LCD_String_xy(0, 0, display);
            sprintf(display, "CO2:            ");
            LCD_String_xy(1, 0, display);
            break;
        case menu_mainPage_Timer:
            sprintf(display, "Watering time:");
            LCD_String_xy(0, 0, display);
            sprintf(display, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
            LCD_String_xy(1, 0, display);
            break;
        case menu_mainPage_SetUp:
            sprintf(display, "1.Time");
            LCD_String_xy(0, 0, display);
            sprintf(display, "2.SensorSense");
            LCD_String_xy(1, 0, display);
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }
}
void menu_loop(void){
    uint32_t currTick = 0;
    currTick = get_currentTick();

    menuStat_t stat = get_menuStat();
    switch(stat){
        case menu_starting:
            if(pageInitTick + 2000 < currTick){
                pageInitTick = 2000 + currTick;
                set_menu(menu_mainPage);
            }
            break;
        case menu_mainPage:
            break;
        case menu_mainPage_Stat:
            dht11_loop();
            mq5_loop();
            break;
        case menu_mainPage_Timer:
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }
}
