#include "main.h"
#include "console.h"

uint8_t buttonState = 0x00;
uint8_t oldButtonState = 0x00;
int8_t speeds[6] = {0x7f, 0x60, 0x40, 0x30, 0x20, 0x10};
uint8_t speedIndex = 0;
bool speedChanged = false;
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

    if ((buttonState = oldButtonState) && !(buttonState & 0b00101110)) { // If no buttons have changed, AND no D-Pad movement, return.
        _delay_ms(20);
        return;
    }

    oldButtonState = buttonState;

    uint8_t b0 = 0b1000000;
	uint8_t b1 = 0b0000000;
	uint8_t b2 = 0b0000000;
    int8_t x = 0;
    int8_t y = 0;
    
    if (buttonState & 4) { // D-Pad up
        y = -speeds[speedIndex];
    }
    else if (buttonState & 16) { // D-Pad down
        y = speeds[speedIndex];
    }

    if (buttonState & 32) { // D-Pad left
        x = -speeds[speedIndex];
    }
    else if (buttonState & 64) { // D-Pad right
        x = speeds[speedIndex];
    }

    if (buttonState & 2) { // Button A, btn 1
        b0 |= 0b100000;
    }

    if (buttonState & 8) { // Button B, btn 2
        b0 |= 0b010000;
    }
        
    if (buttonState & 128) { // Button C, btn 1+2
        b0 |= 0b110000;
    }

    b0 |= ((y >> 4) & 0b1100) + (x >> 6);
    b1 |= (x & 0b111111);
    b2 |= (y & 0b111111);

    printf(b0);
    printf(b1);
    printf(b2);
    _delay_ms(5);
}

void initCDi() {
    _delay_ms(100);
    printf(mode);
}

void refreshButtonState() {
    gpio_set_high(SELECT); // Disable SELECT
    _delay_ms(2);
    buttonState = (~PORTA.IN & 0b11000000) + ((~PORTA.IN & 0b0001110) << 1); // Get D-Pad, B, C

    gpio_set_low(SELECT); // Enable SELECT
    _delay_ms(2);
    while ((PORTA.IN & 0b01010000)) { // Wait until D-Left and D-Right pressed
        
    }
    buttonState += ((~PORTA.IN & 4) >> 1) + ((~PORTA.IN & 128) >> 7); // Get A, Start
    gpio_set_high(SELECT); // Disable SELECT

    if ((buttonState & 1) && !speedChanged) { // Decrease speed value
        speedIndex = (speedIndex + 1) % 6;
        speedChanged = true;
    }
    else if (!(buttonState & 1) && speedChanged) { // Prevent rapid speed cycling
        speedChanged = false;
    }

    /*
    Bit 1 (1)   = START
    Bit 2 (2)   = A
    Bit 3 (4)   = D-Up
    Bit 4 (8)   = B
    Bit 5 (16)  = D-Down
    Bit 6 (32)  = D-Left
    Bit 7 (64)  = D-Right
    Bit 8 (128) = C
    */
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
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;

    gpio_input(RTS);

    gpio_output(SELECT);
    gpio_set_high(SELECT);
    /*
    PA0 <-- UPDI
    PA1 <-- /D-Up
    PA2 <-- /Btn B
    PA3 <-- /D-Down
    PA4 <-- /D-Left
    PA5 --> /SELECT
    PA6 <-- /D-Right
    PA7 <-- /Btn C
    */
}