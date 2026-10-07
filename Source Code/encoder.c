#include "SWCS.h"
#include "encoder.h"
#include "leds.h"

static unsigned char            encoder_code_prev, encoder_code_curr;
static bit                      encoder_left, encoder_right, stage_l, stage_r;

static unsigned char encoder_read_gray_code(void);

void encoder_routine(void)
{
    if (encoder_left || encoder_right)          //wait for handle
        return;
    
    encoder_code_curr = encoder_read_gray_code();
    
    if (encoder_code_curr != encoder_code_prev)
    {
        //11-01-00-10-11        
        if (!stage_l && encoder_code_prev == 0b11 && encoder_code_curr == 0b01) 
        {
            stage_l = 1;
        }
        else if (stage_l && encoder_code_prev == 0b00 && encoder_code_curr == 0b10)
        {
            stage_l = 0;
            encoder_left = 1;
        }               
        //11-10-00-01-11
        else if (!stage_r && encoder_code_prev == 0b10 && encoder_code_curr == 0b00) 
        {
            stage_r = 1;
        }
        else if (stage_r && encoder_code_prev == 0b01 && encoder_code_curr == 0b11)
        {
            stage_r = 0;
            encoder_right = 1;
        }
        else if (encoder_code_curr == 0b11)
        {
            stage_l = 0;
            stage_r = 0;
        }  
        encoder_code_prev = encoder_code_curr;
    }
}

static unsigned char encoder_read_gray_code(void) 
{ 
    unsigned char val = 0; 
    
    if (!TestBit(PINS_ENC1, 1 << PIN_ENC1)) 
        val |= 0b10; 
    if (!TestBit(PINS_ENC2, 1 << PIN_ENC2))
	    val |= 0b01;
  return val; 
}

unsigned char encoder_is_left(void)
{
    bit return_value = encoder_left;
    encoder_left = 0;
    return return_value;
}

unsigned char encoder_is_right(void)
{
    bit return_value = encoder_right;
    encoder_right = 0;
    return return_value;
}