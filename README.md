# LCD-library-for-AVR
A Liquid Crystal Display(LCD) library for 8 * 1, 8 * 2 and 16 * 2 lcd for AVR microcontrollers by Microchip. This library has been tested on ATmega8 and ATmega328p mcu with a 16*2 lcd.
A list of supported display is given below. Check out the [examples](/examples) directory, contains example code on the various features, to get you started with this library.

# How to use:
1. Include the liquidCrystalDisplay.h and liquidCrystalDisplay.c in your project directory.
2. 

## Supported displays: 
It supports 8 * 1, 8 * 2 and 16 * 2 lcd. 
### Note:
It does not support 20 * 4 character lcds yet.

# Features:
This library supports:
## 1. Printing Characters:
1. Printing single characters:  ``` lcdWriteChar() ```.
2. Printing strings: ``` lcdPrintStr() ``` or ``` lcdPrintf() ```.
3. Printing numbers: ``` lcdPrintInt() ``` for intgers, ``` lcdPrintfloat() ``` for floating point numbers or ``` lcdPrintf() ```.

### Note: 
``` lcdPrintf() ``` is analogous to ``` printf() ``` in C but with some limitations. It can be used in place of ``` lcdPrintStr() ```, ``` lcdPrintInt() ``` and
``` lcdPrintfloat() ```. Do keep in mind that it uses higher memory.

## 2. Display Control:
1. Configure the display i.e. turn the display ON or OFF: ``` lcdSetting() ```.
2. Shift the entire display left or right without changing the screen contents: ``` lcdShiftDisplay() ```.
3. Clear the contents on the screen and reposition the cursor to the home position i.e. column 0 and row 0: ``` lcdClearDisplay() ```.

## 3. Cursor Control:
1. Configure the cursor i.e. enable the cursor and cursor blinking ON\OFF: ``` lcdSetting() ```.
2. Set cursor positon: ``` lcdSetCursor() ```.

## Note: 
Details on how to use the functions listed above along with code examples can be found in the [examples](/examples) directory.
