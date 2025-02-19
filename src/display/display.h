#ifndef _DISPLAY_H
#define _DISPLAY_H

// Definições do I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Protótipos das funções
void init_display(ssd1306_t *ssd);                 // Função para inicializar o display
void draw_pixel(ssd1306_t *ssd, int x, int y);     // Função para desenhar um pixel no display
// Funções de desenho de borda
void draw_border_type1(ssd1306_t *ssd); // Desenha a borda tipo 1
void draw_border_type2(ssd1306_t *ssd); // Desenha a borda tipo 2

#endif
