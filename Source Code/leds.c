#include "SWCS.h"
#include "buttons.h"
#include "leds.h"
#include "pca9685.h"

enum led_states {
    LED_OFF,
    LED_ON,
	LED_BLINK,
};

static unsigned char    leds_brightness;                //0-255
static unsigned char    leds_flash;                     //flash bit mask
static unsigned char    leds_leds_brightness[LEDS_COUNT];//actual leds brightness
static enum led_states  leds_state[LEDS_COUNT];         //on/off/blink
static unsigned char    led_register;                   //on/off bit mask
static unsigned char    leds_blink_register;            //blink bit mask
static unsigned char    leds_blink_counter;             //for blinking
static unsigned char    leds_blink_value;               //value for display as blinking
static bit              leds_blink_value_mode;          //set 1 to blink value
static bit              leds_blink_signal;              //blink signal
static unsigned char    leds_blink_value_counter = 1;   //blink mode digit counter

flash unsigned char     flash_leds_mapping[LEDS_COUNT] = {7, 6, 5, 0, 4, 3, 2, 1};
flash unsigned int      gamma_lut[100] = {
     0,   0,   2,   4,   7,  10,  15,  20,  27,  34,  42,  51,  60,  71,  82,  94,
   107, 121, 135, 151, 167, 184, 202, 221, 241, 261, 282, 305, 328, 351, 376, 402,
   428, 455, 483, 512, 541, 572, 603, 635, 669, 702, 737, 773, 809, 846, 884, 923,
   963,1003,1045,1087,1130,1174,1218,1264,1310,1357,1406,1454,1504,1555,1606,1658,
  1711,1765,1820,1876,1932,1989,2047,2106,2166,2227,2288,2350,2413,2477,2542,2608,
  2674,2741,2809,2878,2948,3019,3090,3162,3236,3310,3384,3460,3536,3614,3692,3771,
  3851,3931,4013,4095,};

static void led_turn_on(unsigned char led);
static void led_turn_off(unsigned char led);
static unsigned char leds_change_brightness(unsigned char led);

// ---- Main routine for loop ----
void leds_routine(void)
{
    unsigned char i = 0;
    unsigned char temp = 0;

    if (leds_blink_value_mode)
    {
        if (leds_blink_signal)
        {
            led_turn_on(BUTTON_ENCODER);
            
            temp = leds_blink_value / 100;             
            if (temp >= leds_blink_value_counter)
                led_turn_on(BUTTON_ONE);
            else
                led_turn_off(BUTTON_ONE);
                
            temp = (leds_blink_value / 10) % 10;            
            if (temp >= leds_blink_value_counter)
                led_turn_on(BUTTON_TWO);
            else
                led_turn_off(BUTTON_TWO);
            
            temp = leds_blink_value % 10;            
            if (temp >= leds_blink_value_counter)
                led_turn_on(BUTTON_THREE);
            else
                led_turn_off(BUTTON_THREE);

            if (leds_blink_value_counter <= 12)
                leds_blink_value_counter++;
            else
                leds_blink_value_counter = 1;
        }
        else
        {
            led_turn_off(BUTTON_ENCODER);
            led_turn_off(BUTTON_ONE);
            led_turn_off(BUTTON_TWO);
            led_turn_off(BUTTON_THREE);
        }        
    }
    else
    {
        for (i = 0; i < LEDS_COUNT; i++)
        {
            if (leds_state[i] == LED_OFF)
                led_turn_off(i);
            else if (leds_state[i] == LED_ON)
                led_turn_on(i);
            else if (leds_state[i] == LED_BLINK && leds_blink_signal)
            {
                if (TestBit(leds_blink_register, 1 << i))
                {
                    led_turn_off(i);
                    ClrBit(leds_blink_register, 1 << i);
                }
                else
                {
                    led_turn_on(i);
                    SetBit(leds_blink_register, 1 << i);
                }
            }        
        }
        
    }
    
    if (leds_blink_counter < LED_BLINK_COUNT_ON)
    {                        
        leds_blink_signal = 0;
        leds_blink_counter++;
    }
    else if (leds_blink_counter == LED_BLINK_COUNT_OFF)
    {
        leds_blink_signal = 1;
    }
    else
    {
        leds_blink_signal = ~leds_blink_signal;
        leds_blink_counter = 1;
    }
}

//---- Main external LEDs control functions ---- 

void leds_set_on_off_blink(unsigned char on, unsigned char blink)
{
    unsigned char i = 0;
    for (i = 0; i < LEDS_COUNT; i++)
    {
        if (TestBit(blink, 1 << i))
            leds_state[i] = LED_BLINK;
        else
        {
             if (TestBit(on, 1 << i))
                leds_state[i] = LED_ON;
            else
                leds_state[i] = LED_OFF;
        }
    }
    leds_blink_value_mode = 0;
}

void leds_set_value_mode(unsigned char value)
{
    leds_blink_value_mode = 1;
    
    if (leds_blink_value != value)
    {
        leds_blink_value = value;
        leds_blink_value_counter = 0;
    }
}

//---- Main internal LEDs control functions ----

static void led_turn_on(unsigned char led)
{
    unsigned char new_brightness;
    
    if (led < LEDS_COUNT)
    {
        new_brightness = leds_change_brightness(led);     
        if (!TestBit(led_register, 1 << led) || (new_brightness != leds_leds_brightness[led]))
        {
            leds_leds_brightness[led] = new_brightness;
            pca9685_set_led_off(flash_leds_mapping[led], gamma_lut[leds_leds_brightness[led]]);
            SetBit(led_register, 1 << led);
        }
    }
}

static void led_turn_off(unsigned char led)
{
    if (led < LEDS_COUNT)
    {
        if (TestBit(led_register, 1 << led))
        {
            pca9685_set_led_off(flash_leds_mapping[led], 0);
            ClrBit(led_register, 1 << led);
        }
    }
}

//---- Brightness ----
void leds_set_brightness(unsigned char value)
{
    if (value < LEDS_MAX_BRIGHTNESS && leds_brightness != value)
    {
        leds_brightness = value;
        led_register = 0;
    }
}

unsigned char leds_get_brightness(void)
{
    return leds_brightness;
}

/******************************************************
           ---- LEDs Flashing ----
           
    Press - leds_set_flash_led
        ѕоднимает €ркость до LEDS_FLASH_BRIGHTNESS
    Longpress - leds_rst_flash_led
        —бивает €ркость до leds_brightness
        » поднимает до LEDS_FLASH_BRIGHTNESS
    Release - leds_clr_flash_led
        ќпускает €ркость до leds_brightness
******************************************************/

static unsigned char leds_change_brightness(unsigned char led)
{
    unsigned char led_flash_brightness;
    unsigned char led_regular_brightness;
    
    //Boundary check
    if (led >= LEDS_COUNT)
        return leds_brightness;
    
    //Set brightness for pressed button
    if (TestBit(PIN_ILL, LED_ILL))
    {
        led_flash_brightness = LEDS_MIN_BRIGHTNESS + LEDS_FLASH_STEPS;      //ILL Off
        led_regular_brightness = LEDS_MIN_BRIGHTNESS;
    }
    else if (leds_brightness < LEDS_MAX_BRIGHTNESS - LEDS_FLASH_STEPS)
    {
        led_flash_brightness = leds_brightness + LEDS_FLASH_STEPS;          //ILL On
        led_regular_brightness = leds_brightness;
    }
    else
    {   
        led_flash_brightness = LEDS_MAX_BRIGHTNESS;                         //ILL On
        led_regular_brightness = leds_brightness;
    }
    
    //Flashing
    if (TestBit(leds_flash, 1 << led))
    {
        if (leds_leds_brightness[led] < led_flash_brightness)
            return leds_leds_brightness[led] + 1;
        else
            return led_flash_brightness;
    }
    //Flashing is off, regular operation
    else
    {
        if (leds_leds_brightness[led] > led_regular_brightness)         //flash --> idle OR on --> off
            return leds_leds_brightness[led] - 1;
        else if (leds_leds_brightness[led] < led_regular_brightness)    //off --> on
            return leds_leds_brightness[led] + 1;
//      else
//          return leds_leds_brightness[led] что равно led_regular_brightness
    }
    
    return leds_leds_brightness[led];
}

void leds_set_flash_led(unsigned char led)
{
    if (led < LEDS_COUNT)
        SetBit(leds_flash, 1 << led);
}

void leds_clr_flash_led(unsigned char led)
{
    if (led < LEDS_COUNT)
        ClrBit(leds_flash, 1 << led);
}

void leds_rst_flash_led(unsigned char led)
{
    if (led < LEDS_COUNT)
        leds_leds_brightness[led] = leds_brightness;
}