#include <stm32f405xx.h>

int main(void)
{
	RCC->AHB1ENR |=(1<<1);
	GPIOB->MODER &= ~(3 << 14);

	RCC->AHB1ENR |=(1<<2);
	GPIOC->MODER |=(1<<12);
	 while(1)
	 {
		 uint8_t btnstatus =(uint8_t)(GPIOB->IDR & (1<<7));// read from PB7
		 if(btnstatus==0){
			  GPIOC->ODR &= ~(1<<6); //LED connected to PC6 is ON
		 }
		 else{
			 GPIOC->ODR |=(1<<6); //LED connected to PC6 in off
		 }
	 }
  return 0;
}
