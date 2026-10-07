#ifndef _PCA9685_H_
#define _PCA9685_H_

#define  PCA9685_ADDRESS    0b10000000
#define  PCA9685_ALL_CALL   0b11100000
#define  PCA9685_SUB1_CALL  0b11100010
#define  PCA9685_SUB2_CALL  0b11100100
#define  PCA9685_SUB3_CALL  0b11101000
#define  PCA9685_RESET      0b00000110

#define PCA9685_REG_MODE1       0x00
#define PCA9685_REG_MODE2       0x01
#define PCA9685_REG_SUBADR1     0x02
#define PCA9685_REG_SUBADR2     0x03
#define PCA9685_REG_SUBADR3     0x04
#define PCA9685_REG_ALLCALLADR  0x05

#define PCA9685_REG_LED0_ON_L   0x06
#define PCA9685_REG_LED0_ON_H   0x07
#define PCA9685_REG_LED0_OFF_L  0x08
#define PCA9685_REG_LED0_OFF_H  0x09

#define PCA9685_REG_LED1_ON_L   0x0A
#define PCA9685_REG_LED1_ON_H   0x0B
#define PCA9685_REG_LED1_OFF_L  0x0C
#define PCA9685_REG_LED1_OFF_H  0x0D

#define PCA9685_REG_LED2_ON_L   0x0E
#define PCA9685_REG_LED2_ON_H   0x0F
#define PCA9685_REG_LED2_OFF_L  0x10
#define PCA9685_REG_LED2_OFF_H  0x11

#define PCA9685_REG_LED3_ON_L   0x12
#define PCA9685_REG_LED3_ON_H   0x13
#define PCA9685_REG_LED3_OFF_L  0x14
#define PCA9685_REG_LED3_OFF_H  0x15

#define PCA9685_REG_LED4_ON_L   0x16
#define PCA9685_REG_LED4_ON_H   0x17
#define PCA9685_REG_LED4_OFF_L  0x18
#define PCA9685_REG_LED4_OFF_H  0x19

#define PCA9685_REG_LED5_ON_L   0x1A
#define PCA9685_REG_LED5_ON_H   0x1B
#define PCA9685_REG_LED5_OFF_L  0x1C
#define PCA9685_REG_LED5_OFF_H  0x1D

#define PCA9685_REG_LED6_ON_L   0x1E
#define PCA9685_REG_LED6_ON_H   0x1F
#define PCA9685_REG_LED6_OFF_L  0x20
#define PCA9685_REG_LED6_OFF_H  0x21

#define PCA9685_REG_LED7_ON_L   0x22
#define PCA9685_REG_LED7_ON_H   0x23
#define PCA9685_REG_LED7_OFF_L  0x24
#define PCA9685_REG_LED7_OFF_H  0x25

#define PCA9685_REG_LED8_ON_L   0x26
#define PCA9685_REG_LED8_ON_H   0x27
#define PCA9685_REG_LED8_OFF_L  0x28
#define PCA9685_REG_LED8_OFF_H  0x29

#define PCA9685_REG_LED9_ON_L   0x2A
#define PCA9685_REG_LED9_ON_H   0x2B
#define PCA9685_REG_LED9_OFF_L  0x2C
#define PCA9685_REG_LED9_OFF_H  0x2D

#define PCA9685_REG_LED10_ON_L  0x2E
#define PCA9685_REG_LED10_ON_H  0x2F
#define PCA9685_REG_LED10_OFF_L 0x30
#define PCA9685_REG_LED10_OFF_H 0x31

#define PCA9685_REG_LED11_ON_L  0x32
#define PCA9685_REG_LED11_ON_H  0x33
#define PCA9685_REG_LED11_OFF_L 0x34
#define PCA9685_REG_LED11_OFF_H 0x35

#define PCA9685_REG_LED12_ON_L  0x36
#define PCA9685_REG_LED12_ON_H  0x37
#define PCA9685_REG_LED12_OFF_L 0x38
#define PCA9685_REG_LED12_OFF_H 0x39

#define PCA9685_REG_LED13_ON_L  0x3A
#define PCA9685_REG_LED13_ON_H  0x3B
#define PCA9685_REG_LED13_OFF_L 0x3C
#define PCA9685_REG_LED13_OFF_H 0x3D

#define PCA9685_REG_LED14_ON_L  0x3E
#define PCA9685_REG_LED14_ON_H  0x3F
#define PCA9685_REG_LED14_OFF_L 0x40
#define PCA9685_REG_LED14_OFF_H 0x41

#define PCA9685_REG_LED15_ON_L  0x42
#define PCA9685_REG_LED15_ON_H  0x43
#define PCA9685_REG_LED15_OFF_L 0x44
#define PCA9685_REG_LED15_OFF_H 0x45

#define PCA9685_REG_ALL_LED_ON_L    0xFA
#define PCA9685_REG_ALL_LED_ON_H    0xFB
#define PCA9685_REG_ALL_LED_OFF_L   0xFC
#define PCA9685_REG_ALL_LED_OFF_H   0xFD

#define PCA9685_REG_PRE_SCALE   0xFE
#define PCA9685_REG_TEST_MODE   0xFF

//---------------------------------------------

#define PCA9685_REG_BIT_ALLCALL     0
#define PCA9685_REG_BIT_SUB3        1
#define PCA9685_REG_BIT_SUB2        2
#define PCA9685_REG_BIT_SUB1        3
#define PCA9685_REG_BIT_SLEEP       4
#define PCA9685_REG_BIT_AI          5
#define PCA9685_REG_BIT_EXTCLK      6
#define PCA9685_REG_BIT_RESTART     7

#define PCA9685_REG_BIT_OUTNE0      0
#define PCA9685_REG_BIT_OUTNE1      1
#define PCA9685_REG_BIT_OUTDRV      2
#define PCA9685_REG_BIT_OCH         3
#define PCA9685_REG_BIT_INVRT       4

#define PCA9685_REG_BIT_LED_FULL_ON 4
#define PCA9685_REG_BIT_LED_FULL_OFF    4

#define PCA9685_FULL_ON             0x1000
#define PCA9685_FULL_OFF            0x1000

void pca9685_init(void);
void pca9685_set_prescaler(unsigned char value);

void pca9685_set_led_on(unsigned char led, unsigned int value);
void pca9685_set_led_off(unsigned char led, unsigned int value);
void pca9685_set_led_all_on(unsigned int value);
void pca9685_set_led_all_off(unsigned int value);

void pca9685_write_reg(unsigned char addr, unsigned char reg, unsigned char data);
void pca9685_write_reg16(unsigned char addr, unsigned char reg, unsigned int data);
void pca9685_write_reg16_16(unsigned char addr, unsigned char reg, unsigned int data1, unsigned int data2);

void pca9685_write_reg_start(unsigned char addr, unsigned char reg);
void pca9685_write_reg_continue(unsigned char data);
void pca9685_write_reg16_continue(unsigned int data);
void pca9685_write_reg_stop(void);

unsigned char pca9685_read_reg(unsigned char addr, unsigned char reg);

#endif /* _PCA9685_H_ */
