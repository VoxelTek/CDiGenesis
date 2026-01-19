#include "console.h"
#include "gpio.h"

static const gpio_t RTS = {&PORTC, 0};

void initPins();