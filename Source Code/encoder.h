#ifndef _ENCODER_H_
#define _ENCODER_H_

#define PIN_ENC1  1
#define PIN_ENC2  0

#define PINS_ENC1   PINA
#define PINS_ENC2   PINA

void encoder_routine(void);
unsigned char encoder_is_left(void);
unsigned char encoder_is_right(void);

#endif //_ENCODER_H_