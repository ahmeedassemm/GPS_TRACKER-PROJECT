#include "GPIO.h"

int main() {
    GPIO_initPORTF();
    // Testing turning on all LEDs
    led_on(GPIO_ALL_LEDS);
}
