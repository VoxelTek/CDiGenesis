#include "console.h"
#include "gpio.h"

static const gpio_t RTS     = {&PORTC, 0};
static const gpio_t SELECT  = {&PORTA, 5};

void loop();
void initPins();
void refreshButtonState();