#include "SWCS.h"
#include "ad5245.h"

#include <i2c.h>
#include <delay.h>

void ad5245_write(unsigned char data)
{   
    i2c_start();
    i2c_write(AD5245_ADDRESS);
    i2c_write(0x00);
    i2c_write(data);
    i2c_stop();
    delay_us(1);
}