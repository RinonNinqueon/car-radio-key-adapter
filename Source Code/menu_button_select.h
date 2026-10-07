#ifndef _MENU_BUTTON_SELECT_H_
#define _MENU_BUTTON_SELECT_H_

unsigned char menu_button_select_enc_left(unsigned char menu_item);
unsigned char menu_button_select_enc_right(unsigned char menu_item);
unsigned char menu_button_select_buttons(unsigned char menu_item, unsigned char button);
void menu_button_select_leds(unsigned char menu_item);

#endif /* _MENU_BUTTON_SELECT_H_ */
