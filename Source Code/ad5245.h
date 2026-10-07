#ifndef _AD5245_H_
#define _AD5245_H_

#define AD5245_ADDRESS          0b01011000

#define AD5245_OK               0
#define AD5245_ERROR            100

#define AD5245_MIDPOINT         128

#define AD5245_WRITE            0x00
#define AD5245_RESET            0x40
#define AD5245_SHUTDOWN         0x20

void ad5245_write(unsigned char data);

#endif /* _AD5245_H_ */
