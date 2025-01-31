#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs e do botão
#define LED_BLUE_PIN 11
#define LED_GREEN_PIN 12
#define LED_RED_PIN 13
#define BUTTON_PIN 5

// Variáveis globais
bool timer_running = false;  // Impede nova ativação do temporizador
int led_state = 0;            // Estado atual dos LEDs
bool sequence_complete = true; // Garante que o botão só funcione após a sequência

// Função de callback para o temporizador
int64_t led_timer_callback(alarm_id_t id, void *user_data) {
    if (led_state == 0) {
        gpio_put(LED_BLUE_PIN, 1);
        gpio_put(LED_GREEN_PIN, 1);
        gpio_put(LED_RED_PIN, 1);
        led_state = 1;
        add_alarm_in_ms(3000, led_timer_callback, NULL, false);
    } else if (led_state == 1) {
        gpio_put(LED_BLUE_PIN, 0);
        gpio_put(LED_GREEN_PIN, 1);
        gpio_put(LED_RED_PIN, 1);
        led_state = 2;
        add_alarm_in_ms(3000, led_timer_callback, NULL, false);
    } else if (led_state == 2) {
        gpio_put(LED_BLUE_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
        gpio_put(LED_RED_PIN, 1);
        led_state = 3;
        add_alarm_in_ms(3000, led_timer_callback, NULL, false);
    } else if (led_state == 3) {
        gpio_put(LED_BLUE_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
        gpio_put(LED_RED_PIN, 0);
        led_state = 0;
        timer_running = false; // Permite nova ativação do botão
        sequence_complete = true;
    }
    return 0;
}

// Função para verificar o botão com debounce
bool check_button() {
    static uint32_t last_button_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    
    if ((current_time - last_button_time) > 300) {  // Reduz debounce para 300ms
        last_button_time = current_time;
        return gpio_get(BUTTON_PIN) == 0;  // Botão pressionado
    }
    return false;
}

int main() {
    // Inicializa os pinos
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_RED_PIN);
    gpio_init(BUTTON_PIN);

    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita pull-up interno no botão

    while (true) {
        if (check_button() && !timer_running && sequence_complete) {
            timer_running = true;
            sequence_complete = false;
            led_state = 0;
            add_alarm_in_ms(10, led_timer_callback, NULL, false); // Reduz tempo inicial para resposta mais rápida
        }
        sleep_ms(10); // Reduz uso excessivo da CPU
    }
    return 0;
}
