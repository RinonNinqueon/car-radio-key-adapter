#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_root.h"

unsigned char menu_root_enc_left(unsigned char menu_item)
{
    if (menu_item > 0)
        return menu_item - 1;
    else
        return menu_item; 
}

unsigned char menu_root_enc_right(unsigned char menu_item)
{
    if (menu_item < 2)
        return menu_item + 1;
    else
        return menu_item;
}

unsigned char menu_root_buttons(unsigned char menu_item, unsigned char button, unsigned char extra)
{
    if (button == BUTTON_ENCODER)
    {
        if (buttons_get_button_long(button))
        {
            menu_goto_idle();
            buttons_clear_all_buttons();
            return 0;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            buttons_clear_all_buttons();
            if (menu_get_level() == MENU_ITEM_LEARNING)
            { 
                menu_enter(MENU_LEARNING);
                return 0;
            }
            else if (menu_get_level() == MENU_ITEM_BRIGHTNESS)
            { 
                menu_enter(MENU_BRIGHTNESS);
                return extra;
            }
            else if (menu_get_level() == MENU_ITEM_BUTTON_SELECT)
            { 
                menu_enter(MENU_BUTTON_SELECT);
                return 0;
            }
        }
    }
    return menu_item;
}

void menu_root_leds(unsigned char menu_item)
{
    leds_set_on_off_blink(1 << (menu_item) | (1 << BUTTON_ENCODER), 0);  //Encoder ON + Button ON
}