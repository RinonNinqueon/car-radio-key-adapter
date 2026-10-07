/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Steering Wheel Control Switch
Version : 1.0
Date    : 15.04.2025
Author  : Rinon Ninqueon
Company : Eltex
Comments: 


Chip type               : ATtiny24A
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 32
*******************************************************/

#include <tiny84.h>
#include <delay.h>

// I2C Bus functions
#include <i2c.h>

#include "SWCS.h"
#include "74hc595.h"
#include "encoder.h"
#include "buttons.h"
#include "leds.h"
#include "menu.h"
#include "pca9685.h"

// Declare your global variables here

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Reinitialize Timer1 value
//50ms
TCNT1H=0x3CB0 >> 8;
TCNT1L=0x3CB0 & 0xff;

//250ms
//TCNT1H=0x85EE >> 8;
//TCNT1L=0x85EE & 0xff;
// Place your code here
    leds_routine();
    menu_timer_routine();
}

// Pin change 0-7 interrupt service routine
interrupt [PC_INT0] void pin_change_isr0(void)
{
// Place your code here
    encoder_routine();
}

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=Out Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (0<<DDA3) | (1<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=1 Bit5=1 Bit4=1 Bit3=T Bit2=1 Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit3=1 Bit2=1 Bit1=1 Bit0=1 
PORTB=(1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000,000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 50 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x3C;
TCNT1L=0xB0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (1<<TOIE1);

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-7: On
// Interrupt on any change on pins PCINT8-11: Off
MCUCR=(0<<ISC01) | (0<<ISC00);
PCMSK0=(0<<PCINT7) | (0<<PCINT6) | (0<<PCINT5) | (0<<PCINT4) | (0<<PCINT3) | (0<<PCINT2) | (1<<PCINT1) | (1<<PCINT0);
GIMSK=(0<<INT0) | (0<<PCIE1) | (1<<PCIE0);
GIFR=(0<<INTF0) | (0<<PCIF1) | (1<<PCIF0);

// USI initialization
// Mode: Disabled
// Clock source: Register & Counter=no clk.
// USI Counter Overflow Interrupt: Off
USICR=(0<<USISIE) | (0<<USIOIE) | (0<<USIWM1) | (0<<USIWM0) | (0<<USICS1) | (0<<USICS0) | (0<<USICLK) | (0<<USITC);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR0=(0<<ADC1D) | (0<<ADC2D);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);


// Bit-Banged I2C Bus initialization
// I2C Port: PORTA
// I2C SDA bit: 6
// I2C SCL bit: 4
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();
delay_ms(10);
pca9685_init();
menu_init();
//encoder_code = encoder_read_gray_code();

// Global enable interrupts
#asm("sei")

while (1)
    {
        // Place your code here 
//        encoder_routine();
        buttons_routine();
        menu_routine();
        delay_ms(1);
    }
}
