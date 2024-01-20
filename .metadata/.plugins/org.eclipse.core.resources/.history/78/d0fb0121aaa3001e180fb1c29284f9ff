#include <stm32f405xx.h>
void ms_delay_tim2(uint32_t n)
{
    RCC->APB1ENR |= (1 << 0);   // Enable clock for TIM2
    TIM2->PSC = 16000 - 1;       // Set prescaler for 1ms timebase
    TIM2->ARR = 1000 - 1;        // Set auto-reload value for 1ms period
    TIM2->CR1 = (1 << 0);        // Enable the timer

    for (uint32_t i = 0; i < n; i++) {
        while (!(TIM2->SR & (1 << 0))); // Wait until UIF (Update Interrupt Flag) is set
        TIM2->SR &= ~(1 << 0);           // Clear UIF to reset the interrupt flag
    }
}

int main(void)
{

    RCC->AHB1ENR |= (1 << 2);
    GPIOC->MODER |= (1 << 12);
    RCC->AHB1ENR |= (1 << 0);
    GPIOA->MODER &= ~(3 << 0);

    while (1) {

        if (GPIOA->IDR & (1 << 0)) {
             GPIOC->ODR |= (1 << 6);
            ms_delay_tim2(2);
            GPIOC->ODR &= ~(1 << 6);
        }
    }

    return 0;
}
