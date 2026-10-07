#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_button_select.h"

unsigned char menu_button_select_enc_left(unsigned char menu_item)
{
    if (menu_item > 0)
        return menu_item - 1;
    else
        return menu_item; 
}

unsigned char menu_button_select_enc_right(unsigned char menu_item)
{
    if (menu_item < KEYS_COUNT + KEYS_ENC_COUNT - 1)
        return menu_item + 1;
    else
        return menu_item;
}

unsigned char menu_button_select_buttons(unsigned char menu_item, unsigned char button)
{
    if (button == BUTTON_ENCODER)
    {
        if (buttons_get_button_long(button))
        {
            menu_enter(MENU_ROOT);
            buttons_clear_all_buttons();
            return MENU_ITEM_BUTTON_SELECT;
        }
        else if (buttons_get_button_pressed(button) && buttons_get_button_release(button))
        {
            menu_enter(MENU_BUTTON_CODE);
            buttons_clear_all_buttons();
            
            /*
                menu_item   0 1 2 3 4 5 6 7 8 9
                button_name H M P < E > N 1 2 3
                button_id   2 3 4 0 5 1 6 7 8 9
                id          0 1 2 - 3 - 4 5 6 7
            */
            
            if (menu_item < BUTTON_ENCODER)                                                         //Left buttons
                return menu_get_button_code(menu_item + KEYS_ENC_COUNT);
            else if (menu_item == BUTTON_ENCODER)                                                  //Encoder left
                return menu_get_button_code(BUTTON_ENC_LEFT);
            else if (menu_item == BUTTON_ENCODER + 1)                                              //Encoder
                return menu_get_button_code(menu_item + KEYS_ENC_COUNT);
            else if (menu_item == BUTTON_ENCODER + 2)                                              //Encoder right
                return menu_get_button_code(BUTTON_ENC_RIGHT);
            else if (menu_item > BUTTON_ENCODER + KEYS_ENC_COUNT)                                  //Right buttons
                return menu_get_button_code(menu_item + KEYS_ENC_COUNT);
            return 0;
        }
    }
    if (buttons_get_button_release(button))
        buttons_clear_button(button);
    
    return menu_item;
}

void menu_button_select_leds(unsigned char menu_item)
{
    if (menu_item < BUTTON_ENCODER)                                                         //Left buttons
        leds_set_on_off_blink(1 << BUTTON_ENCODER, 1 << menu_item);                                //Encoder ON Button BLINK
    else if (menu_item == BUTTON_ENCODER)                                                  //Encoder left
        leds_set_on_off_blink(1 << BUTTON_ENCODER, (1 << BUTTON_ENCODER) | (1 << BUTTON_PREV));   //Encoder and Prev BLINK
    else if (menu_item == BUTTON_ENCODER + 1)                                              //Encoder
        leds_set_on_off_blink(1 << BUTTON_ENCODER, 1 << BUTTON_ENCODER);                           //Encoder BLINK
    else if (menu_item == BUTTON_ENCODER + 2)                                              //Encoder right
        leds_set_on_off_blink(1 << BUTTON_ENCODER, (1 << BUTTON_ENCODER) | (1 << BUTTON_NEXT));   //Encoder and Next BLINK
    else if (menu_item > BUTTON_ENCODER + KEYS_ENC_COUNT)                                  //Right buttons
        leds_set_on_off_blink(1 << BUTTON_ENCODER, (1 << menu_item - KEYS_ENC_COUNT));             //Encoder ON Button BLINK
}