#include "init.h"


void GPIO_Init (void)
{

    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN);
    (void)RCC->AHB1ENR;
    //PB0 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0, (0x1u << GPIO_MODER_MODE0_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_0);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0, (0x1u << GPIO_OSPEEDR_OSPEED0_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD0, (0x0u << GPIO_PUPDR_PUPD0_Pos));

    //PB7 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7, (0x1u << GPIO_MODER_MODE7_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_7);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED7, (0x1u << GPIO_OSPEEDR_OSPEED7_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR7);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD7, (0x0u << GPIO_PUPDR_PUPD7_Pos));
    //PB14 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14, (0x1u << GPIO_MODER_MODE14_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_14);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED14, (0x1u << GPIO_OSPEEDR_OSPEED14_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD14, (0x0u << GPIO_PUPDR_PUPD14_Pos));

    //PB8 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE8, (0x1u << GPIO_MODER_MODE8_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_8);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED8, (0x1u << GPIO_OSPEEDR_OSPEED8_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR8);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD8, (0x0u << GPIO_PUPDR_PUPD8_Pos));

    //PB11 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE11, (0x1u << GPIO_MODER_MODE11_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_11);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED11, (0x1u << GPIO_OSPEEDR_OSPEED11_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR11);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD11, (0x0u << GPIO_PUPDR_PUPD11_Pos));

    //PB10 - out
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE10, (0x1u << GPIO_MODER_MODE10_Pos));
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_10);
    MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED10, (0x1u << GPIO_OSPEEDR_OSPEED10_Pos));
    CLEAR_BIT(GPIOB->BSRR, GPIO_BSRR_BR10);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD10, (0x0u << GPIO_PUPDR_PUPD10_Pos));
}

   

void CLK_CLEAR(void)
{
 MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U); 
 CLEAR_REG(RCC->CFGR); 
 while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET); 
 CLEAR_BIT(RCC->CR, RCC_CR_PLLON); 
 while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET); 
 CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON); 
 while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET); 
 CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);   
}

void RCC_Init(void)
{
    //RCC_CR_init
    SET_BIT(RCC->CR, RCC_CR_HSEON); //Запускаем внешний кварцевый резонатор 
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET); //Ждём пока он запустится 
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); //Сбросим бит байпаса в 0, если вдруг там что-то лежит 
    SET_BIT(RCC->CR, RCC_CR_CSSON); //Запустим Clock detector

    //RCC_PLLCFGR
    CLEAR_REG(RCC->PLLCFGR); 
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE); 
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_2); //Выставляем предделитель входной частоты PLL на 4 
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7); //Настраиваем умножение частоты, полученной после деления (частоты VCO) на х180 
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk); //Настраиваем предделитель получившейся частоты после умножения. Иными словами, получаем итоговую частоту PLL 
    SET_BIT(RCC->CR, RCC_CR_PLLON); //Запустим PLL 
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY)); //Ждём запуска PLL

    //RCC_CFGR
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); //Выбираем PLL в качестве System Clock 
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1); //Предделитель AHB, без делителя 
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4); //Предделитель APВ1, делим на 4 
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2); //Предделитель APВ2, делим на 2 
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO2PRE, RCC_CFGR_MCO2PRE_Msk); //Предделитель на выходе MCO2 (PC9) = 5 
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2); //Настраиваем на выход MCO2 - System clock
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);

}

void ITR_init(void)
{ 
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); //Включение тактирования периферии SYSCFG 
    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC); //Настройка мультиплексора на вывод линии прерывания EXTI13 на PC13 
    SET_BIT(EXTI->IMR, EXTI_IMR_MR13); //Настройка маскирования 13 линии 
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13); //Настройка детектирования нарастающего фронта 13 линии 
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13); //Настройка детектирования спадающего фронта 13 линии 
    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); //Установка 0 приоритета прерывания для вектора EXTI15_10
    NVIC_EnableIRQ(EXTI15_10_IRQn); //Включение прерывания по вектору EXTI15_10 
}

void SysTick_Init(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //На всякий случай, предварительно, выключим счётчик 
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk); //Разрешаем прерывание по системному таймеру 
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); //Источник тактирования будет идти из AHB без деления 
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, (180000000 / 1000) - 1 << SysTick_LOAD_RELOAD_Pos); //Значение с которого начинается счёт, эквивалентное 1 кГц 
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, 0 << SysTick_VAL_CURRENT_Pos); //Очистка поля 
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //Включим счётчик
}