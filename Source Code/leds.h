#ifndef _LEDS_H_
#define _LEDS_H_

#define LEDS_COUNT          8
#define LED_BLINK_COUNT_ON  10
#define LED_BLINK_COUNT_OFF 5

#define LEDS_FLASH_STEPS        10
#define LEDS_FLASH_STEPS_MOD2   3
#define LEDS_MAX_BRIGHTNESS     100
#define LEDS_DEFAULT_BRIGHTNESS 90
#define LEDS_MIN_BRIGHTNESS     1

#define PIN_ILL     PINA
#define PORT_ILL    PORTA
#define LED_ILL     2

void leds_routine(void);
void leds_set_brightness(unsigned char value);
unsigned char leds_get_brightness(void);
void leds_set_on_off_blink(unsigned char on, unsigned char blink);
void leds_set_value_mode(unsigned char value);
void leds_set_flash_led(unsigned char led);
void leds_clr_flash_led(unsigned char led);
void leds_rst_flash_led(unsigned char led);

#endif /* _LEDS_H_ */
