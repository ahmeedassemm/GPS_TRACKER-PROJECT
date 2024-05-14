#include <stdint.h>
#include <stdio.h>

#include "LCD.h"
#include "SysTick.h"
#include "tm4c123gh6pm.h"

//RS->PB0
//E->PB2
//RW->GND
//D4-D7->PB4-PB7

//intializes lcd and port B
void LCD_init(void) {
	SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
	while ((SYSCTL_PRGPIO_R &= 0x00000002) == 0);/*waite to activate*/
	GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
	GPIO_PORTB_PCTL_R &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
	GPIO_PORTB_DIR_R |= 0xFF;         /* Configure PORTB as output pin */
	GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
	GPIO_PORTB_DEN_R |= 0xFF;         /* Enable Digital I/O onPORTB */
	GPIO_PORTB_DATA_R &= 0x0;         /* Clear data in PORT B */

	SysTick_Wait1ms(20);//delay 20ms
	LCD_sendCommand(0X33);//wakeup
	SysTick_Wait1ms(5);//DELAY 5mS
	LCD_sendCommand(0X32);//wakeup
	LCD_sendCommand(0X28); /* Select 4-bit Mode of LCD */
	LCD_sendCommand(0X06); /* clear whatever is written on display */
	LCD_sendCommand(0X01); /* shift cursor right */
	LCD_sendCommand(0X0F);  /* Enable Display and cursor blinking */
	LCD_sendCommand(0x02);
}

// send command to LCD
void LCD_sendCommand(uint8_t command) {
	GPIO_PORTB_DATA_R &= 0xFE;    /*Instruction Mode RS=0*/
	SysTick_Wait1ms(1);
	GPIO_PORTB_DATA_R |= 0X04;/*enable=1*/
	SysTick_Wait1ms(1);//delay 40us 
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
	GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | (command & 0xF0));
	SysTick_Wait1ms(1);
	GPIO_PORTB_DATA_R &= 0xFB;/*enable =0*/
	SysTick_Wait1ms(1);
	GPIO_PORTB_DATA_R |= 0X04;/*enable=1*/
	SysTick_Wait1ms(1);
	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | ((command << 4) & 0xF0));/*write data*/
	SysTick_Wait1ms(1);
	GPIO_PORTB_DATA_R &= 0xFB;/*enable =0*/
	SysTick_Wait1ms(1);
}

// send data as string
void LCD_displayString(const char* Str) {
	uint8_t i = 0;
	while (Str[i] != '\0') {
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

// send data as char
void LCD_displayCharacter(uint8_t data) {
	GPIO_PORTB_DATA_R |= 0x01; /* Instruction Mode RS=1 /write data to LCD so RW=0/ENABLE=0 */
	GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0x0F) | (data & 0xF0);
	GPIO_PORTB_DATA_R |= 0X04;/*enable=1*/
	SysTick_Wait1us(40);
	GPIO_PORTB_DATA_R &= 0xFB;/*enable =0*/
	GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | ((data << 4) & 0xF0));/*write data*/
	GPIO_PORTB_DATA_R |= 0X04;/*enable=1*/
	SysTick_Wait1us(40);
	GPIO_PORTB_DATA_R &= 0xFB;/*enable =0*/
	SysTick_Wait1us(40);
}

// clear the lcd values to write new one
void LCD_Clear() {
	LCD_sendCommand(1);//clear diplay
	LCD_sendCommand(0x80); /* LCD cursor location */
	SysTick_Wait1ms(500);
}

// Used to convert float numbers to string and diplay on the lcd 		
void LCD_displayfloat(float data) {
	char str[7];
	int i = 0;
	sprintf(str, "%f", data);//used to convert flaot to string
	LCD_sendCommand(1); /* clear display */
	LCD_sendCommand(0x80); /* LCD cursor location */

	while (str[i] != '\0') {
		LCD_displayCharacter(str[i]);
		i++;
	}
	SysTick_Wait1ms(500);//delay 500ms
}
