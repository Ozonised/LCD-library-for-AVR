#include "LiquidCrystalDisplay.h"

static bool lcdIsBusy(LiquidCrystalDisplay *lcd);
static void enable4bitMode(LiquidCrystalDisplay *lcd);
static void writeInst(LiquidCrystalDisplay *lcd, bool writeType, uint8_t data);


static void enable4bitMode(LiquidCrystalDisplay *lcd)
{
	*lcd->controlOutPort |= _BV(lcd->E);
	*lcd->dataOutPort |= _BV(lcd->D5) | _BV(lcd->D4);
	*lcd->controlOutPort &= ~_BV(lcd->E);
}

static bool lcdIsBusy(LiquidCrystalDisplay *lcd)
{
	bool busy_flag = false;
	
	*lcd->dataOutPort &= ~(_BV(lcd->D7) | _BV(lcd->D6) | _BV(lcd->D5) | _BV(lcd->D4));
	// data port as input
	*lcd->dataDirPort &= ~(_BV(lcd->D7) | _BV(lcd->D6) | _BV(lcd->D5) | _BV(lcd->D4));
	
	// read data
	*lcd->controlOutPort |= _BV(lcd->RW);
	*lcd->controlOutPort &= ~_BV(lcd->RS);
	
	*lcd->controlOutPort |= _BV(lcd->E);
	// reading the first 4 bits although we ignore all but D7(first)bit
	busy_flag = *lcd->dataInPort & _BV(lcd->D7);
	*lcd->controlOutPort &= ~_BV(lcd->E);
	
	_delay_us(1);
	// toggling E to read the last 4 bits, although we don't care about their value
	*lcd->controlOutPort |= _BV(lcd->E);
	_delay_us(1);
	*lcd->controlOutPort &= ~_BV(lcd->E);
	
	return busy_flag;
}

static void writeInst(LiquidCrystalDisplay *lcd, bool writeType, uint8_t data)
{
	// data pins D7 - D4 as output
	*lcd->dataDirPort |= _BV(lcd->D7) | _BV(lcd->D6) | _BV(lcd->D5) | _BV(lcd->D4);
	
	if (writeType)
	{
		// write data
		*lcd->controlOutPort &= ~_BV(lcd->RW);
		*lcd->controlOutPort |= _BV(lcd->RS);
	}
	else
	{
		// write instruction
		*lcd->controlOutPort &= ~(_BV(lcd->RW) | _BV(lcd->RS));
	}
	
	// writing data to pins D7 to D3
	for (int8_t i = 7; i >= 0; i--) {
		
		switch (i)
		{
			case 7:
			case 3:
			*lcd->controlOutPort |= _BV(lcd->E);
			
			if (BIT_READ(data, i))
			*lcd->dataOutPort |= _BV(lcd->D7);
			else
			*lcd->dataOutPort &= ~_BV(lcd->D7);
			break;
			
			case 6:
			case 2:
			if (BIT_READ(data, i))
			*lcd->dataOutPort|= _BV(lcd->D6);
			else
			*lcd->dataOutPort &= ~_BV(lcd->D6);
			break;
			
			case 5:
			case 1:
			if (BIT_READ(data, i))
			*lcd->dataOutPort |= _BV(lcd->D5);
			else
			*lcd->dataOutPort &= ~_BV(lcd->D5);
			break;
			
			case 4:
			case 0:
			if (BIT_READ(data, i))
			*lcd->dataOutPort |= _BV(lcd->D4);
			else
			*lcd->dataOutPort &= ~_BV(lcd->D4);
			
			*lcd->controlOutPort &= ~_BV(lcd->E);
			// enable pin minimum cycle time is 1uS
			_delay_us(1);
			break;
		}
	}
}

/**
* @brief initializes the LCD struct to ports used by the LCD
* @param *lcd pointer to lcd structure
* @param *ctrlDirPort pointer to DDRn to which RS, RW, RW, E pins are connected to
* @param *ctrlOutPort pointer to PORTn to which RS, RW, RW, E pins are connected to
* @param *dataDirPort pointer to DDRn to which pins D3-D7 are connected to
* @param *dataOutPort pointer to PORTn to which pins D3-D7 are connected to
* @param *dataInPort pointer to PINBn to which pins D3-D7 are connected to
*/
void lcdPortInit(LiquidCrystalDisplay *lcd, volatile uint8_t *ctrlDirPort, volatile uint8_t *ctrlOutPort, volatile uint8_t *dataDirPort, volatile uint8_t *dataOutPort, volatile uint8_t *dataInPort)
{
	lcd->controlDirPort = ctrlDirPort;
	lcd->controlOutPort = ctrlOutPort;
	
	lcd->dataDirPort = dataDirPort;
	lcd->dataOutPort = dataOutPort;
	lcd->dataInPort = dataInPort;
}

/**
* @brief initializes the port connected to the LCD, sets the LCD lines & enables 4-bit operation mode
* @param *lcd pointer to lcd structure
* @param RS-D7 pins connected to the LCD
*/
void lcdInit(LiquidCrystalDisplay *lcd, uint8_t no_of_columns, uint8_t no_of_rows, uint8_t RS, uint8_t RW, uint8_t E, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7)
{
	lcd->no_of_columns = no_of_columns;
	lcd->no_of_rows = no_of_rows;
	
	lcd->RS = RS;
	lcd->RW = RW;
	lcd->E = E;
	
	lcd->D4 = D4;
	lcd->D5 = D5;
	lcd->D6 = D6;
	lcd->D7 = D7;
	
	// control port as OUTPUT
	*lcd->controlDirPort |= _BV(lcd->RS) | _BV(lcd->RW) | _BV(lcd->E);
	*lcd->controlOutPort &= ~(_BV(lcd->RS) | _BV(lcd->RW) | _BV(lcd->E));
	
	// data port as OUTPUT
	*lcd->dataDirPort |= _BV(lcd->D7) | _BV(lcd->D6) | _BV(lcd->D5) | _BV(lcd->D4);
	*lcd->dataOutPort &= ~(_BV(lcd->D7) | _BV(lcd->D6) | _BV(lcd->D5) | _BV(lcd->D4));
	
	// we need to wait at least 40ms after VCC rises to 2.7volt
	// refer to page 46 of the data sheet
	_delay_ms(50);
	
	// enabling 4-bit mode, 8-bit is enabled by default
	// refer to page 42 table 12 of the data sheet
	// refer to page 46 for initialization by instruction
	
	enable4bitMode(lcd);
	// 	_delay_us(4200);
	// 	enable4bitMode(lcd);
	// 	_delay_us(4200);
	// 	enable4bitMode(lcd);
	// 	_delay_us(100);
	// 	enable4bitMode(lcd);
	
	while(lcdIsBusy(lcd));
	
	if (lcd->no_of_rows == 1)
	{
		// configuring the LCD as a 1 line display
		writeInst(lcd, _INST, _1LINE_DISPLAY);
	}
	else if (lcd->no_of_rows == 2)
	{
		// configuring the LCD as a 2 line display
		writeInst(lcd, _INST, _2LINE_DISPLAY);
	}
	lcdClearDisplay(lcd);
}

/**
* @brief settings for the LCD
* @param *lcd pointer to lcd structure
* @param display turns the display ON or OFF
* @param cursor turns the cursor ON or OFF
* @param blinkCursor enables(ON) and disables(OFF) the blinking of the cursor
*/
void lcdSetting(LiquidCrystalDisplay *lcd, bool display, bool cursor, bool blinkCursor)
{
	//refer to hitachi's data sheet page 24 table 6 for different instruction
	uint8_t inst = 0x08 | display << 2 | cursor << 1 | blinkCursor;
	
	while(lcdIsBusy(lcd));
	writeInst(lcd, _INST, inst);
}

/**
* @brief clears the entire display  removing all the contents and repositioning the cursor to the start position
* @param *lcd pointer to lcd structure
*/
void lcdClearDisplay(LiquidCrystalDisplay *lcd)
{
	while (lcdIsBusy(lcd));
	writeInst(lcd, _INST, _CLEAR_LCD);
}

/**
* @brief scrolls the entire display to the left as the cursor crosses the left most limit
* @param *lcd pointer to lcd structure
* @param autoScroll ON to enable & OFF to disable auto scroll
*/
void lcdAutoScroll(LiquidCrystalDisplay *lcd, bool autoScroll)
{
	while(lcdIsBusy(lcd));
	writeInst(lcd, _INST, autoScroll ? _AUTO_SCROLL_ON : _AUTO_SCROLL_OFF);
}

/**
* @brief shifts the entire display
* @param *lcd pointer to lcd structure
* @param dir direction of the shift(LEFT or RIGHT)
* @param n shifts display by n number of steps
*/
void lcdShiftDisplay(LiquidCrystalDisplay * lcd, bool dir, uint8_t n)
{
	while (n-- > 0)
	{
		while(lcdIsBusy(lcd));
		writeInst(lcd, _INST, dir ? _SHIFT_DISPLAY_RIGHT : _SHIFT_DISPLAY_LEFT);
	}
}

/**
* @brief shifts the cursor to the direction
* @param *lcd pointer to lcd structure
* @param dir direction of the shift(LEFT or RIGHT)
* @param n shifts display by n number of steps
*/
void lcdShiftCursor(LiquidCrystalDisplay *lcd, bool dir, uint8_t n)
{
	while(n-- > 0)
	{
		while(lcdIsBusy(lcd));
		writeInst(lcd, _INST, dir ? _SHIFT_CURSOR_RIGHT : _SHIFT_CURSOR_LEFT);
	}
}

/**
* @brief sets the cursor to the specified position
* @param *lcd pointer to lcd structure
* @param column column number starting from 0
* @param row row number starting from 0
*/
void lcdSetCursor(LiquidCrystalDisplay *lcd, uint8_t column, uint8_t row)
{
	uint8_t cursorPos = _ROW1_START_ADD * row + column;
	
	switch (lcd->no_of_rows)
	{
		// 1 line display
		case 1:
		if (cursorPos > _8x1LCD_END_ADD)
		cursorPos = _ROW0_START_ADD;  // revert to the start position
		break;
		
		// 2 line display
		case 2:
		switch (row)
		{
			case 0:
			// cursorPos is more than 7 then move the cursor to row 1's column 0
			if (cursorPos > _ROW0_END_ADD)
			cursorPos = _ROW1_START_ADD;		// move to row 1 & column 0
			break;
			
			case 1:
			if (cursorPos > _ROW1_END_ADD)
			cursorPos = _ROW0_START_ADD;		// move to home position,i.e, column 0 and row 0
			break;
			
			default:
			row = 0;
			break;
		}
		break;
	}
	
	while (lcdIsBusy(lcd));
	// cursor position | 0x80 ensures that D7 is high while setting DDRAM address
	// refer to table 6 on page 24
	writeInst(lcd, _INST, cursorPos | 0x80);
}

/**
* @brief sets the cursor to the home position
* @param *lcd pointer to lcd structure
*/
void lcdHomeCursor(LiquidCrystalDisplay *lcd)
{
	while(lcdIsBusy(lcd));
	writeInst(lcd, _INST, _HOME_CURSOR);
}

/**
* @brief writes a single character
* @param *lcd pointer to lcd structure
* @param c character to be printed
*/
void lcdWriteChar(LiquidCrystalDisplay *lcd, char c)
{
	while (lcdIsBusy(lcd));
	writeInst(lcd, _DATA, c);
}

/**
* @brief prints strings
* @param *lcd pointer to lcd structure
* @param str string to be printed
*/
void lcdPrintStr(LiquidCrystalDisplay *lcd, char *str)
{
	for (; *str != '\0'; str++)
	lcdWriteChar(lcd, *str);
}

/**
* @brief prints integers
* @param *lcd pointer to lcd structure
* @param num number to be printed
*/
void lcdPrintInt(LiquidCrystalDisplay *lcd, long num)
{
	if (num == 0) lcdWriteChar(lcd, '0');
	
	if (num < 0)
	{
		num *= -1;
		lcdWriteChar(lcd, '-');
	}
	
	long revNum = 0;		// stores num in reverse order
	uint8_t no_of_digits = 0;
	
	// reversing num and storing it into revNum
	while (num)
	{
		revNum = revNum * 10 + num % 10;
		num /= 10;
		++no_of_digits;
	}
	
	// printing the digits 
	// if revNum is 0 while no_of_digits is greater than 0 than the remaining digits are 0
	while (revNum || no_of_digits > 0)
	{
		lcdWriteChar(lcd, '0' + revNum % 10);
		revNum /= 10;
		--no_of_digits;
	}
}

/**
* @brief prints floating point number
* @param *lcd pointer to lcd structure
* @param num number to be printed
* @param precision number of digits after the decimal point
*/
void lcdPrintFloat(LiquidCrystalDisplay *lcd, float num, uint8_t precision)
{
	// Shifting the decimal point to the right by n times
	for (uint8_t i = 0; i < precision; i++) num *= 10;
	long i_num = num;
	
	if (i_num == 0) lcdWriteChar(lcd, '0');
	
	if (i_num < 0)
	{
		i_num *= -1;
		lcdWriteChar(lcd, '-');
	}
	
	long revNum = 0;
	uint8_t no_of_digits = 0;
	
	// reversing num and storing it into revNum
	while (i_num)
	{
		revNum = revNum * 10 + i_num % 10;
		i_num /= 10;
		++no_of_digits;
	}
	
	uint8_t pointPos = no_of_digits - precision;
	
	while (revNum)
	{
		if (pointPos-- == 0) lcdWriteChar(lcd, '.');
		
		lcdWriteChar(lcd, '0' + revNum % 10);
		revNum /= 10;
	}
}

/**
* @brief prints formatted output to the LCD analog to printf but with limitations
* @param *lcd pointer to lcd structure
* @param *fmt string to be formatted and printed (supports %d or %i, %f, %c & %s)
* @param ... arguments
*/
void lcdPrintf(LiquidCrystalDisplay *lcd, char *fmt, ...)
{
	va_list arg;
	
	double d_val;
	int i_val;
	char c_val;
	char *s_val;
	uint8_t f_precision = 0; // no of digits to print after the decimal point
	
	va_start(arg, fmt);
	
	for (char *p = fmt; *p; p++)
	{
		if (*p != '%')
		{
			lcdWriteChar(lcd, *p);
			continue;
		}
		
		if (*++p == '.')
		{
			while (isdigit(*++p)) f_precision = f_precision * 10 + *p - '0';
		}
		
		switch (*p)
		{
			case 'd':
			case 'i':
			i_val = va_arg(arg, int);
			lcdPrintInt(lcd, i_val);
			break;
			
			case 'f':
			d_val = va_arg(arg, double);
			// if floating point precision is not defined(precision = 0) then print 3 digits after the point
			lcdPrintFloat(lcd, d_val, f_precision ? f_precision : _DEFAULT_FLOAT_PRECISION);
			f_precision = 0;
			break;
			
			case 'c':
			c_val = va_arg(arg, int);
			lcdWriteChar(lcd, c_val);
			break;
			
			case 's':
			s_val = va_arg(arg, char*);
			lcdPrintStr(lcd, s_val);
			break;
			
			default:
			lcdWriteChar(lcd, *p);
			break;
		}
		
	}
	va_end(arg);
}