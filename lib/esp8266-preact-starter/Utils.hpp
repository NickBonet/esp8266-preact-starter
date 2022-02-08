/**
 * Header file for common utility functions used throughout the project.
 *
 */

#include <Arduino.h>

/**
 * Activates the ESP's onboard LED.
 *
 */
void activateESPLED()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void deactiveESPLED()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}