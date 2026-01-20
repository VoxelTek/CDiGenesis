#include "console.h"
#include "gpio.h"
#include "cdi.h"
#include <time.h>
#include <avr/delay.h>

static const gpio_t RTS     = {&PORTC, 0};
static const gpio_t SELECT  = {&PORTA, 5};

void loop();
void initCDi();
void initPins();
void refreshButtonState();