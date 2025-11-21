#include "init.h"
// #include "it_handlers.h"

#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"

#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

void blink(uint32_t bitmask, uint8_t freq);
void blink2(uint32_t bitmask1, uint32_t bitmask2, uint8_t freq);


void TIM_Init(void);
void ADC_Init(void);
void GPIO_Init(void);