#ifndef _LCD_H_
#define _LCD_H_

void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_displayString(const char* Str);
void LCD_displayCharacter(uint8_t data);
void LCD_Clear(void);

#endif
