#include "GPIO.h"

int main() {
    while (1) {
    GPIO_initPORTF();
    // Testing turning on all LEDs
    led_on(GPIO_ALL_LEDS);
    }
}
