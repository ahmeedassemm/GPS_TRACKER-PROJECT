#ifndef _UART_H
#define _UART_H

void UART0_Init(void);
char UART0_InChar(void);
void UART0_OutChar(char c);
void UART0_OutString(char* pt);
void UART2_Init(void);
char UART2_InChar(void);
void UART2_OutChar(char c);

#endif
