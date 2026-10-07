#include "SWCS.h"
#include "ad5245.h"
#include "buttons.h"
#include "encoder.h"
#include "leds.h"
#include "menu.h"
#include "menu_idle.h"
#include "menu_root.h"
#include "menu_learning.h"
#include "menu_brightness.h"
#include "menu_button_select.h"
#include "menu_button_code.h"

#include <delay.h>

eeprom unsigned char        eeprom_brightness;                                  //0-99
eeprom unsigned char        eeprom_button_codes[KEYS_ENC_COUNT + KEYS_COUNT];

static bit                  key_push;                                       //Set 1 to activate MOSFET in IDLE mode
static bit                  encoder_event;                                  //Set 1 when Encoder pressed in menu_set_button_code_i2c
static unsigned char        current_button;                                 //Current pressed button
static unsigned char        button_codes[KEYS_ENC_COUNT + KEYS_COUNT];      //Coder readed from EEPROM

static enum programm_modes  program_mode;                                   //Main mode
static unsigned char        menu_item;                                      //Curren menu item or value
static enum menus           menu_level;                                     //Menu item
static unsigned char        timer_counter;
static unsigned char        button_code;                                    //Code for pressed button in IDLE mode

#define TIMER_IS_OFF        (timer_counter == 0)

void menu_init(void)
{
    unsigned char i = 0;
    unsigned char eeprom_value;
                  
    //----Read-EEPROM-Brightness----
    do
    {
        eeprom_value = eeprom_brightness;        //eeprom read
        if (eeprom_value == 0xFF)     
        {
            eeprom_brightness = LEDS_DEFAULT_BRIGHTNESS-1;
            eeprom_value = LEDS_DEFAULT_BRIGHTNESS-1;
        }
        
        //----Init_LEDs----
        
        menu_set_brightness_lut(eeprom_value);
    }
    while(0);   //optimisation, don't store "code" int variable;

    //----Read-EEPROM-Button-Codes----
    //  0    1   2   3  4  5  6  7  8  9
    //ENC1 ENC2 ENC B1 B2 B3 B4 B5 B6 B7
    for (i = 0; i < KEYS_ENC_COUNT + KEYS_COUNT; i++)
    {
        eeprom_value = eeprom_button_codes[i];        //eeprom read
        if (eeprom_value == 0xFF)
        {
            button_codes[i] = i;
            eeprom_button_codes[i] = i;
        }
        else
            button_codes[i] = eeprom_value;
    }
    
    program_mode = MODE_IDLE;
    menu_level = MENU_ROOT;
}

void menu_routine(void)
{
    unsigned char button = 0;
    
    //------------ENCODER-----------
    if (encoder_is_left())
    {
        if (program_mode == MODE_IDLE)
           menu_item = menu_idle_enc_left(menu_item);
        else if (program_mode == MODE_MENU)
        {
            if (menu_level == MENU_ROOT)
                menu_item = menu_root_enc_left(menu_item);
            else if (menu_level == MENU_LEARNING)
                menu_item = menu_learning_enc_left(menu_item);
            else if (menu_level == MENU_LEARNING)
                menu_item = menu_brightness_enc_left(menu_item);
            else if (menu_level == MENU_BUTTON_SELECT)
                menu_item = menu_button_select_enc_left(menu_item);
            else if (menu_level == MENU_BUTTON_CODE)
                menu_item = menu_button_code_enc_left(menu_item);
        }
    }
    else if (encoder_is_right())
    {
        if (program_mode == MODE_IDLE)
            menu_item = menu_idle_enc_right(menu_item);
        else if (program_mode == MODE_MENU)
        {
            if (menu_level == MENU_ROOT)
                menu_item = menu_root_enc_right(menu_item);
            else if (menu_level == MENU_LEARNING)
                menu_item = menu_learning_enc_right(menu_item);
            else if (menu_level == MENU_LEARNING)
                menu_item = menu_brightness_enc_right(menu_item);
            else if (menu_level == MENU_BUTTON_SELECT)
                menu_item = menu_button_select_enc_right(menu_item);
            else if (menu_level == MENU_BUTTON_CODE)
                menu_item = menu_button_code_enc_right(menu_item);
        }
    }
    else
    {
    //------------BUTTONS-----------
        for (button = 0; button < KEYS_COUNT; button++)
        {
            if (program_mode == MODE_IDLE && !key_push)
                menu_level = menu_idle_buttons(menu_item, button);
            else if (program_mode == MODE_MENU)
            {
                if (menu_level == MENU_ROOT)
                    menu_level = menu_root_buttons(menu_item, button, eeprom_brightness);
                else if (menu_level == MENU_LEARNING && !key_push)
                    menu_level = menu_learning_buttons(menu_item, button);
                else if (menu_level == MENU_BRIGHTNESS)
                    menu_level = menu_brightness_buttons(menu_item, button);
                else if (menu_level == MENU_BUTTON_SELECT)
                    menu_level = menu_button_select_buttons(menu_item, button);
                else if (menu_level == MENU_BUTTON_SELECT)
                    menu_level = menu_button_code_buttons(menu_item, button);
            }
        }
    }
    
    //------------LEDS--------------
    if (program_mode == MODE_IDLE)
    {
        menu_idle_leds(menu_item);
    }
    else if (program_mode == MODE_MENU)
    {
        if (menu_level == MENU_ROOT)
            menu_root_leds(menu_item);
        else if (menu_level == MENU_LEARNING)
            menu_learning_leds(menu_level);
        else if (menu_level == MENU_BRIGHTNESS)
            menu_brightness_leds(menu_item);
        else if (menu_level == MENU_BUTTON_SELECT)
            menu_button_select_leds(menu_item);
        else if (menu_level == MENU_BUTTON_CODE)
            menu_button_code_leds(menu_item);
    }
    
    //------------PUSH--------------
    if (key_push == 1)                              //if need to push button
    {
        ad5245_write(button_code);                  //Set i2c resistance
        
        SetBit(PORT_PUSH, (1 << PIN_PUSH));
        delay_ms(10);                               //Button delay
        
        if (TIMER_IS_OFF)
        {
            if (encoder_event)                      //Encoder movement
            {                
                encoder_event = 0;
                key_push = 0;
            }                                       //Or button press
            else if (buttons_get_button_release(current_button))
            {
                buttons_clear_button(current_button);
                key_push = 0;
            }            
        }
    }
}

//---- Brightness ----

void menu_set_brightness_lut(unsigned char value)
{
    if (value < 100)
        leds_set_brightness(value);
}

void menu_write_brightness(unsigned char value)
{
    if (value < 100)
        eeprom_brightness = value;
}

//---- Timer ----

void menu_timer_routine(void)
{
    if (timer_counter > 0)
        timer_counter--;
}

void menu_timer_start(void)
{
    timer_counter = MENU_TIMER_LEARNING;
}

unsigned char menu_timer_is_off(void)
{
    if (TIMER_IS_OFF)
        return 1;
    else
        return 0;
}

//---- Menu ----

void menu_enter(unsigned char new_menu_level)
{
    menu_level = new_menu_level;    
}

void menu_goto_idle(void)
{
    program_mode = MODE_IDLE;
}

void menu_goto_menu(void)
{
    program_mode = MODE_MENU;
}

unsigned char menu_get_level(void)
{
    return menu_level;
}

//---- Buttons ----

//0, 1 -- encoder left/right
//2-9 -- buttons
void menu_set_button_code_i2c(unsigned char button)
{
    if (button >= KEYS_ENC_COUNT)
        current_button = button-KEYS_ENC_COUNT;
    else
        encoder_event = 1;
    button_code = button_codes[button];
    key_push = 1;
}

unsigned char menu_get_button_code(unsigned char button)
{
    if (button < KEYS_COUNT + KEYS_ENC_COUNT)
        return button_codes[button];
    else
        return 0;
}

void menu_set_button_code_eeprom(unsigned char button, unsigned char code)
{
    if (button < KEYS_COUNT + KEYS_ENC_COUNT)
    {
        button_codes[button] = code;
        eeprom_button_codes[button] = code;
    }
}