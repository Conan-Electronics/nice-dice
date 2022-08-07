#include <avr/io.h>
#include <util/delay.h>
#include "ioports.h"

int num;

#define LED B, 2

int main(void) {
    COUTPUT(LED);
    CCLEAR(LED);
    while (1) {
        CTOGGLE(LED);
        _delay_ms(500);
    }

    return 0;
}