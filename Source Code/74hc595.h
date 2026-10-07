#ifndef _74HC595_H_
#define _74HC595_H_

#define PIN_595_SHIFT   2
#define PIN_595_DATA    0
#define PIN_595_LATCH   1

#define PORT_595_SHIFT  PORTB
#define PORT_595_DATA   PORTB
#define PORT_595_LATCH  PORTB

void hc595_send_data8(unsigned char data);

#endif //_74HC595_H_