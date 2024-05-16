#ifndef _GPIO_H_
#define _GPIO_H_

#define GPIO_RED_LED 2
#define GPIO_GREEN_LED 8
#define GPIO_BLUE_LED 4
#define GPIO_ALL_LEDS 14

// switch 1 is pressed
#define SW1 !(GPIO_PORTF_DATA_R & 0x10)
// switch 2 is pressed
#define SW2 !(GPIO_PORTF_DATA_R & 0x01)


void PortF_Init(void);
char PortF_Input(void);
void PortF_Output(char data);

#endif
