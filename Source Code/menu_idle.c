#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_idle.h"

unsigned char menu_idle_enc_left(unsigned char menu_item)
{
    menu_set_button_code_i2c(BUTTON_ENC_LEFT);
    return menu_item; 
}

unsigned char menu_idle_enc_right(unsigned char menu_item)
{
    menu_set_button_code_i2c(BUTTON_ENC_RIGHT);
    return menu_item;
}

unsigned char menu_idle_buttons(unsigned char menu_item, unsigned char button)
{
    if (button == BUTTON_ENCODER)               //Special event for menu button -- check for press and release!
    {
        if (buttons_get_button_long(button))   //Enter menu
        {
            menu_goto_menu();
            menu_enter(MENU_ROOT);
            buttons_clear_all_buttons();
            return 0;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))  //Обязательно отслеживаем отпускание, потому что Press -> Long <--> Release
            menu_set_button_code_i2c(button + KEYS_ENC_COUNT);       //Short press - as usuall button
    }
    else if (buttons_get_button_pressed(button))
        menu_set_button_code_i2c(button + KEYS_ENC_COUNT);

    return menu_item;
}

void menu_idle_leds(unsigned char menu_item)
{
    return; //nothing
}
