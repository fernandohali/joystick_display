#ifndef _LED_H
#define _LED_H

#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/types.h"
#include <stdint.h>

#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12
#define LED_RED_PIN 13

void init_led(void);
void update_leds(int x_value, int y_value);
void toggle_green_led(void); // Nova função

#endif // _LED_H