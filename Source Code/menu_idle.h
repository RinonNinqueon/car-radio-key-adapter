#ifndef _MENU_IDLE_H_
#define _MENU_IDLE_H_

unsigned char menu_idle_enc_left(unsigned char menu_item);
unsigned char menu_idle_enc_right(unsigned char menu_item);
unsigned char menu_idle_buttons(unsigned char menu_item, unsigned char button);
void menu_idle_leds(unsigned char menu_item);

#endif /* _MENU_IDLE_H_ */
