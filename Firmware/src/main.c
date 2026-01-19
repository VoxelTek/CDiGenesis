#include "main.h"
#include "console.h"

int main() {
    initPins();
    console_init(1200);
}

uint16_t refreshButtonState() {
    
}

void initPins() {
    PORTA.DIRSET = 0b00000100;
    PORTA.DIRCLR = ~(0b00000100);
    /*
    PA0 <-- UPDI
    PA1 <-- D-Up
    PA2 <-- Btn A/B
    PA3 <-- D-Down
    PA4 <-- D-Left
    PA5 --> Select
    PA6 <-- D-Right
    PA7 <-- Btn Start/C
    */
}