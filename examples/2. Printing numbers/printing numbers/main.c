#include <avr/io.h>
#include <util/delay.h>
#include "LiquidCrystalDisplay.h"

LiquidCrystalDisplay lcd;

int main(void)
{
	float f_num1 = 15.6825, f_num2 = 4.6825;
	int i_num1 = 15, i_num2 = 250;
	
	// initializes the LCD object to the ports the control and data pins are connected to
	lcdPortInit(&lcd, &DDRB, &PORTB, &DDRD, &PORTD, &PIND);
	
	// initializes the LCD as a 16*2 character display and enables 4-bit mode
	lcdInit(&lcd, 16, 2, PB2, PB1, PB0, PD5, PD4, PD3, PD2);
	
	// turns the display ON, cursor ON and enables cursor blinking
	lcdSetting(&lcd, ON, ON, ON);
	
	/************************************************************************/
	/*						  Printing integers                             */
	
	lcdPrintStr(&lcd, "Printing integer");
	
	// Places the cursor on the first column on the second row ,i.e, column 0 and row 1
	lcdSetCursor(&lcd, 0, 1);
	
	// prints the integer i_num1
	lcdPrintInt(&lcd, i_num1);
	
	// prints a single character
	lcdWriteChar(&lcd, '+');
	
	// prints the integer i_num2
	lcdPrintInt(&lcd, i_num2);
	
	lcdWriteChar(&lcd, '=');
	
	lcdPrintInt(&lcd, i_num2 + i_num1);
	
	/************************************************************************/
	
	_delay_ms(2000);
	
	// clears the entire screen and repositions the cursor to the home position
	lcdClearDisplay(&lcd);
	
	/************************************************************************/
	/*                     Printing floats                                  */
	
	lcdPrintStr(&lcd, "Printing floats");
	
	_delay_ms(2000);
	
	lcdClearDisplay(&lcd);
	
	// prints a floating point number with 4 digits after the decimal point
	lcdPrintFloat(&lcd, f_num1, 4);
	
	// prints a single character
	lcdWriteChar(&lcd, '/');
	
	lcdPrintFloat(&lcd, f_num2, 4);
	
	// Places the cursor on the first column on the second row ,i.e, column 0 and row 1
	lcdSetCursor(&lcd, 0, 1);
	
	lcdPrintStr(&lcd, "Result: ");
	
	// prints a floating point number with 3 digits after the decimal point
	lcdPrintFloat(&lcd, (f_num1 / f_num2), 3);
	
	/************************************************************************/
	
	
	while (1)
	{
	}
}

