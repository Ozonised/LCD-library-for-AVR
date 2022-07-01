#include <avr/io.h>
#include "LiquidCrystalDisplay.h"

LiquidCrystalDisplay lcd;

// lcdPrintf() is similar to printf() in C but with limited features
// Note: lcdPrintf() does not support escape sequence characters like '\n', '\t', ..
// When printing integers both "%d" & "%i" are valid format specifiers
// Note that "%6d" or "%6i" is not supported
// When printing floats the precision can be set by specifying the field width:
// ".4f" prints 4 characters after the decimal point
// When no precision is defined ("%f") then lcdPrintf() by default will print 3 digits after the decimal point.
// The default precision can be changed by altering the value _DEFAULT_FLOAT_PRECISION macro in liquidCrystalDisplay.h 
// at line 45 
// "%.4f" & "%f" both work but "6.4f" doesn't

int main(void)
{
	float f_num1 = 15.6825, f_num2 = 4.6825;
	int i_num1 = 15, i_num2 = 250;
	char name[] = "Farhan";
	char c = 'i';
	
	// initializes the LCD object to the ports the control and data pins are connected to
	lcdPortInit(&lcd, &DDRB, &PORTB, &DDRD, &PORTD, &PIND);
	
	// initializes the LCD as a 16*2 character display and enables 4-bit mode
	lcdInit(&lcd, 16, 2, PB2, PB1, PB0, PD5, PD4, PD3, PD2);
	
	// turns the display ON, cursor ON and enables cursor blinking
	lcdSetting(&lcd, ON, ON, ON);
	
	// printing a single character
	
	lcdPrintf(&lcd, "H%c", c);
	
	_delay_ms(2500);
	
	lcdSetCursor(&lcd, 0, 1);
	
	// printing strings
	lcdPrintf(&lcd, "Name: %s", name);
	
	_delay_ms(2500);
	
	lcdClearDisplay(&lcd);
	
	lcdPrintf(&lcd, "Printing integer");
	
	lcdSetCursor(&lcd, 0, 1);
	
	lcdPrintf(&lcd, "%d + %d = %i", i_num1, i_num2, i_num2 + i_num1);
	
	_delay_ms(2500);
	
	lcdClearDisplay(&lcd);
	
	lcdPrintf(&lcd, "Printing floats");
	
	_delay_ms(2500);
	
	lcdClearDisplay(&lcd);
	
	// print floats with 3 digits of precision
	lcdPrintf(&lcd, "%f / %f", f_num1, f_num2);
	
	lcdSetCursor(&lcd, 0, 1);
	
	lcdPrintf(&lcd, "%f", f_num1 / f_num2);
	
	_delay_ms(2500);
	
	lcdClearDisplay(&lcd);
	
	lcdPrintf(&lcd, "Printing floats");
	
	_delay_ms(2500);
	
	lcdClearDisplay(&lcd)	;
	
	// prints the first and second argument with 4 digits of precision 
	lcdPrintf(&lcd, "%.4f / %.4f", f_num1, f_num2);
	
	lcdSetCursor(&lcd, 0, 1);
	
	// prints the result of the division with 2 digit of precision
	lcdPrintf(&lcd, "%.2f", f_num1 / f_num2);
	
	while (1)
	{
	}
}

