#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 400
#define LED_VERMELHO 13
#define BOTAO_A 5      
#define BOTAO_B 6      

int estado_atual = 0;
static volatile uint32_t ultimo_tempo = 0; // Armazena o tempo do último evento (em microssegundos)
volatile uint32_t last_irq_time_A = 0;
volatile uint32_t last_irq_time_B = 0;
int num_eventos = 10;
// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0; // Intensidade do vermelho
uint8_t led_g = 0; // Intensidade do verde
uint8_t led_b = 200; // Intensidade do azul

// Buffer para armazenar quais LEDs estão ligados matriz 5x5

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}


int numero = 10;
// Inicialização dos desenhos
int i = 0;
    // Desenho do número 0
// Matriz para armazenar os desenhos dos números de 0 a 9
double desenho0[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

void num0(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho0[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 1
double desenho1[25] = 
    {0.0, 0.2, 0.2, 0.2, 0.0,
     0.0, 0.0, 0.2, 0.0, 0.0,
     0.0, 0.0, 0.2, 0.0, 0.0,
     0.0, 0.2, 0.2, 0.0, 0.0,
     0.0, 0.0, 0.2, 0.0, 0.0};

void num1(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho1[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}
// Desenho do número 2
double desenho2[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};
void num2(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho2[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 3
double desenho3[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

void num3(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho3[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}
// Desenho do número 4
double desenho4[25] = {
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0
};
void num4(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho4[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 5
double desenho5[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};
void num5(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho5[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 6
double desenho6[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

void num6(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho6[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}
// Desenho do número 7
double desenho7[25] = {
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};

void num7(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho7[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}
// Desenho do número 8
double desenho8[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};
void num8(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho8[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

// Desenho do número 9
double desenho9[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0
};
void num9(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho9[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}
void atualizar_estado() {
    switch (estado_atual) {
        case 0:
            num0(255,0,0);
            break;
        case 1:
            num1(0,255,0);
            break;
        case 2:
            num2(200,100,50);
            break;
        case 3:
            num3(0,0,255);
            break;
        case 4:
            num4(0,75,150);
            break;
        case 5:
            num5(150,90,24);
            break;
        case 6:
            num6(156,36,85);
            break;
        case 7:
            num7(225,100,0);
            break;
        case 8:
            num8(0,201,204);
            break;
        case 9:
            num9(97,0,99);
            break;
    }
}
void debounce_botao(uint pino, volatile uint32_t *last_irq_time, int direcao) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    if (tempo_atual - *last_irq_time > 200) {
        *last_irq_time = tempo_atual;
        estado_atual += direcao;
        if (estado_atual >= num_eventos) estado_atual = 0;
        if (estado_atual < 0) estado_atual = num_eventos - 1;
        atualizar_estado();
    }
}
int main()
{
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);
    while (1)
    {
     gpio_put(LED_VERMELHO, 1);
     sleep_ms(125);
     gpio_put(LED_VERMELHO, 0);
     sleep_ms(75);
     if (!gpio_get(BOTAO_B)) debounce_botao(BOTAO_B, &last_irq_time_B, -1);
     if (!gpio_get(BOTAO_A)) debounce_botao(BOTAO_A, &last_irq_time_A, +1);
     sleep_ms(20);
    }

    return 0;
}
