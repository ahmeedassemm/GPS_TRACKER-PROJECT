#include "GPIO.h"
#include "tm4c123gh6pm.h"

// intializes port F
void PortF_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x00000020; // 1) activate clock for Port F
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0);// ready?
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x1F; // allow changes to PF4-0
    GPIO_PORTF_DIR_R = 0x0E; // 5) PF4,PF0 in, PF3-1 out
    GPIO_PORTF_PUR_R = 0x11; // enable pull-up on PF0 and PF4
    GPIO_PORTF_DEN_R = 0x1F; // 7) enable digital I/O on PF4-0
}

char PortF_Input(void) {
    return (char)(GPIO_PORTF_DATA_R & 0x11); // read PF4,PF0 inputs
}

void PortF_Output(char data) { // write PF3-PF1 outputs
    GPIO_PORTF_DATA_R = data;
}

void led_on(unsigned char led) {
    GPIO_PORTF_DATA_R |= led;
}

void led_off(unsigned char led) {
    GPIO_PORTF_DATA_R &= ~led;
}
