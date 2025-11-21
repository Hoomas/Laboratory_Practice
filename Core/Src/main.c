#include "main.h"
//PB0 - led
//PB1 - pot

uint16_t ADC_Read(void) {
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART); 
    while(!(READ_BIT(ADC1->SR, ADC_SR_EOC)));
    return ADC1->DR; 
}

uint16_t adc =0;
uint32_t enc;
uint32_t duty;
int main(void) {
    GPIO_Init();
    ADC_Init();
    TIM_Init();
    TIM2->CNT = 0;
    uint32_t enc = 0;
    uint8_t led_count = 0;
    uint16_t adc = 0;
    uint16_t brightness = 0;
    while(1) {
        adc = ADC_Read();
        brightness = adc / 4; 
        if (brightness > 1000) brightness = 1000;
        enc = TIM2->CNT;
        int position = (int16_t)enc / 2; 

        if (position < 0) {
            position = 0;
            TIM2->CNT = 0; 
        }
        if (position > 6) {
            position = 6;
            TIM2->CNT = 6 * 2;
        }
        led_count = position;
        if (led_count >= 1) TIM9->CCR1 = brightness;
        else    TIM9->CCR1 = 0;
        if (led_count >= 2) TIM9->CCR2 = brightness;
        else    TIM9->CCR2 = 0;
        if (led_count >= 3) TIM1->CCR1 = brightness;
        else    TIM1->CCR1 = 0;
        if (led_count >= 4) TIM1->CCR2 = brightness;
        else    TIM1->CCR2 = 0;
        if (led_count >= 5) TIM1->CCR3 = brightness;
        else    TIM1->CCR3 = 0;
        if (led_count >= 6) TIM1->CCR4 = brightness;
        else    TIM1->CCR4 = 0;
        

    
    } 
}  