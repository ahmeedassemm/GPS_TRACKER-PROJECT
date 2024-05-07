#include <stdint.h>

#include "UART.h"
#include "SysTick.h"

// for gps
void UART2_INIT() {
	SYSCTL_RCGCUART_R |= 0X04; // activate UART2
	SYSCTL_RCGCGPIO_R |= 0X08; //  activate port D

	UART2_CTL_R &= ~(0X0001);   // disable UART
	UART2_IBRD_R = 104;
	UART2_FBRD_R = 11;

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;  // Unlock port D
	GPIO_PORTD_CR_R |= 0xC0;  // Allow changes to PD7-PD6
	GPIO_PORTD_AFSEL_R |= 0XC0; // enable alt function PD7, PD6
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0X00FFFFFF) | 0X11000000; // configure uart for pa0,pa1

	UART2_CC_R = 0; 	   // use system clock
	UART2_LCRH_R = 0x60; // 8-bit word length, no Fifo , no parity, 1 stop bit
	UART2_CTL_R = 0X0301;  // enable RXE,TXE AND UART

	GPIO_PORTD_DEN_R |= 0XC0;  // enable digital IO on PD6,PD7
	GPIO_PORTD_AMSEL_R &= ~0XC0; // disable analog function on PD6, PD7

	SysTick_Wait1ms(1);
}

void UART0_INIT() {
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

	UART0_CTL_R &= ~UART_CTL_UARTEN;
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF) | (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~0x03;
}

void UART0_send_byte(uint8_t c) {
	while ((UART0_FR_R & 0x20) != 0);
	UART0_DR_R = c;
}

void UART0_output_string(char* s) {
	while (*s) {
		UART0_send_byte(*s);
		s++;
	}
}

void UART2_send_byte(uint8_t c) {
	while ((UART2_FR_R & 0x20) != 0);
	UART2_DR_R = c;
}

uint8_t UART2_read_byte(void) {
	while ((UART2_FR_R & 0x10) != 0);
	return (uint8_t)(UART2_DR_R & 0xFF);
}

void UART0_send_byte(char data) {
	while ((UART0_FR_R & UART_FR_TXFF) == UART_FR_TXFF);
	UART0_DR_R = data;
}

void UART0_output_string(char* c){
	while(*c){
		UART0_send_byte(*c);
		c++;
	}
}
