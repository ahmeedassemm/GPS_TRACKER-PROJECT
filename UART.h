#ifndef _UART_H
#define _UART_H

void UART0_Init(void);
void UART0_OutChar(char c);
void UART0_OutString(char* pt);
void UART2_Init(void);
char UART2_InChar(void);

#endif

