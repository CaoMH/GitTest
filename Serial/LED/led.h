#include "sys.h"

#ifndef LED_H
#define LED_H
void LED_Init(void);
#define LED0 PAout(8)// PB5
#define LED1 PDout(2)// PE5	

#endif