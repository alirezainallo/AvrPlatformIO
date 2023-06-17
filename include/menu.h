#ifndef _MENU_H
#define _MENU_H

#include "LCD.h"
#include "mq5.h"
#include "main.h"
#include "DHT11.h"
#include "timTick.h"
#include "keypad_4x4.h"
#include "heart_beat.h"

// typedef enum menuStat_tag{
//     menu_starting = 0,
//     menu_mainPage,
//     menu_mainPage_Stat,
//     menu_mainPage_Timer,
//     menu_mainPage_SetUp,
//     menu_processGsm,
//     menu_displayTime,
//     menu_displaySensor,
//     menu_changeClock,
//     menu_setRtcAlarm,
// }menuStat_t;

void menu_init(void);
void menu_initPage(menuStat_t stat);
void set_menu(menuStat_t menu);
menuStat_t get_menuStat(void);
void menu_loop(void);

#endif //_MENU_H
