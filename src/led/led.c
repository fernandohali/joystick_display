#include "led.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../joystick/joystick.h"
#include <stdlib.h>
#include <math.h>

// Variável para controlar o estado do PWM
static bool pwm_enabled = true;

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

	// Configuração do PWM
	uint slice_num_blue = pwm_gpio_to_slice_num(LED_BLUE_PIN);
	uint slice_num_red = pwm_gpio_to_slice_num(LED_RED_PIN);

	pwm_set_wrap(slice_num_blue, 255);
	pwm_set_wrap(slice_num_red, 255);

	pwm_set_chan_level(slice_num_blue, PWM_CHAN_A, 0);
	pwm_set_chan_level(slice_num_red, PWM_CHAN_A, 0);

	pwm_set_enabled(slice_num_blue, true);
	pwm_set_enabled(slice_num_red, true);

	printf("LEDs inicializados.\n");
}

// Função para atualizar os LEDs com base nos valores do joystick
void update_leds(int x_value, int y_value)
{
	if (!pwm_enabled)
	{
		// Se o PWM estiver desativado, desliga os LEDs
		pwm_set_chan_level(pwm_gpio_to_slice_num(LED_RED_PIN), PWM_CHAN_A, 0);
		pwm_set_chan_level(pwm_gpio_to_slice_num(LED_BLUE_PIN), PWM_CHAN_A, 0);
		return;
	}

	// Mapeia os valores dos eixos para a faixa de 0 a 255 para o controle de PWM
	int red_brightness = abs(x_value - 2048) / 16;		   // Dividido por 16 para ajustar a faixa de 0 a 255
	int blue_brightness = abs(4095 - y_value - 2048) / 16; // Invertendo o eixo Y

	// Limita os valores entre 0 e 255
	red_brightness = (red_brightness > 255) ? 255 : red_brightness;
	blue_brightness = (blue_brightness > 255) ? 255 : blue_brightness;

	// Atualiza o brilho dos LEDs
	pwm_set_chan_level(pwm_gpio_to_slice_num(LED_RED_PIN), PWM_CHAN_A, red_brightness);
	pwm_set_chan_level(pwm_gpio_to_slice_num(LED_BLUE_PIN), PWM_CHAN_A, blue_brightness);

	printf("LED Vermelho: %d, LED Azul: %d\n", red_brightness, blue_brightness);
}

// Função para alternar o estado do PWM
void toggle_pwm()
{
	pwm_enabled = !pwm_enabled;
	printf("PWM %s.\n", pwm_enabled ? "ativado" : "desativado");
}