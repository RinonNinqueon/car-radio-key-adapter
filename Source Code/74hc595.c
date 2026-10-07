#include <delay.h>

#include "SWCS.h"
#include "74hc595.h"

void hc595_send_data8(unsigned char data)
{
    unsigned char i = 0;
    ClrBit(PORT_595_LATCH, 1 << PIN_595_LATCH);
    for (i = 8; i > 0; i--)
    {
        ClrBit(PORT_595_SHIFT, 1 << PIN_595_SHIFT);
        if (TestBit(data, 1 << (i - 1)))
            SetBit(PORT_595_DATA, 1 << PIN_595_DATA);
        else
            ClrBit(PORT_595_DATA, 1 << PIN_595_DATA);
        delay_us(10);
        
        SetBit(PORT_595_SHIFT, 1 << PIN_595_SHIFT);
        delay_us(10);
    }
    SetBit(PORT_595_LATCH, 1 << PIN_595_LATCH);
    delay_us(10);
}