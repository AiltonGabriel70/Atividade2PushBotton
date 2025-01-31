Projeto: Temporizador de um Disparo (One Shot) para LEDs com Raspberry Pi Pico W

Descrição

Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando um microcontrolador Raspberry Pi Pico W. O sistema funciona com base no pressionamento de um botão (pushbutton), ativando uma sequência de iluminação e desligamento de três LEDs com temporização controlada.

Componentes Utilizados

Raspberry Pi Pico W

3 LEDs (azul, vermelho e verde)

3 resistores de 330 Ω

1 botão (pushbutton)

Funcionamento

Quando o usuário pressiona o botão, os três LEDs são ligados simultaneamente.

Após 3 segundos, o LED azul é desligado, enquanto os LEDs verde e vermelho permanecem ligados.

Após mais 3 segundos, o LED verde é desligado, mantendo apenas o LED vermelho ligado.

Após mais 3 segundos, o LED vermelho é desligado, finalizando o ciclo.

O botão só pode ser pressionado novamente após o ciclo completo.

Recursos Implementados

Uso da função add_alarm_in_ms() do Pico SDK para temporização precisa.

Sistema de callback para gerenciamento da sequência de LEDs.

Mecanismo de debounce para evitar leituras falsas do botão.

Bloqueio do botão até o fim do ciclo para garantir execução correta da sequência.

Modo de Uso

Compile e carregue o código no Raspberry Pi Pico W.

Monte o circuito conforme a simulação sugerida no Wokwi.

Pressione o botão para iniciar a sequência de LEDs.

Aguarde a finalização do ciclo antes de pressionar o botão novamente.

Simulação e Testes

A simulação pode ser realizada no Wokwi. Também foi testada a implementação na ferramenta educacional BitDogLab, utilizando:

LED RGB nos GPIOs 11, 12 e 13

Botão A no GPIO 05

Melhorias Futuras

Implementação de um display para indicar o tempo restante.

Opção de ajustar o tempo de cada fase da sequência.

Integração com sensores para novos gatilhos de acionamento.

