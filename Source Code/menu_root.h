#ifndef _MENU_ROOT_H_
#define _MENU_ROOT_H_

unsigned char menu_root_enc_left(unsigned char menu_item);
unsigned char menu_root_enc_right(unsigned char menu_item);
unsigned char menu_root_buttons(unsigned char menu_item, unsigned char button, unsigned char extra);
void menu_root_leds(unsigned char menu_item);

#endif /* _MENU_ROOT_H_ */
