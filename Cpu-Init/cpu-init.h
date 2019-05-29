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
