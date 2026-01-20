#include "main.h"
#include "console.h"

uint8_t buttonState = 0x00;
const int8_t speed = 0x40; // Needs to be less than 128 (0x7F or less)
const uint8_t mode = MANEUVER;

int main() {
    initPins();
    while (!gpio_read(RTS)) { // Wait for console ready

    }
    console_init(1200);
    initCDi();
    while (1) {
        loop();
    }
}

void loop() {
    refreshButtonState();

    uint8_t b0 = 0b1000000;
	uint8_t b1 = 0b0000000;
	uint8_t b2 = 0b0000000;
    int8_t x = 0;
    int8_t y = 0;
    
    if (buttonState & 1) { // D-Pad up
        y = speed;
    }
    else if (buttonState & 4) { // D-Pad down
        y = -speed;
    }
    
    if (buttonState & 2) { // Button B
        b0 |= 0b100000;
    }

    if (buttonState & 8) { // D-Pad left
        x = speed;
    }
    else if (buttonState & 16) { // D-Pad right
        x = -speed;
    }

    if (buttonState & 32) { // Button C
        b0 |= 0b010000;
    }

    b0 |= ((y >> 4) & 0b1100) + (x >> 6);
    b1 |= (x & 0b111111);
    b2 |= (y & 0b111111);

    printf(b0);
    printf(b1);
    printf(b2);    
}

void initCDi() {
    _delay_ms(100);
    printf(mode);
}

void refreshButtonState() {
    gpio_set_high(SELECT); // Disable SELECT
    _delay_ms(2);
    buttonState = ((~PORTA.IN & 0b01111110) >> 1); // Get D-Pad, B, C
}

void initPins() {
    // Set pins to input
    PORTA.DIR = 0b00000000;
    PORTA.DIRCLR = 0b01111110;
    // Set as pull-up
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;

    gpio_input(RTS);

    gpio_output(SELECT);
    gpio_set_high(SELECT);
    /*
    PA0 <-- UPDI
    PA1 <-- /D-Up
    PA2 <-- /Btn B
    PA3 <-- /D-Down
    PA4 <-- /D-Left
    PA5 <-- /D-Right
    PA6 <-- /Btn C
    */
}