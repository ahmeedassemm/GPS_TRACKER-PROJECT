#include "tm4c123gh6pm.h"
#include "UART.h"
//pc
void UART0_Init(void) {
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;// activate UART0
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;//  activate port A

	UART0_CTL_R &= ~UART_CTL_UARTEN;// disable UART
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN); //8bit data,FIFO enabled
	UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	//PA0 = U0RX, PA1 = U0TX
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF) |
		(GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~0x03;
}

void UART0_OutChar(char c) {
	while ((UART0_FR_R & 0x20) != 0); //check FIFO not full
	UART0_DR_R = c;
}

void UART0_OutString(char* pt) {
	while (*pt) {
		UART0_OutChar(*pt);
		pt++;
	}
}

// for gps
void UART2_Init(void) {
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2;  // activate UART2
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;  //  activate port D

	UART2_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	UART2_IBRD_R = 104;
	UART2_FBRD_R = 11;

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;  // Unlock port D
	GPIO_PORTD_CR_R |= 0xC0;            // Allow changes to PD7-PD6
	GPIO_PORTD_AFSEL_R |= 0XC0;         // enable alt function PD7, PD6
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0X00FFFFFF) | 0X11000000;  // configure uart for pa0,pa1

	UART2_CC_R = 0;        // use system clock
	UART2_LCRH_R = 0x60;   // 8-bit word length, no Fifo , no parity, 1 stop bit
	UART2_CTL_R = 0X0301;  // enable RXE,TXE AND UART

	GPIO_PORTD_DEN_R |= 0XC0;     // enable digital IO on PD6,PD7
	GPIO_PORTD_AMSEL_R &= ~0XC0;  // disable analog function on PD6, PD7
}

char UART2_InChar(void) {
	char c;

	while ((UART2_FR_R & 0x10) != 0);
	c = UART2_DR_R;
	return c;
}