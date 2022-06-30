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
	
	lcdPrintStr(&lcd, "Hello World!");
	
	_delay_ms(1500);
	
	// Places the cursor on the first column of the second row ,i.e, column 0 and row 1
	lcdSetCursor(&lcd, 0, 1);

	_delay_ms(1500);
	
	lcdPrintStr(&lcd, "Bye World!");
	
	_delay_ms(1500);
	
	// Places the cursor on the first column of the first row ,i.e, column 0 and row 0
	lcdHomeCursor(&lcd);
	
	_delay_ms(1500);
	
	// Places the cursor on column 10 of the first row
	lcdSetCursor(&lcd, 10, 0);
	
	_delay_ms(1500);
	
	// overwrites 'd' with 'l'
	lcdWriteChar(&lcd, 'l');
	
	_delay_ms(1500);
	
	// Shifts the cursor to the left by 5 position
	lcdShiftCursor(&lcd, LEFT, 5);
	
	_delay_ms(1500);
	
	lcdPrintStr(&lcd, " He");
	
	_delay_ms(1500);
	
	// Shifts the cursor to the right by 3 position
	lcdShiftCursor(&lcd, RIGHT, 3);
	
	// cursor blinking OFF
	lcdSetting(&lcd, ON, ON, OFF);
	
	while (1)
	{
	}
}

