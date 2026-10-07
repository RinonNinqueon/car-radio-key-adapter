#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_brightness.h"

unsigned char menu_brightness_enc_left(unsigned char menu_item)
{
    if (menu_item > 0)
        return menu_item - 1;
    else
        return menu_item; 
}

unsigned char menu_brightness_enc_right(unsigned char menu_item)
{
    if (menu_item < 100)
        return menu_item + 1;
    else
        return menu_item;
}

unsigned char menu_brightness_buttons(unsigned char menu_item, unsigned char button)
{
    if (button == BUTTON_ENCODER)
    {
        if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            menu_write_brightness(menu_item);
            menu_enter(MENU_ROOT);
            
            buttons_clear_all_buttons();
            return MENU_ITEM_BRIGHTNESS;
        }
    }
    if (buttons_get_button_release(button))
        buttons_clear_button(button);
    
    return menu_item;
}

void menu_brightness_leds(unsigned char menu_item)
{
    menu_set_brightness_lut(menu_item);
}