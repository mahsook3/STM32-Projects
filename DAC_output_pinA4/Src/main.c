#include <stm32f405xx.h>

uint32_t analog;
void delay(uint32_t dly)
{
	uint32_t i,j;
	for(i=0;i<dly;i++);
	for(j=0;i<16000;j++);
}

int main(void)
{

    int i;
    const static int sinewave[]=
    {
    		0,500,1000,1500,2000,2500,3000,3500,4000,4095,0,4095,4000,3500,3000,2500,2000,1500,1000,500
    };
    RCC->AHB1ENR |= (1<<0);
    GPIOA->MODER &= ~(3<<8);
    GPIOA->MODER |= (3<<8);

    RCC->APB1ENR |= (1<<29);
    DAC->CR |= 1;

    while(1){
    	for(i=0;i<20;i++){
    		DAC->DHR12R1 =sinewave[i];
    		analog=DAC->DHR12R1;
    		delay(200);
    	}
    }

    return 0;
}
