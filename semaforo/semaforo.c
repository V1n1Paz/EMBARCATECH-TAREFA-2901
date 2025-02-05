#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

//Define valores iniciais para os pinos dos LEDs
static int LED_PIN_ON = 11;
static int LED_PIN_OFF = 10;

//Função callback que será chamada a cada 3000ms
bool repeating_timer_callback( struct repeating_timer *t){

    gpio_put(LED_PIN_ON, 1);                    //Acende o LED

    if (LED_PIN_OFF > 10 && LED_PIN_OFF < 14)   //Apaga o LED anterior (se eestiver entre os pinos 11 e 13)
        gpio_put(LED_PIN_OFF, 0);

    LED_PIN_ON++;                   //Incrementa o pino do LED a ser aceso             
    LED_PIN_OFF = LED_PIN_ON - 1;   //Incrementa o pino do LED a ser apagado

    if (LED_PIN_ON > 13)            //Se o pino do LED a ser aceso for maior que 13, volta para 11
        LED_PIN_ON = 11;
        
    return 1;
}


int main()
{
    //Configurações do timer
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    //Inicializa o a comunicação serial
    stdio_init_all();

    //Define a vaiavel para contar o tempo
    int countTime = 1;

    for ( uint LED_PIN_INIT = 11; LED_PIN_INIT <= 13; LED_PIN_INIT++)   //Inicializa os pinos dos LEDs e os define como saída(11 a 13)
    {
        gpio_init(LED_PIN_INIT);
        gpio_set_dir(LED_PIN_INIT, GPIO_OUT);
        gpio_put(LED_PIN_INIT, 0);
    }
    
    sleep_ms(1000);     //Aguarda um segundo
    printf("Um segundo se passou!\nContagem atual:  %d\n\n", countTime);    //Imprime a contagem atual
    
    //Loop principal
    while (true) {    
        sleep_ms(1000);    //Aguarda um segundo
        countTime++;       //Incrementa a contagem
        printf("Mais um segundo se passou!\nContagem atual: %d\n\n", countTime);    //Imprime a contagem atual
    }
}
