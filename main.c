#include "GPIO.h"
#include "UART.h"

int main() {
    GPIO_initPORTF();
    UART7_INIT();

    while (1) {
    // Testing turning on all LEDs
    led_on(GPIO_ALL_LEDS);
    }
}
