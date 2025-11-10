

#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"

#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

//led pins PB10(69), PB11(70), PB12(73)
//button pins PB10(69), PB6(136)


void GPIO_init__Memory(void);


void Led_init(void);
void Buttons_Init(void);
void PB10_out(void);
void PB10_inp(void);


#define RCC_AHB1ENR         *(uint32_t *)(0x40023800UL + 0x30UL)
#define RCC_GPIOB_EN        0x02UL
#define RCC_GPIOC_EN        0x04UL

#define GPIOB_MODER         *(uint32_t *)(0x40020400UL + 0x00UL)
#define GPIOB_OTYPER        *(uint32_t *)(0x40020400UL + 0x04UL)
#define GPIOB_OSPEEDR       *(uint32_t *)(0x40020400UL + 0x08UL)
#define GPIOB_PUPDR         *(uint32_t *)(0x40020400UL + 0x0CUL)
#define GPIOB_BSRR          *(uint32_t *)(0x40020400UL + 0x18UL)

#define GPIOC_IDR           *(uint32_t *)(0x40020800UL + 0x10UL)


#define GPIO_PIN_OUT_6      0x00001000UL  //13:12
#define GPIO_PIN_MED_6      0x00001000UL  // medium speed
#define GPIO_PIN_SET_6      0x00000040UL  
#define GPIO_PIN_RESET_6    0x00400000UL 


#define GPIO_PIN_OUT_10     0x00100000UL  //21:20
#define GPIO_PIN_MED_10     0x00100000UL  // medium speed
#define GPIO_PIN_SET_10     0x00000400UL 
#define GPIO_PIN_RESET_10   0x04000000UL 
#define GPIO_PIN_READ_10    0x00000400UL
#define GPIO_PIN_PULLDN_10  0x00200000UL 
#define GPIO_PIN_INP_NI_10  0x00300000UL // not inversed



#define GPIO_PIN_OUT_11     0x400000UL // 22:23
#define GPIO_PIN_MED_11     0x400000UL // medium speed
#define GPIO_PIN_SET_11     0x800UL 
#define GPIO_PIN_RESET_11   0x8000000UL

#define GPIO_PIN_OUT_12     0x01000000UL  //25:24
#define GPIO_PIN_MED_12     0x01000000UL  // medium speed
#define GPIO_PIN_SET_12     0x00001000UL  
#define GPIO_PIN_RESET_12   0x10000000UL  

#define GPIO_PIN_OUT_15     0x40000000UL  // 31:30
#define GPIO_PIN_MED_15     0x40000000UL  // medium speed
#define GPIO_PIN_SET_15     0x00008000UL  
#define GPIO_PIN_RESET_15   0x80000000UL  





#define GPIO_OFF            0x00UL

#define BIT_SET(REG, BIT)   ((REG) |= (BIT))
#define BIT_READ(REG, BIT)  ((REG) & (BIT))

