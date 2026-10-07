#ifndef _MENU_H_
#define _MENU_H_

// Menu Main
void menu_init(void);
void menu_routine(void);
//Timer
void menu_timer_start(void);
unsigned char menu_timer_is_off(void);
void menu_timer_routine(void);
//Menu Level
void menu_enter(unsigned char new_menu_level);
void menu_goto_idle(void);
void menu_goto_menu(void);
unsigned char menu_get_level(void);
//Brightness
void menu_set_brightness_lut(unsigned char value);
void menu_write_brightness(unsigned char value);
//Button
void menu_set_button_code_i2c(unsigned char button);
void menu_set_button_code_eeprom(unsigned char button, unsigned char code);
unsigned char menu_get_button_code(unsigned char button);

/*******************************************************
    IDLE <--> MENU
               ||
    0 Learning <---> Brightness <---> Button setup
         ||               ||                ||
    1 MENU_LEARNING  MENU_BRIGHTNESS  MENU_BUTTON_SELECT
                                            ||
    2 Button1 <--> Button2 <--> Button3 <--> EncoderR <--> EncoderBtn <--> EncoderL <--> Button4 <--> Button5 <--> Button6 <--> Button7
                                            ||
    3                                 MENU_BUTTON_CODE
*******************************************************/

#define MENU_ITEM_LEARNING      0
#define MENU_ITEM_BRIGHTNESS    1
#define MENU_ITEM_BUTTON_SELECT 2 

#define MENU_TIMER_LEARNING     60

enum programm_modes {
  MODE_IDLE,
  MODE_MENU,
};

enum menus {
  MENU_ROOT = 0,
  MENU_LEARNING = 1,
  MENU_BRIGHTNESS = 2,
  MENU_BUTTON_SELECT = 3,
  MENU_BUTTON_CODE = 4
};   

#endif /* _MENU_H_ */
