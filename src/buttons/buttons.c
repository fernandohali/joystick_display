#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../led/led.h" // Inclua o cabeçalho led.h
#include "../display/inc/ssd1306.h"
#include "../display/display.h"
#include <stdio.h>
#include "buttons.h"
#include "pico/bootrom.h"

static uint32_t last_interrupt_time = 0;
#define DEBOUNCE_DELAY 200 // Aumentado para 200 ms para melhorar o debounce
extern ssd1306_t ssd;

// Função de callback para interrupções dos botões
void button_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Debounce: verifica se o tempo desde a última interrupção é maior que o delay
    if (current_time - last_interrupt_time > DEBOUNCE_DELAY)
    {
        last_interrupt_time = current_time;

        if (gpio == JOYSTICK_BUTTON)
        {
            printf("Botão do joystick pressionado.\n");
            enable_leds(true);  // Habilita os LEDs
            toggle_green_led(); // Alternar o LED verde

            printf("Alternando borda para estilo 1.\n");
            draw_border_type1(&ssd); // Borda normal
        }
        else
        {
            printf("Alternando borda para estilo 2.\n");
            draw_border_type2(&ssd); // Borda mais grossa
        }

        if (gpio == BUTTON_A)
        {
            printf("Botão A pressionado.\n");
            enable_leds(true); // Habilita os LEDs
            toggle_pwm();      // Alternar o estado do PWM
            toggle_red_led();  // Alternar o LED vermelho
            toggle_blue_led(); // Alternar o LED azul
        }

        if (gpio == BUTTON_B)
        {
            printf("Botão B pressionado.\n");
            reset_usb_boot(0, 0);
        }
    }
}

// Função de inicialização dos botões
void init_buttons()
{
    // Inicializa os pinos dos botões
    gpio_init(JOYSTICK_BUTTON);
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);

    // Configura os pinos como entrada
    gpio_set_dir(JOYSTICK_BUTTON, GPIO_IN);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);

    // Habilita pull-up nos pinos dos botões
    gpio_pull_up(JOYSTICK_BUTTON);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Configura interrupções para os botões
    gpio_set_irq_enabled(JOYSTICK_BUTTON, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON_A, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    // Configura a função de callback para as interrupções
    gpio_set_irq_callback(&button_irq_handler);

    // Habilita interrupções globais
    irq_set_enabled(IO_IRQ_BANK0, true);

    printf("Botões inicializados.\n");
}

/* // Função para alternar o estilo da borda
void toggle_border_style()
{
    static bool border_style = false;
    border_style = !border_style;
    if (border_style)
    {
    }
    else
    {
    }
}
 */