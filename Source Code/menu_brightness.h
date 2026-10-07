#ifndef _MENU_BRIGHTNESS_H_
#define _MENU_BRIGHTNESS_H_

unsigned char menu_brightness_enc_left(unsigned char menu_item);
unsigned char menu_brightness_enc_right(unsigned char menu_item);
unsigned char menu_brightness_buttons(unsigned char menu_item, unsigned char button);
void menu_brightness_leds(unsigned char menu_item);

#endif /* _MENU_BRIGHTNESS_H_ */
