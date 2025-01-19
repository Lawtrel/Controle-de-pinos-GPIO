#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

// Definições dos pinos dos LEDs e Buzzer
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 21

// Definições das notas musicais
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

const int tempo = 108;
int melody[] = {
    NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
    REST,8, NOTE_E4,8, NOTE_B4,2,
    NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
    REST,8, NOTE_E4,8, NOTE_B4,2,
    NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,
    REST,8, NOTE_E4,8, NOTE_B4,2,
    NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,
    REST,8, NOTE_E4,8, NOTE_B4,2,
    NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
    NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
    NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
    NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
    NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
    NOTE_A4,-2,
    NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
    NOTE_E4,-2,
    NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
    NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,
    NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,
    NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,
    NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,
    NOTE_A4,2, NOTE_A4,4,
    NOTE_D4,1,
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int notaInteira = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void tocar() {
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (notaInteira) / divider;
        } else if (divider < 0) {
            noteDuration = (notaInteira) / abs(divider);
            noteDuration *= 1.5;
        }

        int frequency = melody[thisNote];
        int delay = 1000000 / frequency / 2; // Calcula o delay em microsegundos

        for (int i = 0; i < noteDuration * 1000 / (delay * 2); i++) {
            gpio_put(BUZZER, 1);
            sleep_us(delay);
            gpio_put(BUZZER, 0);
            sleep_us(delay);
        }

        sleep_ms(noteDuration * 0.1); // Pausa entre as notas
    }
}

void inicializar() {
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(BUZZER);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);
}
// funcao para desligar os LEDs
void desligar_leds() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

void ligar_leds(uint led) {
    desligar_leds();
    gpio_put(led, 1);
}

void ligar_todosLeds() {
    gpio_put(LED_VERDE, 1);
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
}

int main()
{
    stdio_init_all();
    inicializar();

    char comando;
    //funcao para pegar o comando do usuario e ligar o respectivo LED
    while (true) {
        comando = getchar_timeout_us(1000000);
        switch (comando)
        {
        case '1':
            ligar_leds(LED_VERDE);
            printf("Ligando LED Verde\n");
            break;
        case '2':
            ligar_leds(LED_AZUL);
            printf("Ligando LED Azul\n");
            break;
        case '3':
            ligar_leds(LED_VERMELHO);
            printf("Ligando LED Vermelho\n");
            break;
        case '4':
            ligar_todosLeds();
            printf("Ligando todos os LEDs\n");
            break;
        case '0':
            desligar_leds();
            printf("Desligando todos os LEDs\n");
            break;

        case '5':
            printf("Tocando música:  Song of storms - Legend of Zelda\n");
            tocar();
            break;
        default:
            break;
        }
    }
    return 0;
}
