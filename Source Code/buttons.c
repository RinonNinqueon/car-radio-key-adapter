#include "SWCS.h"
#include "buttons.h"
#include "leds.h"
#include "74hc595.h"

#include <delay.h>

static unsigned char    buttons_pressed;
static unsigned char    buttons_pressed_long;
static unsigned char    buttons_released;
static unsigned char    buttons_counter[KEYS_COUNT];

                                                        //   4  3  1  0  2  7  6  5
flash unsigned char     flash_buttons_mapping[KEYS_COUNT] = {4, 3, 1, 0, 2, 7, 6, 5};

void buttons_routine(void)
{
    unsigned char button = 0;
    for (button = 0; button < KEYS_COUNT; button++)
    {
        hc595_send_data8(~(1 << button));                                   //Send 0 to shift register
        delay_us(1);
        
        if (!TestBit(PIN_MATRIX, 1 << KEY_MATRIX_COM))                      //if pressed - 0
        {
            if (buttons_counter[button] == BUTTON_FILTER_COUNT)              //if over filter count
            {
                SetBit(buttons_pressed, 1 << button);                       //Set pressed
                leds_set_flash_led(button);
            }
                
            if (buttons_counter[button] < BUTTON_LONG_COUNT)                //Count till long press  
                buttons_counter[button]++;
            if (buttons_counter[button] >= BUTTON_LONG_COUNT)               //if pressed long
            {
                SetBit(buttons_pressed_long, 1 << button);                  //Set long press
                leds_rst_flash_led(button);
            }        
        }
        else                                                                //if released
        {
            if (buttons_counter[button] > BUTTON_FILTER_COUNT)              //restore filter to shord press
                buttons_counter[button] = BUTTON_FILTER_COUNT;
                
            if (buttons_counter[button] > 0)                                //Decrease till zero
                buttons_counter[button]--;
            if (buttons_counter[button] == 1)
            {
                leds_clr_flash_led(button);
                if (!TestBit(buttons_pressed, 1 << button) &&
                    !TestBit(buttons_pressed_long, 1 << button))            //we can clear before released be set
                    SetBit(buttons_released, 1 << button);                  //Set released
            }
        }
    }
}

unsigned char buttons_get_button_pressed(unsigned char button)
{
    return TestBit(buttons_pressed, 1 << flash_buttons_mapping[button]);
}

unsigned char buttons_get_button_long(unsigned char button)
{
    return TestBit(buttons_pressed_long, 1 << flash_buttons_mapping[button]);
}

unsigned char buttons_get_button_release(unsigned char button)
{
    return TestBit(buttons_released, 1 << flash_buttons_mapping[button]);
}

void buttons_clear_button(unsigned char button)
{
    ClrBit(buttons_pressed,      1 << flash_buttons_mapping[button]);
    ClrBit(buttons_pressed_long, 1 << flash_buttons_mapping[button]);
    ClrBit(buttons_released,     1 << flash_buttons_mapping[button]);
}

void buttons_clear_all_buttons(void)
{
    buttons_pressed = 0;
    buttons_pressed_long = 0;
    buttons_released = 0;
}