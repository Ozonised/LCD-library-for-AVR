#ifndef LIQUIDCRYSTALDISPLAYH_
#define LIQUIDCRYSTALDISPLAYH_

#include <avr/io.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <ctype.h>
#include <util/delay.h>

#define BIT_READ(data, bit) (data & _BV(bit))
#define ON true
#define OFF false

#define LEFT 0
#define RIGHT 1

#define _INST 0
#define _DATA 1

#define _CLEAR_LCD 0x01U
#define _SHIFT_DISPLAY_RIGHT 0x1CU
#define _SHIFT_DISPLAY_LEFT 0x18U

#define _AUTO_SCROLL_ON 0x07U
#define _AUTO_SCROLL_OFF 0x05U

#define _HOME_CURSOR 0x02U
#define _SHIFT_CURSOR_RIGHT 0x14U
#define _SHIFT_CURSOR_LEFT 0x10U

#define _1LINE_DISPLAY 0x20U
#define _2LINE_DISPLAY 0x28U

// DDRAM address corresponds to cursor address
#define _ROW0_START_ADD 0x00U
#define _ROW1_START_ADD 0x40U
//8x1 lcd
#define _8x1LCD_END_ADD 0x4FU
// 2 line display
#define _ROW0_END_ADD 0x27U
#define _ROW1_END_ADD 0x67U

// no. of digits to print after the decimal point
#define _DEFAULT_FLOAT_PRECISION 3U

typedef struct {
	uint8_t no_of_columns;
	uint8_t no_of_rows;
	
	volatile uint8_t *controlDirPort;
	volatile uint8_t *controlOutPort;
	uint8_t RS;
	uint8_t RW;
	uint8_t E;
	
	volatile uint8_t *dataDirPort;
	volatile uint8_t *dataOutPort;
	volatile uint8_t *dataInPort;
	uint8_t D4;
	uint8_t D5;
	uint8_t D6;
	uint8_t D7;
	
} LiquidCrystalDisplay;

void lcdPortInit(LiquidCrystalDisplay *lcd, volatile uint8_t *ctrlDirPort, volatile uint8_t *ctrlOutPort, volatile uint8_t *dataDirPort, volatile uint8_t *dataOutPort, volatile uint8_t *dataInPort);
void lcdInit(LiquidCrystalDisplay *lcd, uint8_t no_of_columns, uint8_t no_of_rows, uint8_t RS, uint8_t RW, uint8_t E, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7);
void lcdSetting(LiquidCrystalDisplay *lcd, bool display, bool cursor, bool blinkCursor);

void lcdSetCursor(LiquidCrystalDisplay *lcd, uint8_t column, uint8_t row);
void lcdHomeCursor(LiquidCrystalDisplay *lcd);
void lcdShiftCursor(LiquidCrystalDisplay *lcd, bool dir, uint8_t n);

void lcdClearDisplay(LiquidCrystalDisplay *lcd);
void lcdAutoScroll(LiquidCrystalDisplay *lcd, bool autoScroll);
void lcdShiftDisplay(LiquidCrystalDisplay * lcd, bool dir, uint8_t n);

void lcdWriteChar(LiquidCrystalDisplay *lcd, char c);
void lcdPrintStr(LiquidCrystalDisplay *lcd, char *str);
void lcdPrintInt(LiquidCrystalDisplay *lcd, long num);
void lcdPrintFloat(LiquidCrystalDisplay *lcd, float num, uint8_t precision);
void lcdPrintf(LiquidCrystalDisplay *lcd, char *fmt, ... );

#endif /* LIQUID CRYSTAL DISPLAY_H_ */