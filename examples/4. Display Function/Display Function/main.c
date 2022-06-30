#include <avr/io.h>
#include "LiquidCrystalDisplay.h"
#include <util/delay.h>

LiquidCrystalDisplay lcd;

int main(void)
{
	// initializes the LCD object to the ports the control and data pins are connected to
	lcdPortInit(&lcd, &DDRB, &PORTB, &DDRD, &PORTD, &PIND);
	
	// initializes the LCD as a 16*2 character display and enables 4-bit mode
	lcdInit(&lcd, 16, 2, PB2, PB1, PB0, PD5, PD4, PD3, PD2);
	
	// turns the display ON, cursor ON and enables cursor blinking
	lcdSetting(&lcd, ON, ON, ON);
	
	lcdPrintStr(&lcd, "Hello world!");
	
	_delay_ms(1500);
	
	// shifts the display to the left by 5 steps
	lcdShiftDisplay(&lcd, LEFT, 5);
	
	_delay_ms(1500);
	
	// shifts the display to the right by 5 steps
	lcdShiftDisplay(&lcd, RIGHT, 5);
	
	_delay_ms(1500);
	
	// turns the display OFF
	lcdSetting(&lcd, OFF, ON, ON);
	
	_delay_ms(1500);
	
	// turns the display ON
	lcdSetting(&lcd, ON, ON, ON);
	
	// Clears the entire screen and repositions the cursor to the home position ,i.e, column 0 and row 0
	lcdClearDisplay(&lcd);
	
	_delay_ms(1500);
	
	lcdPrintStr(&lcd, "Bye world!");
	while (1)
	{
	}
}

