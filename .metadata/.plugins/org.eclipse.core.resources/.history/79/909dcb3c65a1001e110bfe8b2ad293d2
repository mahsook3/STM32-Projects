#include <stdio.h>
#include <stdint.h>
#include "stm32f405xx.h"
void pc6_tim3_pwm_config(void)
{
   RCC->AHB1ENR|=(1<<2);
   GPIOC->MODER|=(2<<12);
   GPIOC->AFR[0]=(2<<24);
   RCC->APB1ENR|=(1<<1);
   TIM3->PSC=0;
   TIM3->CNT=0;
   TIM3->CR1|=(1<<0);
   TIM3->CCMR1|=(0<<3);
   TIM3->CCMR1|=(7<<4);
   TIM3->CCER|=(3<<0);
}
void tim3_pc6_set_dutycycle(uint32_t freq, uint32_t duty_cycle, uint8_t channel)
{
	TIM3->ARR=((16000000/freq)-1);
	TIM3->CCR1=(duty_cycle*((TIM3->ARR)+1))/100;
}
int main()
{
	pc6_tim3_pwm_config();
     while(1)
     {
    	 tim3_pc6_set_dutycycle(1000,90,1);
    	 for(int i=0;i<3000000;i++);
    	 tim3_pc6_set_dutycycle(1000,75,1);
    	 for(int i=0;i<3000000;i++);
    	 tim3_pc6_set_dutycycle(1000,50,1);
    	 for(int i=0;i<3000000;i++);
    	 tim3_pc6_set_dutycycle(1000,25,1);
    	 for(int i=0;i<3000000;i++);
     }
}
