Raspberry Pi Pico W - Controle de LEDs com Pushbutton

Este repositório contém códigos em C para o Raspberry Pi Pico W, desenvolvidos usando o VS Code e testados no simulador Wokwi, integrado ao ambiente de desenvolvimento através da extensão oficial. O objetivo é controlar LEDs por meio de timers, interrupções e debouncing, além de exibir informações via comunicação serial.

🚀 Descrição do Projeto

O código ALARMES-ATV permite o controle de três LEDs (vermelho, verde e azul) conectados aos pinos GPIO do Raspberry Pi Pico W. O acionamento de um pushbutton faz com que os LEDs acendam simultaneamente e se apaguem em sequência, com intervalos de tempo definidos por timers.

No projeto SEMAFORO, há um código que acende LEDs em sequência utilizando timers repetitivos, com mensagens de depuração enviadas via comunicação serial.

⚡ Funcionalidades

Acionamento de LEDs: Os LEDs acendem ao pressionar o botão e apagam em sequência: verde → azul → vermelho.

Controle Sequencial de LEDs: LEDs acendem e apagam em sequência automaticamente.

Timers com Alarmes: Utilização de alarmes para controlar o tempo de desligamento dos LEDs.

Debounce Simples: Implementação de um atraso para evitar leituras falsas do botão.

Feedback Serial: Mensagens exibidas no terminal serial para depuração e acompanhamento do estado do sistema.

Simulação com Wokwi Integrado ao VS Code: Testes realizados diretamente no VS Code usando o simulador Wokwi para validação do comportamento do código antes da implementação em hardware real.

📋 Estrutura do Código de ALarmes

Definição de Pinos:

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUT_PIN 5

Funções de Controle:

turn_off_callback(): Desliga o LED verde.

turn_off_blue(): Desliga o LED azul.

turn_off_red(): Desliga o LED vermelho e redefine o estado do sistema.

Loop Principal:
O código verifica continuamente o estado do botão e gerencia o acionamento dos LEDs.

Código do SEMAFORO (Sequência Automática de LEDs):
Utiliza um timer repetitivo para acender LEDs em sequência, apagando o LED anterior automaticamente.

🛠️ Como Usar

1. Pré-requisitos:

Raspberry Pi Pico W

VS Code com extensões para C/C++

SDK do Raspberry Pi Pico configurado

Extensão do simulador Wokwi integrada ao VS Code

2. Montagem do Circuito:

LEDs conectados aos pinos GPIO 11, 12 e 13 (com resistores de 220Ω).

Pushbutton conectado ao GPIO 5 com resistor de pull-up.

3. Simulação com Wokwi:

Instale a extensão do Wokwi no VS Code.

Crie um novo projeto Wokwi no próprio VS Code.

Copie e cole o código no ambiente do Wokwi.

Execute a simulação diretamente no VS Code para verificar o funcionamento dos LEDs e do botão.

4. Compilação e Upload no Hardware:

mkdir build && cd build
cmake ..
make

Em seguida, arraste o arquivo .uf2 gerado para o Raspberry Pi Pico W em modo de bootloader.

5. Monitoramento Serial:

Use um monitor serial (como minicom ou o terminal integrado do VS Code) para visualizar as mensagens:

minicom -b 115200 -o -D /dev/ttyACM0

🧪 Exemplos de Saída Serial

Button pressed


Turn off green

Turn off blue

Turn off red

Um segundo se passou!

Contagem atual: 1

📚 Contribuição

Sinta-se à vontade para abrir issues ou enviar pull requests com melhorias.

Feito por Vinicius Paz
