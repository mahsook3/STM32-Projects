#include <stdio.h>

#include <stdint.h>

#include "stm32f405xx.h"

uint32_t result;
//uint32_t VOLTAGE;
void pc6_tim3_pwm_config(void) {
  RCC -> AHB1ENR |= (1 << 2);
  GPIOC -> MODER |= (2 << 12);
  GPIOC -> AFR[0] = (2 << 24);
  RCC -> APB1ENR |= (1 << 1);
  TIM3 -> PSC = 0;
  TIM3 -> CNT = 0;
  TIM3 -> CR1 |= (1 << 0);
  TIM3 -> CCMR1 |= (0 << 3);
  TIM3 -> CCMR1 |= (7 << 4);
  TIM3 -> CCER |= (3 << 0);
}
void tim3_pc6_set_dutycycle(uint32_t freq, uint32_t duty_cycle, uint8_t channel) {
  TIM3 -> ARR = ((16000000 / freq) - 1);
  TIM3 -> CCR1 = (duty_cycle * ((TIM3 -> ARR) + 1)) / 100;
}
int main() {
  RCC -> AHB1ENR |= (1 << 0);
  GPIOA -> MODER &= ~(3 << 0); //clear pin mode PC2 POT
  GPIOA -> MODER |= (3 << 0); //set pin analog mode (11)

  /* setup ADC2*/
  RCC -> APB2ENR |= (1 << 8); //Enable ADC1 clock - ADC1 connected to APB2 BUS
  ADC1 -> CR2 = 0; //0:Disable ADC conversion and go to power down mode

  //ADC regular sequence register 3
  //SQR3 - Its 4:0 SQ1[4:0]:1st conversion in regular sequence

  ADC1 -> SQR3 |= (0 << 0); // conversion sequence starts at ch1
  //SQR1 is 0000: 1 conversion

  ADC1 -> SQR1 = 0; //conversion sequence length is 1
  ADC1 -> CR2 |= 1; //enable ADC1
  pc6_tim3_pwm_config();

  while (1) {
    ADC1 -> CR2 |= (1 << 30); // Start of conversion at regular channel
    while (!(ADC1 -> SR & 2)) {} //wait for conversion to complete
    result = ADC1 -> DR;

    //VOLTAGE = (result / 4095.0) * 3.3;

    if ((result > 1024) & (result <= 2048)) {
      tim3_pc6_set_dutycycle(1000, 25, 1);
      for (int i = 0; i < 3000000; i++);
    }
    else if ((result > 2048) & (result <= 3072)) {
      tim3_pc6_set_dutycycle(1000, 50, 1);
      for (int i = 0; i < 3000000; i++);
    }
    else if ((result > 3072) & (result <= 4096)) {
      tim3_pc6_set_dutycycle(1000, 100, 1);
      for (int i = 0; i < 3000000; i++);
    }
    else {
      tim3_pc6_set_dutycycle(1000, 0, 1);
      for (int i = 0; i < 3000000; i++);
    }
  }
}
