# joystick_display

Este projeto implementa um sistema de navegação utilizando um joystick analógico e um display SSD1306 na placa BitDogLab com o microcontrolador RP2040. Ele explora conceitos de conversores A/D, PWM, interrupções e comunicação I2C.

## Demonstração
[Link para o vídeo de demonstração](#)

## Funcionalidades
- **Controle de LEDs RGB**: Ajuste da intensidade dos LEDs Azul e Vermelho baseado nos valores do joystick.
- **Navegação no Display**: Movimento de um quadrado de 8x8 pixels proporcional aos valores do joystick.
- **Botão do Joystick**:
  - Alterna o estado do LED Verde a cada pressão.
  - Modifica a borda do display ao ser pressionado.
- **Botão A**: Ativa ou desativa os LEDs RGB.

## Componentes Utilizados
- **Placa BitDogLab com RP2040**
- **Joystick analógico** (GPIOs 26 e 27)
- **LED RGB** (GPIOs 11, 12 e 13)
- **Display SSD1306** via I2C (GPIOs 14 e 15)
- **Botão do Joystick** (GPIO 22)
- **Botão A** (GPIO 5)

## Requisitos do Projeto
1. **Interrupções**: Todas as ações dos botões são tratadas via interrupções (IRQ).
2. **Debouncing**: Implementado para evitar leituras falsas nos botões.
3. **Uso de PWM**: Controla a intensidade luminosa dos LEDs RGB.
4. **Comunicação I2C**: Para controle do display OLED SSD1306.
5. **Organização do Código**: Estruturado e comentado para facilitar a compreensão.

## Autor
Fernando Hali Santos Andrade
