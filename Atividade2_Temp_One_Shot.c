//Atividade 2 usando OneShot para controle de LEDs 
//Gilmaiane Porto Silva

#include "pico/stdlib.h"
#include "hardware/timer.h"

#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define GREEN_LED_PIN 11
#define BUTTON_PIN 5

// Estados dos LEDs
enum LEDState {
    ALL_ON,
    TWO_ON,
    ONE_ON,
    OFF
};

// Variável global para controlar o estado dos LEDs
volatile enum LEDState current_state = OFF;
volatile bool button_locked = false; // Impede múltiplas execuções simultâneas

// Função para desligar os LEDs
void turn_off_leds() {
    gpio_put(BLUE_LED_PIN, 0);
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
}

// Callback do temporizador (One Shot)
int64_t led_timer_callback(alarm_id_t id, void *user_data) {
    switch (current_state) {
        case ALL_ON:
            gpio_put(BLUE_LED_PIN, 1); //3 leds acesos
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 1);
            current_state = TWO_ON;
            add_alarm_in_ms(3000, led_timer_callback, NULL, false);
            break;
        case TWO_ON:
            gpio_put(BLUE_LED_PIN, 1); //2 leds acesos
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 0);
            current_state = ONE_ON;
            add_alarm_in_ms(3000, led_timer_callback, NULL, false);
            break;
        case ONE_ON:
            gpio_put(BLUE_LED_PIN, 0);  // Desliga azul
            gpio_put(RED_LED_PIN, 1);   // Mantém vermelho aceso
            gpio_put(GREEN_LED_PIN, 0); // Verde já estava desligado
            current_state = OFF;
            add_alarm_in_ms(3000, led_timer_callback, NULL, false);
            break;
        case OFF:
            gpio_put(BLUE_LED_PIN, 0);  // Garante que tudo está apagado
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 0);
            button_locked = false; // Libera o botão para uma nova ativação            
            break;
    }
    return 0; // Indica que o alarme não deve ser reativado
}

// Função para debouncing do botão 
bool debounce_button() {
    static uint32_t last_time = 0;
    uint32_t current_time = time_us_32();
    if (current_time - last_time > 200000) { // 200ms de debounce
        last_time = current_time;
        return true;
    }
    return false;
}


// Interrupção do botão
void button_isr(uint gpio, uint32_t events) {
    if (debounce_button() && !button_locked) {
        button_locked = true;
        current_state = ALL_ON;
        led_timer_callback(0, NULL);
    }
}

int main() {
    // Inicialização
    stdio_init_all();

    // Configuração dos pinos
    gpio_init(BLUE_LED_PIN);
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BUTTON_PIN);
    
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    //Interrupção
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_isr);


    // Loop principal
    while (true) {
        sleep_ms(10);
    }

    return 0;
}
