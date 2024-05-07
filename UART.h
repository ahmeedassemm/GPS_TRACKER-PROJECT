#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Bit_Utilities.h"


void UART0_init(void);
void UART0_send_byte(uint8_t c);
void UART0_output_string(char* s);

void UART2_INIT(void);
void UART2_send_byte(uint8_t c);
uint8_t UART2_read_byte(void);

