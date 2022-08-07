#ifndef _IOPORTS_H_
#define _IOPORTS_H_

#define LOW 0
#define HIGH 1

#define INPUT(port, pin) DDR##port &= ~(1 << pin)
#define OUTPUT(port, pin) DDR##port |= (1 << pin)
#define CLEAR(port, pin) PORT##port &= ~(1 << pin)
#define SET(port, pin) PORT##port |= (1 << pin)
#define TOGGLE(port, pin) PORT##port ^= (1 << pin)
#define READ(port, pin) (PIN##port & (1 << pin))

#define _VARFROMCOMB(x, y) x
#define _BITFROMCOMB(x, y) y

#define _INPUT(port, pin) INPUT(port, pin)
#define _OUTPUT(port, pin) OUTPUT(port, pin)
#define _CLEAR(port, pin) CLEAR(port, pin)
#define _SET(port, pin) SET(port, pin)
#define _TOGGLE(port, pin) TOGGLE(port, pin)
#define _READ(port, pin) READ(port, pin)

#define CINPUT(comb) _INPUT(_VARFROMCOMB(comb), _BITFROMCOMB(comb))
#define COUTPUT(comb) _OUTPUT(_VARFROMCOMB(comb), _BITFROMCOMB(comb))
#define CCLEAR(comb) _CLEAR(_VARFROMCOMB(comb), _BITFROMCOMB(comb))
#define CSET(comb) _SET(_VARFROMCOMB(comb), _BITFROMCOMB(comb))
#define CTOGGLE(comb) _TOGGLE(_VARFROMCOMB(comb), _BITFROMCOMB(comb))
#define CREAD(comb) _READ(_VARFROMCOMB(comb), _BITFROMCOMB(comb))

#endif