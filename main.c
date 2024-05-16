#include <stdbool.h>
#include <stdio.h>

#include "GPIO.h"
#include "SysTick.h"
#include "LCD.h"
#include "GPS.h"
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "utilities.h"

#define THRESHOLD_DISTANCE 1

extern float currentLat;
extern float currentLong;

int main() {
    // Declare variables
    double dd;
    char str_buffer[50];
    float previousLat = currentLat;
    float previousLong = currentLong;
    double total_distance = 0;
    bool first_time = true;
    // Initialize the system
    PortF_Init();
    SysTick_Init();
    LCD_init();
    UART0_Init();
    UART2_Init();
    // Start the system
    PortF_Output(GPIO_RED_LED);
    LCD_displayString("Starting...");
    SysTick_Wait1s(30);
    LCD_Clear();
    LCD_displayString("Started!");
    while (total_distance < 100 && !SW1) {
        PortF_Output(GPIO_ALL_LEDS);
        GPS_read();
        GPS_format();
        currentLat = to_degree(currentLat);
        currentLong = to_degree(currentLong);
        LCD_Clear();
        sprintf(str_buffer, "d: %f", total_distance);
        LCD_displayString(str_buffer);
        sprintf(str_buffer, "%f,", currentLat);
        UART0_OutString(str_buffer);
        sprintf(str_buffer, "%f\n", currentLong);
        UART0_OutString(str_buffer);
        dd = distance(previousLat, previousLong, currentLat, currentLong);
        if (!first_time && dd > THRESHOLD_DISTANCE) {
            total_distance += dd;
        }
        previousLat = currentLat;
        previousLong = currentLong;
        SysTick_Wait1s(1);
        first_time = false;
    }
    PortF_Output(GPIO_GREEN_LED);
    LCD_Clear();
    if (total_distance >= 100) {
        LCD_displayString("100m exceeded!");
    }
    else {
        LCD_displayString("SW1 pressed!");
    }
    LCD_sendCommand(0xC0);  // Go to the second line
    sprintf(str_buffer, "d: %f", total_distance);
    LCD_displayString(str_buffer);
}
