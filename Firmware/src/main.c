#include "main.h"
#include "console.h"

uint8_t buttonState = 0x00;
uint8_t speed = 0x40; // Needs to be less than 128 (0x7F or less)
const uint8_t mode = MANEUVER;

int main() {
    initPins();
    while (!gpio_read(RTS)){

    }
    console_init(1200);
    initCDi();
    while (1) {
        loop();
    }
}

void loop() {
    /*
    while (!(USART0.STATUS & USART_DREIF_bm)) { // Wait for TX buffer to be empty

    }
    */
    refreshButtonState();

    uint8_t b0 = 0b1000000;
	uint8_t b1 = 0b0000000;
	uint8_t b2 = 0b0000000;
    
    
}

void initCDi() {
    _delay_ms(100);
    printf(mode);
}

void refreshButtonState() {
    gpio_set_high(SELECT); // Disable SELECT
    _delay_ms(2);
    buttonState = (~PORTA.IN & 0b11000000) + ((~PORTA.IN & 0b0001110) << 1); // Get D-Pad, B, C
    /*
    gpio_set_low(SELECT); // Enable SELECT
    _delay_ms(2);
    while ((PORTA.IN & 0b01010000)) { // Wait until L and R pressed
        
    }
    buttonState += ((~PORTA.IN & 4) >> 2) + ((~PORTA.IN & 128) >> 7); // Get A, Start
    gpio_set_high(SELECT); // Disable SELECT
    */
}

void initPins() {
    // Set pins to input
    PORTA.DIR = 0b00100000;
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
    PA2 <-- /Btn B/A
    PA3 <-- /D-Down
    PA4 <-- /D-Left
    PA5 --> Select
    PA6 <-- /D-Right
    PA7 <-- /Btn C/Start
    */
}