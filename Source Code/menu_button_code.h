#ifndef _MENU_BUTTON_CODE_H_
#define _MENU_BUTTON_CODE_H_

unsigned char menu_button_code_enc_left(unsigned char menu_item);
unsigned char menu_button_code_enc_right(unsigned char menu_item);
unsigned char menu_button_code_buttons(unsigned char menu_item, unsigned char button);
void menu_button_code_leds(unsigned char menu_item);

#endif /* _MENU_BUTTON_CODE_H_ */
