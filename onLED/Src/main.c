#include <stdint.h>

int main(void)
{
    uint32_t *clockRegB = (uint32_t*)0x40023830; // AHB1ENR address (RCC->AHBENR)
    uint32_t *clockRegC = (uint32_t*)0x40023830; // AHB1ENR address (RCC->AHBENR)
    uint32_t *moderRegC = (uint32_t*)0x42020800; // GPIOC->MODER for LED
    uint32_t *moderRegB = (uint32_t*)0x42020400; // GPIOB->MODER for Button switch
    uint32_t *odrRegC = (uint32_t*)0x42020814;   // GPIOC->ODR for LED
    uint32_t *idrRegB = (uint32_t*)0x42020410;   // GPIOB->IDR for Button switch
    uint32_t *pupdrRegB = (uint32_t*)0x4202040C; // GPIOB->PUPDR for Button switch

    // Enable clock for Port B (Button)
    *clockRegB |= (1 << 1); // Enable clock for GPIOB

    // Enable clock for Port C (LED)
    *clockRegC |= (1 << 2); // Enable clock for GPIOC

    // Configure PC6 as output
    *moderRegC |= (1 << 12); // Set bit 12 for output mode
    *moderRegC &= ~(1 << 13); // Clear bit 13 for output mode

    // Configure PB7 as input with no pull-up/pull-down
    *moderRegB &= ~(3 << 14); // Clear bits 14 and 15 for input mode
    *pupdrRegB &= ~(3 << 14); // No pull-up/pull-down

    while (1)
    {
        uint8_t btnStatus = (uint8_t)(*idrRegB & (1 << 7)); // Read from PB7
        if (btnStatus == 0) // Use == for comparison instead of =
        {
            *odrRegC &= ~(1 << 6); // LED connected via PC6 is ON
        }
        else
        {
            *odrRegC |= (1 << 6); // LED connected via PC6 is OFF
        }
    }
}
