#include <stm32f405xx.h>

uint8_t read_Ch;
uint8_t ch;

void USART3_init(void);
void USART3_write(uint8_t);
uint8_t USART3_read(void);
void delayMs(int);

#define size 4
uint8_t a[size] = {11, 12, 13, 14};

int main(void) {
    USART3_init();
    while (1) {
        for (int i = 0; i < 4; i++) {
            USART3_write(a[i]);
            delayMs(100);
            read_Ch = USART3_read();
            delayMs(100);
        }
    }
}

void USART3_init(void) {
    RCC->AHB1ENR |= (1 << 2);  // Enable GPIOC clock
    RCC->APB1ENR |= (1 << 18); // Enable USART3 clock

    // PC10 is the TX PIN for USART3
    GPIOC->MODER &= ~(3 << 20); // PC10, clear bit 21, 20
    GPIOC->MODER |= (1 << 21);  // PC10 in AFR mode, set bit 21
    GPIOC->AFR[1] &= ~(0xF << 8); // AFRH since pin10, clear bits 11, 10, 9, 8
    GPIOC->AFR[1] |= (7 << 8);  // AF7(0111), set bits 10, 9, 8

    // PC11 is the RX PIN for USART3
    GPIOC->MODER &= ~(3 << 22); // PC11, clear bit 23, 22
    GPIOC->MODER |= (1 << 23);  // PC11 in AFR mode, set bit 23, AF-19
    GPIOC->AFR[1] &= ~(0xF << 12); // AFRH since pin11, clear bits 15, 14, 13, 12
    GPIOC->AFR[1] |= (7 << 12);  // AF7(0111), set bits 14, 13, 12

    // USART3 Settings
    USART3->BRR = 0x0683; // 9600 baud @ 16 MHz
    USART3->CR1 = (0xC << 0); // Enable RE and TE bits - 1100, set bits 3, 2
    USART3->CR2 = 0; // 1 stop bit (00), bits 13, 12 corresponding to the number of stop bits
    USART3->CR3 = 0; // Default settings
    USART3->CR1 |= (1 << 13); // USART3 Enable
}

void USART3_write(uint8_t ch) {
    while (!(USART3->SR & (1 << 7))) {} // Wait until TXE (Transmit Data Register Empty) flag is set
    USART3->DR = (ch & 0xFF);
}

uint8_t USART3_read(void) {
    while (!(USART3->SR & (1 << 5))) {} // Wait until RXNE (Read Data Register Not Empty) flag is set
    return USART3->DR;
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--) {
        for (i = 0; i < 2000; i++);
    }
}
