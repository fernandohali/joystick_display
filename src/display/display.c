#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "../buttons/buttons.h"
#include "inc/ssd1306.h"
#include "display.h"

// Função de inicialização do display
void init_display(ssd1306_t *ssd)
{
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa e configura o display OLED
    ssd1306_init(ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(ssd);
    ssd1306_send_data(ssd);

    // Limpa o display
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

// Função para desenhar um pixel no display
void draw_pixel(ssd1306_t *ssd, int x, int y)
{
    // Desenha o quadrado 8x8 pixels na posição (x, y)
    ssd1306_rect(ssd, x, y, 8, 8, true, true); // Desenha o quadrado
    ssd1306_send_data(ssd);
}

// Função para atualizar o display com a nova posição
void update_display(ssd1306_t *ssd, int x, int y)
{
    // Atualiza o display com o quadrado na nova posição
    draw_pixel(ssd, x, y);
}

// Funções para desenhar as bordas
void draw_border_type1(ssd1306_t *ssd)
{
    ssd1306_rect(ssd, 0, 0, 128, 64, true, true); // Borda cheia
    ssd1306_send_data(ssd);
}

void draw_border_type2(ssd1306_t *ssd)
{
    ssd1306_rect(ssd, 1, 1, 126, 62, false, true); // Borda diferente
    ssd1306_send_data(ssd);
}
