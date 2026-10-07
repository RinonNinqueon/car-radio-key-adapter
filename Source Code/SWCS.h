#ifndef _WCS_H_
#define _WCS_H_

#include <tiny44.h>

#define SetBit(x,y)     (x|=y)
#define ClrBit(x,y)     (x&=~(y))
#define TestBit(x,y)    (x&(y))
#define TestNBit(x,y)   (x&(~(y)))

#define PIN_PUSH  2
#define PORT_PUSH  PORTA

#endif //_WCS_H_