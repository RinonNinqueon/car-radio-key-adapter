#include "SWCS.h"
#include "pca9685.h"

#include <i2c.h>
#include <delay.h>

#define PCA9685_ON_VALUE    0

void pca9685_init(void)
{
    unsigned char reg;
//    pca9685_write_reg(PCA9685_REG_MODE1, (1 << PCA9685_REG_BIT_SLEEP) | (1 << PCA9685_REG_BIT_AI));
    pca9685_set_prescaler(0x1E);
    reg = pca9685_read_reg(PCA9685_ADDRESS, PCA9685_REG_MODE1);
    ClrBit(reg, 1 << PCA9685_REG_BIT_SLEEP);
    SetBit(reg, 1 << PCA9685_REG_BIT_AI);
    pca9685_write_reg(PCA9685_ADDRESS, PCA9685_REG_MODE1, reg);
    
//    reg = pca9685_read_reg(PCA9685_ADDRESS, PCA9685_REG_MODE2);
//    SetBit(reg, 1 << PCA9685_REG_BIT_OCH);
//    pca9685_write_reg(PCA9685_ADDRESS, PCA9685_REG_MODE2, reg);
    
    delay_ms(1);
    pca9685_set_led_all_on(PCA9685_ON_VALUE);
    pca9685_set_led_all_off(0);
}

void pca9685_set_prescaler(unsigned char value)
{
    pca9685_write_reg(PCA9685_ADDRESS, PCA9685_REG_PRE_SCALE, value);
}

void pca9685_set_led_on(unsigned char led, unsigned int value)
{
    pca9685_write_reg16(PCA9685_ADDRESS, PCA9685_REG_LED0_ON_L + led * 4, value);
}

void pca9685_set_led_off(unsigned char led, unsigned int value)
{
    if (value == 0x0FFF)
        pca9685_write_reg16_16(PCA9685_ADDRESS, PCA9685_REG_LED0_ON_L + led * 4, PCA9685_FULL_ON, 0);
    else if (value == 0x0000)
        pca9685_write_reg16_16(PCA9685_ADDRESS, PCA9685_REG_LED0_ON_L + led * 4, PCA9685_ON_VALUE, PCA9685_FULL_OFF);
    else
        pca9685_write_reg16_16(PCA9685_ADDRESS, PCA9685_REG_LED0_ON_L + led * 4, PCA9685_ON_VALUE, value);
}

void pca9685_set_led_all_on(unsigned int value)
{
    pca9685_write_reg(PCA9685_ALL_CALL, PCA9685_REG_ALL_LED_ON_L, value & 0xFF);
    pca9685_write_reg(PCA9685_ALL_CALL, PCA9685_REG_ALL_LED_ON_H, (value >> 8) & 0x1F);
}

void pca9685_set_led_all_off(unsigned int value)
{
    pca9685_write_reg(PCA9685_ALL_CALL, PCA9685_REG_ALL_LED_OFF_L, value & 0xFF);
    pca9685_write_reg(PCA9685_ALL_CALL, PCA9685_REG_ALL_LED_OFF_H, (value >> 8) & 0x1F);
}

void pca9685_write_reg(unsigned char addr, unsigned char reg, unsigned char data)
{   
    i2c_start();
    i2c_write(addr);
    i2c_write(reg);
    i2c_write(data);
    i2c_stop();
    delay_us(1);
}

void pca9685_write_reg16(unsigned char addr, unsigned char reg, unsigned int data)
{   
    i2c_start();
    i2c_write(addr);
    i2c_write(reg);
    i2c_write(data & 0xFF);
    i2c_write((data >> 8) & 0x1F);
    i2c_stop();
    delay_us(1);
}

void pca9685_write_reg16_16(unsigned char addr, unsigned char reg, unsigned int data1, unsigned int data2)
{   
    i2c_start();
    i2c_write(addr);
    i2c_write(reg);
    i2c_write(data1 & 0xFF);
    i2c_write((data1 >> 8) & 0x1F);
    i2c_write(data2 & 0xFF);
    i2c_write((data2 >> 8) & 0x1F);
    i2c_stop();
    delay_us(1);
}

void pca9685_write_reg_start(unsigned char addr, unsigned char reg)
{   
    i2c_start();
    i2c_write(addr);
    i2c_write(reg);
}

void pca9685_write_reg_continue(unsigned char data)
{   
    i2c_write(data);
}

void pca9685_write_reg16_continue(unsigned int data)
{   
    i2c_write(data & 0xFF);
    i2c_write((data >> 8) & 0x1F);
}

void pca9685_write_reg_stop(void)
{   
    i2c_stop();
    delay_us(1);
}

unsigned char pca9685_read_reg(unsigned char addr, unsigned char reg)
{
    unsigned char data;
    i2c_start();
    i2c_write(addr);
    i2c_write(reg);
    i2c_start();
    i2c_write(addr | 1);
    data = i2c_read(0);
    i2c_stop();
    return data;
}