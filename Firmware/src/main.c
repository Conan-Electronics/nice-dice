#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "ioports.h"

#define SHR_DATA B, 0
#define SHR_CLCK B, 1
#define SHR_LATCH B, 2
#define SHR_ENABLE B, 3

#define BUTTON B, 4

#define DIGIT_COUNT 6

uint8_t digits[DIGIT_COUNT] = {
    0b00000100,
    0b01000010,
    0b01000110,
    0b11001010,
    0b11001110,
    0b11111010};

uint8_t digit = 0;

void shr_write(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << (7 - i))) {
            CSET(SHR_DATA);
        } else {
            CCLEAR(SHR_DATA);
        }
        CSET(SHR_CLCK);
        CCLEAR(SHR_CLCK);
    }

    CSET(SHR_LATCH);
    CCLEAR(SHR_LATCH);
}

void next_digit() {
    digit = (digit + 1) % 6;
    shr_write(digits[digit]);
}

int main(void) {
    // Init shift register
    COUTPUT(SHR_DATA);
    COUTPUT(SHR_CLCK);
    COUTPUT(SHR_ENABLE);
    COUTPUT(SHR_LATCH);
    CSET(SHR_ENABLE);

    // Init button
    CINPUT(BUTTON);

    unsigned int seed = 0;
    while (CREAD(BUTTON)) {
        seed++;
    }
    srand(seed);
    CCLEAR(SHR_ENABLE);

    while (1) {
        // Roll the dice
        digit = rand() % 6;
        for (uint8_t waits = 0; waits < 10; waits++) {
            next_digit();
            _delay_ms(100);
        }
        for (int8_t delay = 4; delay < 16; delay++) {
            next_digit();
            for (uint8_t waits = 0; waits < delay; waits++) {
                _delay_ms(25);
            }
        }

        // Blink Animation
        _delay_ms(300);
        CSET(SHR_ENABLE);
        _delay_ms(50);
        CCLEAR(SHR_ENABLE);
        for (int8_t i = 0; i < 6; i++) {
            CTOGGLE(SHR_ENABLE);
            _delay_ms(400);
        }

        // Wait for button press
        while (CREAD(BUTTON)) {
        }
    }

    return 0;
}