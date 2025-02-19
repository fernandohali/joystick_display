#include "led.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../joystick/joystick.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Variável para controlar o estado do PWM
static bool pwm_enabled = false;  // Inicialmente desativado
static bool leds_enabled = false; // Inicialmente desativado

// Função para inicializar os LEDs
void init_led(void)
{
    // Inicializando os pinos dos LEDs
    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_RED_PIN);

    // Definindo como saída
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    // Configuração PWM para os LEDs Azul e Vermelho
    gpio_set_function(LED_BLUE_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);

    // Obtendo números de slice e canal corretos
    uint slice_num_blue = pwm_gpio_to_slice_num(LED_BLUE_PIN);
    uint slice_num_red = pwm_gpio_to_slice_num(LED_RED_PIN);
    uint chan_blue = pwm_gpio_to_channel(LED_BLUE_PIN);
    uint chan_red = pwm_gpio_to_channel(LED_RED_PIN);

    // Configuração do PWM
    pwm_set_wrap(slice_num_blue, 255);
    pwm_set_wrap(slice_num_red, 255);

    pwm_set_chan_level(slice_num_blue, chan_blue, 0);
    pwm_set_chan_level(slice_num_red, chan_red, 0);

    pwm_set_enabled(slice_num_blue, true);
    pwm_set_enabled(slice_num_red, true);

    printf("LEDs inicializados. Slice Azul: %d, Slice Vermelho: %d, Canal Azul: %d, Canal Vermelho: %d\n", slice_num_blue, slice_num_red, chan_blue, chan_red);
}

// Função para atualizar os LEDs com base nos valores do joystick
void update_leds(int x_value, int y_value)
{
    if (!leds_enabled || !pwm_enabled)
    {
        pwm_set_chan_level(pwm_gpio_to_slice_num(LED_RED_PIN), pwm_gpio_to_channel(LED_RED_PIN), 0);
        pwm_set_chan_level(pwm_gpio_to_slice_num(LED_BLUE_PIN), pwm_gpio_to_channel(LED_BLUE_PIN), 0);
        return;
    }

    // Mapeia os valores dos eixos para a faixa de 0 a 255
    int red_brightness = abs(x_value - 2048) / 8;         // Ajuste para melhor visibilidade
    int blue_brightness = abs(4095 - y_value - 2048) / 8; // Ajuste para melhor visibilidade

    // Limita os valores entre 0 e 255
    red_brightness = red_brightness > 255 ? 255 : red_brightness;
    blue_brightness = blue_brightness > 255 ? 255 : blue_brightness;

    // Garante que ambos os LEDs acendam simultaneamente
    pwm_set_chan_level(pwm_gpio_to_slice_num(LED_RED_PIN), pwm_gpio_to_channel(LED_RED_PIN), red_brightness);
    pwm_set_chan_level(pwm_gpio_to_slice_num(LED_BLUE_PIN), pwm_gpio_to_channel(LED_BLUE_PIN), blue_brightness);

    printf("LED Vermelho: %d, LED Azul: %d\n", red_brightness, blue_brightness);
}

// Função para alternar o estado do PWM
void toggle_pwm()
{
    pwm_enabled = !pwm_enabled;
    printf("PWM %s.\n", pwm_enabled ? "ativado" : "desativado");
}

// Função para habilitar/desabilitar os LEDs
void enable_leds(bool enable)
{
    leds_enabled = enable;
    if (!enable)
    {
        gpio_put(LED_GREEN_PIN, 0);
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_BLUE_PIN, 0);
    }
    printf("LEDs %s.\n", enable ? "habilitados" : "desabilitados");
}

// Função para alternar o LED verde
void toggle_green_led()
{
    if (leds_enabled)
    {
        static bool green_led_state = false;
        green_led_state = !green_led_state;
        gpio_put(LED_GREEN_PIN, green_led_state);
        printf("LED Verde %s.\n", green_led_state ? "ligado" : "desligado");
    }
}

// Função para alternar o LED azul
void toggle_blue_led()
{
    if (leds_enabled)
    {
        static bool blue_led_state = false;
        blue_led_state = !blue_led_state;
        gpio_put(LED_BLUE_PIN, blue_led_state);
        printf("LED Azul %s.\n", blue_led_state ? "ligado" : "desligado");
    }
}

// Função para alternar o LED vermelho
void toggle_red_led()
{
    if (leds_enabled)
    {
        static bool red_led_state = false;
        red_led_state = !red_led_state;
        gpio_put(LED_RED_PIN, red_led_state);
        printf("LED Vermelho %s.\n", red_led_state ? "ligado" : "desligado");
    }
}
