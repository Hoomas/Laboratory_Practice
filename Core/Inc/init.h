

#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"

#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

//led pins PB10(69), PB11(70), PB12(73)
//button pins PB10(69), PB6(136)


// void GPIO_init__Memory(void);



void TIM_Init(void);
void ADC_Init(void);
void GPIO_Init(void);

uint16_t ADC_Read(void);
// void CLK_CLEAR(void);
// void RCC_Init(void);
// void ITR_init(void);
// void SysTick_Init(void);

