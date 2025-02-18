#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"

#include "display/inc/ssd1306.h"
#include "display/display.h"
#include "led/led.h"
#include "buttons/buttons.h"
#include "joystick/joystick.h"

// Definindo o display SSD1306
ssd1306_t ssd;

int main()
{
    stdio_init_all();

    printf("Iniciando...\n");

    // Inicializando os módulos
    init_buttons();
    printf("Botões inicializados.\n");

    init_led();
    printf("LEDs inicializados.\n");

    init_joystick();
    printf("Joystick inicializado.\n");

    init_display(&ssd);
    printf("Display inicializado.\n");

    int x = 60, y = 30; // Posição inicial do quadrado

    sleep_ms(1000); // Delay para o loop

    while (true)
    {
        // Leitura dos valores analógicos do joystick
        int x_value = read_joystick_x();
        int y_value = read_joystick_y();

        // Ajustando os valores do joystick (invertendo ambos os eixos)
        int x_offset = (2048 - x_value) / 204; // Invertendo o eixo X
        int y_offset = (y_value - 2048) / 204; // Invertendo o eixo Y corretamente

        // Atualizando a posição do quadrado no display
        x += x_offset;
        y += y_offset;

        // Limites do display (levando em conta o tamanho do quadrado de 8x8)
        if (x < 0)
            x = 0;
        if (x > 120)
            x = 120;
        if (y < 0)
            y = 0;
        if (y > 56)
            y = 56;

        // Atualizando a posição do quadrado no display
        draw_pixel(&ssd, x, y);

        // Atualizando os LEDs
        update_leds(x_value, y_value);

        sleep_ms(100); // Delay para o loop
    }

    return 0;
}