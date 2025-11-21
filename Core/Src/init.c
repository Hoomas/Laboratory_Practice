#include "init.h"
    //  PA0 CLK PB3 DT - enc
    // PB1 - potenc
    // LED PE5, PE6, PE9, PE11, PE13, PE14

   void ADC_Init(void)
{
   
  
 // 1. Тактирование (A, B, E уже включены, ADC1 включен)
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOEEN);
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);

    // ================= НАСТРОЙКА GPIO =================
    
    // --- Потенциометр 1 (PB1) ---
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER1, GPIO_MODER_MODER1); // Analog
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPDR1, 0);

    // --- Потенциометр 2 (PA3) ---
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER3, GPIO_MODER_MODER3); // Analog (11)
    MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPDR3, 0);

    // --- Потенциометр 3 (PA4) ---
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER4, GPIO_MODER_MODER4); // Analog (11)
    MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPDR4, 0);


    // ================= НАСТРОЙКА ADC =================
    
    CLEAR_BIT(ADC1->CR2, ADC_CR2_ADON); // Выключаем для настройки
    
    SET_BIT(ADC->CCR, ADC_CCR_ADCPRE_0); // Делитель частоты /4

    // Настройка длины последовательности
    // Мы будем читать по одному каналу вручную, поэтому L=0 (1 преобразование)
    MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, 0); 

    // Настройка времени выборки (Sampling Time) для всех каналов
    // Канал 9 (PB1), Канал 3 (PA3), Канал 4 (PA4) - все они в регистре SMPR2
    // Ставим 84 цикла (4 -> 100) для стабильности
    MODIFY_REG(ADC1->SMPR2, 
               ADC_SMPR2_SMP9 | ADC_SMPR2_SMP3 | ADC_SMPR2_SMP4, 
               (4 << ADC_SMPR2_SMP9_Pos) | (4 << ADC_SMPR2_SMP3_Pos) | (4 << ADC_SMPR2_SMP4_Pos));

    SET_BIT(ADC1->CR2, ADC_CR2_ADON); // Включаем АЦП

}

uint16_t ADC_Read_Channel(uint8_t channel)
{
    // 1. Выбираем канал
    MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, channel << ADC_SQR3_SQ1_Pos);
    
    // 2. Холостое измерение (чтобы сбросить старый заряд)
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    while(!(READ_BIT(ADC1->SR, ADC_SR_EOC)));
    (void)ADC1->DR; // Читаем и выбрасываем
    
    // 3. Настоящее измерение
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    while(!(READ_BIT(ADC1->SR, ADC_SR_EOC)));
    
    return ADC1->DR; // Возвращаем точный результат
}

void FAN_BUZZER_Init(void)
{
    // 1. Включаем тактирование TIM3 и GPIOB
    // (GPIOB может быть уже включен, но повтор безопасен)
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN); // TIM3 сидит на APB1 (45/90 MHz)

    // ================= НАСТРОЙКА GPIO (PB4, PB5) =================
    
    // Очистка режимов для PB4 и PB5
    GPIOB->MODER &= ~(GPIO_MODER_MODE4 | GPIO_MODER_MODE5);
    
    // Установка режима Alternate Function (10)
    GPIOB->MODER |= (GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1);

    // Настройка AF2 (TIM3) для PB4 и PB5
    // AF2 = 0x02. Записываем в AFRL (т.к. пины 0-7)
    
    // PB4
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL4);          // Очистка
    GPIOB->AFR[0] |= (0x2 << GPIO_AFRL_AFSEL4_Pos); // AF2

    // PB5
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL5);          // Очистка
    GPIOB->AFR[0] |= (0x2 << GPIO_AFRL_AFSEL5_Pos); // AF2

    // ================= НАСТРОЙКА TIM3 =================
    
    TIM3->PSC = 89; // (90 MHz / (89+1)) = 1 MHz
    
    TIM3->ARR = 1000; // Дефолтный период = 1000 мкс (1 кГц)

    // --- Канал 1 (Вентилятор) - ШИМ Mode 1 ---
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M; 
    TIM3->CCMR1 |= (0x6 << TIM_CCMR1_OC1M_Pos); // PWM Mode 1
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;             // Preload Enable
    
    // --- Канал 2 (Бипер) - ШИМ Mode 1 ---
    TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM3->CCMR1 |= (0x6 << TIM_CCMR1_OC2M_Pos); // PWM Mode 1
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;             // Preload Enable

    // Включение выходов
    SET_BIT(TIM3->CCER, TIM_CCER_CC1E | TIM_CCER_CC2E);
    
    // Запуск таймера
    SET_BIT(TIM3->CR1, TIM_CR1_ARPE | TIM_CR1_CEN);
}


uint16_t read_POT1(void)
{
    // Настраиваем одно преобразование на канале 0
    MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1_Msk, 0 << ADC_SQR3_SQ1_Pos);
    
    // Запускаем преобразование
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    
    // Ждем завершения
    while (!(ADC1->SR & ADC_SR_EOC));
    
    // Читаем результат
    return ADC1->DR;
}

// Функция для чтения POT2 (PA1, канал 1)
uint16_t read_POT2(void)
{
    // Настраиваем одно преобразование на канале 1
    MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1_Msk, 1 << ADC_SQR3_SQ1_Pos);
    
    // Запускаем преобразование
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    
    // Ждем завершения
    while (!(ADC1->SR & ADC_SR_EOC));
    
    // Читаем результат
    return ADC1->DR;
}

// Функция для чтения POT3 (PA2, канал 2)
uint16_t read_POT3(void)
{
    // Настраиваем одно преобразование на канале 2
    
    
    // Запускаем преобразование
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    
    // Ждем завершения
    while (!(ADC1->SR & ADC_SR_EOC));
    
    // Читаем результат
    return ADC1->DR;
}