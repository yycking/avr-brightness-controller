/*
 * BRIGHTNESS.c
 *
 * Created: 2014/8/9
 *  Author:  yycking
 */ 

#define F_CPU 1000000UL
#define ADD_BRIGHTNESS _BV(PB3)
#define SUB_BRIGHTNESS _BV(PB4)
#define LED _BV(PB0)

#include <avr/io.h>
#include <util/delay.h>

int hasRelease(char button)
{
	_delay_us(20000);
	if ((PINB & button)==button)
	{
		_delay_us(20000);
		if ((PINB & button)==button)
			return 1;
	}
	return hasRelease(button);
}

int hasPress(char button)
{
	if ((PINB & button)==0)
	{
		_delay_us(20000);
		if ((PINB & button)==0){
			//return hasRelease(button);
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	PORTB |= LED | ADD_BRIGHTNESS | SUB_BRIGHTNESS;
	DDRB  = LED;  //set port PB0 output 
	
	TCCR0B |= _BV(CS01);
	TCCR0A |= _BV(WGM01) | _BV(WGM00) | _BV(COM0A1);
	
    char max = 25;
	char brightness = 13;
    while(1)
    {
		OCR0A = brightness*10;
        if (hasPress(ADD_BRIGHTNESS))
        {
	        if (brightness<max)
	        {
		        brightness++;
	        }
        }
        else if (hasPress(SUB_BRIGHTNESS))
        {
	        if (brightness>0)
	        {
		        brightness--;
	        }
        }
		_delay_us(500000);
    }
}