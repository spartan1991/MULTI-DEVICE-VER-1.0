#include <stdint.h>

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "n3310.h"
#include "system.h"

#define DMA_BUFFER_SIZE 80 // Размер буфера DMA

// Keyboard
#define LEFT   5
#define UP     8
#define RIGHT  9
#define DOWN   6
#define CENTER 7


void gpio_init(void);
void uart1_init(void);
void uart3_init(void);
void dma1_init(void);
void system_init(void);

void clearBuffer(uint8_t* buf);
void copyFilterBuffer(uint8_t* bufIn, uint8_t* bufOut);
