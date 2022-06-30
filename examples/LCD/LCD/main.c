#include <avr/io.h>
#include "Driver/LiquidCrystalDisplay/LiquidCrystalDisplay.h"
#include <util/delay.h>

// Creating an liquid crystal display object
LiquidCrystalDisplay lcd;

int main(void)
{
	float f_num1 = 15.6825;
	float f_num2 = 4.6825;
	
	int i_num1 = 15;
	int i_num2 = 10;
	
	char greetings[] = "Hello, World!";
	char farewell[] = "Bye, World!";
	
	/*
		AVR mcu have 3 ports for input/output:
		> DDRn for setting the pin as INPUT or OUTPUT
		> PORTn for OUTPUT
		> PINn for INPUT
		lcdPortInit takes a pointer to the port the LCD's pins are connected to.
		The RS, RS, E, D7, D6, D4, D3 can all be connected to the same port or different.
		When using different PORT, the control pins(RS, RW, E) must be connected to one PORT while
		the data pins(D7, D6, D4, D3) must be connected to another PORT. The connection for the data pins
		and the control pins cannot be split between multiple port groups.
	*/
	
	// initializes the LCD object to the ports the control and data pins are connected to
	lcdPortInit(&lcd, &DDRD, &PORTD, &DDRC, &PORTC, &PINC);
	
	// initializes the LCD as a 16*2 character display and enables 4-bit mode
	lcdInit(&lcd, 16, 2, PD7, PD6, PD5, PC2, PC3, PC4, PC5);
	
	// turns the display ON, cursor ON and enables cursor blinking
	lcdSetting(&lcd, ON, ON, ON);
	
	// prints a string greetings
	lcdPrintStr(&lcd, greetings);
	
	// Sets cursor to column 0 and row1
	lcdSetCursor(&lcd, 0, 1);

	// prints the string farewell
	lcdPrintStr(&lcd, farewell);
	
	_delay_ms(1000);
	
	// shifts the display left by 4 steps
	lcdShiftDisplay(&lcd, LEFT, 4);
	
	_delay_ms(1000);
	
	// shifts the display right by 4 steps
	lcdShiftDisplay(&lcd, RIGHT, 4);
	
	_delay_ms(1000);
	
	// clears the entire screen
	lcdClearDisplay(&lcd);
	
	// disables the blinking cursor
	lcdSetting(&lcd, ON, ON, OFF);
	
	_delay_ms(1000);
	
	// prints the integer 20
	lcdPrintInt(&lcd, i_num1);
	
	_delay_ms(200);
	
	// prints a single character
	lcdWriteChar(&lcd, '+');
	
	_delay_ms(200);
	
	// prints an integer
	lcdPrintInt(&lcd, i_num2);
	
	_delay_ms(200);
	
	lcdPrintStr(&lcd, "Sum: ");
	lcdPrintInt(&lcd, i_num2 + i_num1);
	
	_delay_ms(1000);
	
	//sets the cursor to the home position (row0 and column 0)
	lcdHomeCursor(&lcd);
	
	_delay_ms(1000);
	
	// prints a floating point number with 4 digits after the decimal point
	lcdPrintFloat(&lcd, f_num1, 4);
	
	// prints a single character
	lcdWriteChar(&lcd, '/');
	
	lcdPrintFloat(&lcd, f_num2, 4);
	
	lcdPrintStr(&lcd, "Result: ");
	
	// if the precision argument is passed a zero then by default it prints 3 digits after the decimal point
	lcdPrintFloat(&lcd, f_num1 / f_num1, 0);
	
	
	while(1);
}

