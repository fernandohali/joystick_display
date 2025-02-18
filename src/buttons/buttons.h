#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "pico/types.h"
#include <stdint.h>

#define BUTTON_A 5
#define JOYSTICK_BUTTON 22

void init_buttons(void);
void button_irq_handler(uint gpio, uint32_t events);
void toggle_border_style(void);
void toggle_pwm(void);

#endif