#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_learning.h"

unsigned char menu_learning_enc_left(unsigned char menu_item)
{
    menu_set_button_code_i2c(BUTTON_ENC_LEFT);
    menu_timer_start();
    return BUTTON_ENC_LEFT; 
}

unsigned char menu_learning_enc_right(unsigned char menu_item)
{
    menu_set_button_code_i2c(BUTTON_ENC_RIGHT);
    menu_timer_start();
    return BUTTON_ENC_RIGHT;
}

unsigned char menu_learning_buttons(unsigned char menu_item, unsigned char button)
{
    if (button == BUTTON_ENCODER)               //Special event for menu button -- check for press and release!
    {
        if (buttons_get_button_long(button))   //Enter menu
        {
            menu_enter(MENU_ROOT);
            buttons_clear_all_buttons();
            return MENU_ITEM_LEARNING;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            menu_set_button_code_i2c(button + KEYS_ENC_COUNT);      //Short press - as usuall button
            return button + KEYS_ENC_COUNT;
        }
    }
    else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
    {
        menu_set_button_code_i2c(button + KEYS_ENC_COUNT);
        return button + KEYS_ENC_COUNT;
    }
    
    return menu_item;
}

void menu_learning_leds(unsigned char menu_item)
{
    if (menu_timer_is_off())    //Select mode
        leds_set_on_off_blink(0xFF, 0xFF);  //All ON, all BLINK
    else                        //On Learning
    {
        leds_set_on_off_blink(0xFF, 1 << menu_item);                                    //All ON, one BLINK
        if (menu_item == BUTTON_ENC_LEFT)                                               //Encoder left
            leds_set_on_off_blink(0xFF, (1 << BUTTON_ENCODER) | (1 << BUTTON_PREV));    //All ON, Encoder and Prev BLINK
        else if (menu_item == BUTTON_ENC_RIGHT)                                         //Encoder right
            leds_set_on_off_blink(0xFF, (1 << BUTTON_ENCODER) | (1 << BUTTON_NEXT));    //All ON, Encoder and Next BLINK
        else                                                                            //Buttons
            leds_set_on_off_blink(0xFF, (1 << menu_item - KEYS_ENC_COUNT));             //All ON, Button BLINK
    }        
}