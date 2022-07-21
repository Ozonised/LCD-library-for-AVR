# LCD-library-for-AVR
A Liquid Crystal Display(LCD) library for AVR microcontrollers by Microchip. This library has been tested on ATmega 8 and ATmega328p mcu with a 16*2 lcd.
Check out the [examples](LCD-library-for-AVR/examples) directory, contains example code regarding various feaures, to get you started with this library.

# How to use:

## Supported displays: 
It supports 8 * 1, 8 * 2 and 16 * 2 lcd. 
### Note:
It does not support 20 * 4 character lcds yet.

# Features:
## 1. Printing Characters:
This library supports:
1. Printing single characters:  ``` lcdWriteChar() ```.
2. Printing strings: ``` lcdPrintStr() ``` or ``` lcdPrintf() ```.
3. Printing numbers: ``` lcdPrintInt() ``` for intgers, ``` lcdPrintfloat() ``` for floating point numbers or ``` lcdPrintf() ```.
### Note: 
``` lcdPrintf() ``` is analogous to ``` printf() ``` in C but with some limitations. It can be used in place of ``` lcdPrintStr() ```, ``` lcdPrintInt() ``` and
``` lcdPrintfloat() ```. Do keep in mind that it uses higher memory.

## 2. Display Control:
1. 

## 3. Cursor Control:
1. Configure the cursor i.e, enable the cursor and cursor blinking ON\OFF: ``` lcdSetting() ```.
2. Set cursor positon: ``` lcdSetCursor() ```.
