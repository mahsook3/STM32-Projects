#include <stm32f405xx.h>
 uint8_t Sensorstatus;

 uint32_t n;
void ms_delay_tim2(uint32_t n){
	//configure TIM2
	RCC->APB1ENR |=(1<<0);
	TIM2->PSC = 16000-1;
	TIM2->ARR =n-1;
	TIM2->CR1 |= (1<<0); //enable the timer


		while(!(TIM2->SR &(1<<0))){}
			TIM2->SR &= ~(1<<0); // clear UIF to reset the interrupt flag

	}

int main(void)
{
// IR sensor
	RCC->AHB1ENR |=(1<<2);
	GPIOC->MODER |= (0<<14);



//Enable clock GPIO(LED)
	RCC->AHB1ENR |= (1<<2);
	//SET GPIO pin 6 (LED) as output
	GPIOC->MODER &=~(1<<12);
	GPIOC->MODER |=(1<<12);
	while(1){
		//Toggle LED on PC6
 if((GPIOC->IDR )& (1 << 7))
 {

	 GPIOC->ODR &= ~(1<<6);

 }
else{

	GPIOC->ODR |= (1<<6);
	 ms_delay_tim2(60000);

	}
}

	return 0;
}

