#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"


//Pinos dos LEDs
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13

//Pino do pushbutton
#define BUT_PIN 5

//Variável para controlar se os LEDs estão mudando de estado
static bool LEDS_ARE_CHANGING = 0;

//Delay dos LEDS
#define LEDS_DELAY 3000

//Delay para debounce
#define DEBOUNCE_DELAY 20

//Defines as funções de alarme
int64_t turn_off_red(alarm_id_t id, void *user_data);
int64_t turn_off_blue(alarm_id_t id, void *user_data);
int64_t turn_off_callback(alarm_id_t id, void *user_data);


//função que desliga o LED verde
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    printf("Turn off green\n"); //Desliga o LED verde
    gpio_put(LED_PIN_GREEN, 0);
    add_alarm_in_ms(2000, turn_off_blue, NULL, 0);  //Adiciona um alarme para desligar o LED azul
    return 0;
}

//função que desliga o LED azul
int64_t turn_off_blue(alarm_id_t id, void *user_data) {
    printf("Turn off blue\n");  //Desliga o LED azul
    gpio_put(LED_PIN_BLUE, 0);  
    add_alarm_in_ms(2000, turn_off_red, NULL, 0);   //Adiciona um alarme para desligar o LED vermelho
    return 0;
}

//Função que desliga o LED vermelho
int64_t turn_off_red(alarm_id_t id, void *user_data) {
    printf("Turn off red\n");
    gpio_put(LED_PIN_RED, 0);   //Desliga o LED vermelho
    LEDS_ARE_CHANGING = 0;      //Define que os LEDs não estão mudando de estado mais
    return 0;
}


int main()
{
    stdio_init_all();   //Inicializa a comunicação serial

    //Inicializa os pinos dos LEDs
    gpio_init(LED_PIN_GREEN);       
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    //Inicializa o pino do pushbutton e o define como pull-up
    gpio_init(BUT_PIN);
    gpio_set_dir(BUT_PIN, GPIO_IN);
    gpio_pull_up(BUT_PIN);

    //Loop principal
    while (true) {
        if (gpio_get(BUT_PIN) == 0 && LEDS_ARE_CHANGING == 0) { //Se o botão foi pressionado e os LEDs não estão mudando de estado
            LEDS_ARE_CHANGING = 1;      //Define que os LEDs estão mudando de estado
            printf("Button pressed\n"); 
            gpio_put(LED_PIN_RED, 1);   //Liga o LED vermelho
            gpio_put(LED_PIN_GREEN, 1); //Liga o LED verde
            gpio_put(LED_PIN_BLUE, 1);  //Liga o LED azul
            add_alarm_in_ms(LEDS_DELAY, turn_off_callback, NULL, 0);  //Adiciona um alarme para desligar o LED verde
        }
        sleep_ms(DEBOUNCE_DELAY);  //Intervalo para debounce
    }
}
