#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../led/led.h"
#include "../display/inc/ssd1306.h"
#include "../display/display.h"
#include <stdio.h>
#include "buttons.h"

static uint32_t last_interrupt_time = 0;
#define DEBOUNCE_DELAY 50 // Reduzido para 50 ms

void button_irq_handler(uint gpio, uint32_t events);

extern ssd1306_t ssd;

// Função de inicialização dos botões
void init_buttons()
{
    gpio_init(JOYSTICK_BUTTON);
    gpio_init(BUTTON_A);

    gpio_set_dir(JOYSTICK_BUTTON, GPIO_IN);
    gpio_set_dir(BUTTON_A, GPIO_IN);

    gpio_pull_up(JOYSTICK_BUTTON);
    gpio_pull_up(BUTTON_A);

    // Configura interrupção para o botão do joystick e botão A
    gpio_set_irq_enabled_with_callback(JOYSTICK_BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);

    printf("Botões inicializados.\n");
}

// Manipulador de interrupção para os botões
void button_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_interrupt_time > DEBOUNCE_DELAY)
    {
        last_interrupt_time = current_time;

        if (gpio == JOYSTICK_BUTTON)
        {
            printf("Botão do joystick pressionado.\n");
            toggle_border_style();
        }

        if (gpio == BUTTON_A)
        {
            printf("Botão A pressionado.\n");
            toggle_pwm(); // Alternar o estado do PWM
        }
    }
}

void toggle_border_style()
{
    static bool border_style = false;
    border_style = !border_style;
    if (border_style)
    {
        printf("Alternando borda para estilo 1.\n");
        draw_border_type1(&ssd);
    }
    else
    {
        printf("Alternando borda para estilo 2.\n");
        draw_border_type2(&ssd);
    }
}