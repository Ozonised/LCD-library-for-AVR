#include <avr/io.h>
#include "LiquidCrystalDisplay.h"
#include <util/delay.h>

// Creating an liquid crystal display object
LiquidCrystalDisplay lcd;

int main(void)
{
	char farewell[] = "Bye, World!";
	
	// initializes the LCD object to the ports the control and data pins are connected to
	lcdPortInit(&lcd, &DDRB, &PORTB, &DDRD, &PORTD, &PIND);
	
	// initializes the LCD as a 16*2 character display and enables 4-bit mode
	lcdInit(&lcd, 16, 2, PB2, PB1, PB0, PD5, PD4, PD3, PD2);
	
	// turns the display ON, cursor ON and enables cursor blinking
	lcdSetting(&lcd, ON, ON, ON);
	
	// prints the string: "Hello,"
	lcdPrintStr(&lcd, "Hello,");
	
	_delay_ms(1000);
	
	// Places the cursor on the first column on the second row ,i.e, column 0 and row 1
	lcdSetCursor(&lcd, 0, 1);

	_delay_ms(1000);
	
	// prints the string: "World!"
	lcdPrintStr(&lcd, "World!");
	
	_delay_ms(2000);
	
	// clears the entire screen and repositions the cursor to the home position (column 0 and row 0)
	lcdClearDisplay(&lcd);
	
	// prints the string farewell
	lcdPrintStr(&lcd, farewell);
	
	while (1)
	{
	}
}

