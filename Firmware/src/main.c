#include "main.h"
#include "console.h"

uint8_t buttonState = 0x0000;

int main() {
    initPins();
    while (!gpio_read(RTS)){

    }
    console_init(1200);
    // CDi serial init
    while (1) {
        loop();
    }
}

void loop() {
    while (!(USART0.STATUS & USART_DREIF_bm)) {

    }
    refreshButtonState();
}

void refreshButtonState() {
    gpio_set_low(SELECT);
    _delay_ms(2);
    buttonState = (~PORTA.IN & 0b11000000) + ((~PORTA.IN & 0b0001110) << 1);
    gpio_set_high(SELECT);
    _delay_ms(2);
    while ((PORTA.IN & 0b01010000)) {
        
    }
    buttonState += ((~PORTA.IN & 4) >> 2) + ((~PORTA.IN & 128) >> 7);
    gpio_set_low(SELECT);
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
    gpio_set_low(SELECT);
    /*
    PA0 <-- UPDI
    PA1 <-- /D-Up
    PA2 <-- /Btn A/B
    PA3 <-- /D-Down
    PA4 <-- /D-Left
    PA5 --> Select
    PA6 <-- /D-Right
    PA7 <-- /Btn Start/C
    */
}