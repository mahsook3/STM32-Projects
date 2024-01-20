#include <stdint.h>#include "stm32f405xx.h"
uint32_t result;
int main(void)
{
  RCC->AHB1ENR |= (1<<2);
  GPIOC->MODER &= ~(3<<4);
  GPIOC->MODER |= (3<<4);
  RCC->APB2ENR |=(1<<8);
  ADC1->CR2=0;
  ADC1->SQR3|=(0xC<<0);
  ADC1->SQR1=0;
  ADC1->CR2|=1;
  while(1){
	  ADC1->CR2 |=(1<<30);
	  while(!(ADC1->SR & 2)){}
	  result = ADC1->DR;
	  if(result>100)
		  GPIOC->ODR &= ~(1<<6);
	  else
		  GPIOC->ODR |= (1<<6);
  }
}
