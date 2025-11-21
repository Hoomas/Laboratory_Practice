#include "init.h"
    //  PA0 CLK PB3 DT - enc
    // PB1 - potenc
    // LED PE5, PE6, PE9, PE11, PE13, PE14

    

void GPIO_Init(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOEEN);

    
    // PA0
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER0, GPIO_MODER_MODER0_1); // AF mode
    MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0, GPIO_PUPDR_PUPDR0_0); // Pull-Up
    MODIFY_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL0, 0x01 << GPIO_AFRL_AFSEL0_Pos); // AF

    // PB3 
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER3, GPIO_MODER_MODER3_1); // AF
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPDR3, GPIO_PUPDR_PUPDR3_0); // Pull-Up
    MODIFY_REG(GPIOB->AFR[0], GPIO_AFRL_AFSEL3, 0x01 << GPIO_AFRL_AFSEL3_Pos); // AF

    // PB1
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER1, GPIO_MODER_MODER1);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPDR1, 0);


    uint32_t pwm_pins = GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER9 |  GPIO_MODER_MODER11 | GPIO_MODER_MODER13 | GPIO_MODER_MODER14;
    CLEAR_BIT(GPIOE->MODER, pwm_pins);

    uint32_t pwm_af_mode = GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER9_1 |  GPIO_MODER_MODER11_1 | GPIO_MODER_MODER13_1 | GPIO_MODER_MODE14_1;
    SET_BIT(GPIOE->MODER, pwm_af_mode);

    // PE5, PE6 -> TIM9 (AF3)
    MODIFY_REG(GPIOE->AFR[0], GPIO_AFRL_AFSEL5, 0x03 << GPIO_AFRL_AFSEL5_Pos);
    MODIFY_REG(GPIOE->AFR[0], GPIO_AFRL_AFSEL6, 0x03 << GPIO_AFRL_AFSEL6_Pos);

    // PE9, PE11, PE13, PE14 -> TIM1 (AF1)
    MODIFY_REG(GPIOE->AFR[1], GPIO_AFRH_AFSEL9,  0x01 << GPIO_AFRH_AFSEL9_Pos);
    MODIFY_REG(GPIOE->AFR[1], GPIO_AFRH_AFSEL11, 0x01 << GPIO_AFRH_AFSEL11_Pos);
    MODIFY_REG(GPIOE->AFR[1], GPIO_AFRH_AFSEL13, 0x01 << GPIO_AFRH_AFSEL13_Pos);
    MODIFY_REG(GPIOE->AFR[1], GPIO_AFRH_AFSEL14, 0x01 << GPIO_AFRH_AFSEL14_Pos);
}


void TIM_Init(void)
{
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN); 
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN | RCC_APB2ENR_TIM9EN);

    TIM2->PSC = 0;
    TIM2->ARR = 0xFFFFFFFF; //max U number
    
    MODIFY_REG(TIM2->CCMR1, TIM_CCMR1_CC1S | TIM_CCMR1_CC2S, TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0); //input mode
    
    MODIFY_REG(TIM2->CCMR1, TIM_CCMR1_IC1F | TIM_CCMR1_IC2F, (0xF << TIM_CCMR1_IC1F_Pos) | (0xF << TIM_CCMR1_IC2F_Pos)); // filtration
    
    MODIFY_REG(TIM2->SMCR, TIM_SMCR_SMS, TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1); //rotation side
    
    SET_BIT(TIM2->CR1, TIM_CR1_CEN);

    TIM9->PSC = 179; 
    TIM9->ARR = 999;
    MODIFY_REG(TIM9->CCMR1, TIM_CCMR1_OC1M | TIM_CCMR1_OC2M, (0x6 << TIM_CCMR1_OC1M_Pos) | (0x6 << TIM_CCMR1_OC2M_Pos));
    

    SET_BIT(TIM9->CCMR1, TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);
    SET_BIT(TIM9->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E);
    SET_BIT(TIM9->CR1, TIM_CR1_ARPE | TIM_CR1_CEN);

    TIM1->PSC = 179; 
    TIM1->ARR = 999; // 1 kHz PWM
    
    // PWM Mode 1 CH1, CH2, CH3, CH4
    MODIFY_REG(TIM1->CCMR1, TIM_CCMR1_OC1M | TIM_CCMR1_OC2M, (0x6 << TIM_CCMR1_OC1M_Pos) | (0x6 << TIM_CCMR1_OC2M_Pos));
    MODIFY_REG(TIM1->CCMR2, TIM_CCMR2_OC3M | TIM_CCMR2_OC4M, (0x6 << TIM_CCMR2_OC3M_Pos) | (0x6 << TIM_CCMR2_OC4M_Pos));
    
    // Preload enable
    SET_BIT(TIM1->CCMR1, TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);
    SET_BIT(TIM1->CCMR2, TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE);
    
    
    SET_BIT(TIM1->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);// out (CH1, CH2, CH3, CH4)
    
    SET_BIT(TIM1->BDTR, TIM_BDTR_MOE);//MOE EN
    
    SET_BIT(TIM1->CR1, TIM_CR1_ARPE | TIM_CR1_CEN);
}


void ADC_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);

    CLEAR_BIT(ADC1->CR2, ADC_CR2_ADON); //adc off
    SET_BIT(ADC->CCR, ADC_CCR_ADCPRE_0); // devide by 4
    MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, 0); //num of channels
    MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, 9 << ADC_SQR3_SQ1_Pos); //first read 
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP9, 4 << ADC_SMPR2_SMP9_Pos); // charging cyles
    SET_BIT(ADC1->CR2, ADC_CR2_ADON); // adc on
    
}


// void CLK_CLEAR(void)
// {
//  MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U); 
//  CLEAR_REG(RCC->CFGR); 
//  while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET); 
//  CLEAR_BIT(RCC->CR, RCC_CR_PLLON); 
//  while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET); 
//  CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON); 
//  while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET); 
//  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   
// }

// void RCC_Init(void)
// {
//     //RCC_CR_init
//     SET_BIT(RCC->CR, RCC_CR_HSEON); //Запускаем внешний кварцевый резонатор 
//     while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET); //Ждём пока он запустится 
//     CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); //Сбросим бит байпаса в 0, если вдруг там что-то лежит 
//     SET_BIT(RCC->CR, RCC_CR_CSSON); //Запустим Clock detector

//     //RCC_PLLCFGR
//     CLEAR_REG(RCC->PLLCFGR); 
//     SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE); 
//     MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_2); //Выставляем предделитель входной частоты PLL на 4 
//     MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7); //Настраиваем умножение частоты, полученной после деления (частоты VCO) на х180 
//     CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk); //Настраиваем предделитель получившейся частоты после умножения. Иными словами, получаем итоговую частоту PLL 
//     SET_BIT(RCC->CR, RCC_CR_PLLON); //Запустим PLL 
//     while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)); //Ждём запуска PLL

//     //RCC_CFGR
//     MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); //Выбираем PLL в качестве System Clock 
//     MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1); //Предделитель AHB, без делителя 
//     MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4); //Предделитель APВ1, делим на 4 
//     MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2); //Предделитель APВ2, делим на 2 
//     MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO2PRE, RCC_CFGR_MCO2PRE_Msk); //Предделитель на выходе MCO2 (PC9) = 5 
//     CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2); //Настраиваем на выход MCO2 - System clock
//     MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);

// }

// void ITR_init(void)
// { 
//     SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); //Включение тактирования периферии SYSCFG 
//     MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC); //Настройка мультиплексора на вывод линии прерывания EXTI13 на PC13 
//     SET_BIT(EXTI->IMR, EXTI_IMR_MR13); //Настройка маскирования 13 линии 
//     SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13); //Настройка детектирования нарастающего фронта 13 линии 
//     SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13); //Настройка детектирования спадающего фронта 13 линии 
//     NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); //Установка 0 приоритета прерывания для вектора EXTI15_10
//     NVIC_EnableIRQ(EXTI15_10_IRQn); //Включение прерывания по вектору EXTI15_10 
// }

// void SysTick_Init(void)
// {
//     CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //На всякий случай, предварительно, выключим счётчик 
//     SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk); //Разрешаем прерывание по системному таймеру 
//     SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); //Источник тактирования будет идти из AHB без деления 
//     MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, (180000000 / 1000) - 1 << SysTick_LOAD_RELOAD_Pos); //Значение с которого начинается счёт, эквивалентное 1 кГц 
//     MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, 0 << SysTick_VAL_CURRENT_Pos); //Очистка поля 
//     SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //Включим счётчик
// }

