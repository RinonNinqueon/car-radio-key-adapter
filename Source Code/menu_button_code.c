#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_button_code.h"

unsigned char menu_button_code_enc_left(unsigned char menu_item)
{
    if (menu_item > 0)
        return menu_item - 1;
    else
        return menu_item; 
}

unsigned char menu_button_code_enc_right(unsigned char menu_item)
{
    if (menu_item < 0xFF)
        return menu_item + 1;
    else
        return menu_item;
}

unsigned char menu_button_code_buttons(unsigned char menu_item, unsigned char button)
{
    if (button == BUTTON_ENCODER)
    {
        if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            menu_enter(MENU_BUTTON_SELECT);
            buttons_clear_all_buttons();
            
            menu_set_button_code_eeprom(button, menu_item);            
            return MENU_ITEM_BUTTON_SELECT;
        }
    }/*
    else if (button == BUTTON_ONE)
    {
        if (buttons_get_button_long(button))
        {
            if (menu_item >= 100)
                menu_item -= 100;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            if (menu_item <= 0xFF - 100)
                menu_item += 100;
        }
    }
    else if (button == BUTTON_TWO)
    {
        if (buttons_get_button_long(button))
        {
            if (menu_item >= 10)
                menu_item -= 10;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            if (menu_item <= 0xFF - 10)
                menu_item += 10;
        }
    }
    else if (button == BUTTON_ONE)
    {
        if (buttons_get_button_long(button))
        {
            if (menu_item > 0)
                menu_item -= 1;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            if (menu_item < 0xFF)
                menu_item += 1;
        }
    }     */
    if (buttons_get_button_release(button))
        buttons_clear_button(button);
    
    return menu_item;
}

void menu_button_code_leds(unsigned char menu_item)
{
   leds_set_value_mode(menu_item);
}