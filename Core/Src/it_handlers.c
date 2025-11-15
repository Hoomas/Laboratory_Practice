#include "it_handlers.h"

#define DELAY_BUTTON_FILTER 100


uint8_t BtnCount;
extern uint8_t LedState;
extern uint16_t GlobalTickCount;
extern uint16_t BtnStartTick;
extern uint8_t mode;
extern uint8_t freq_mode;

uint16_t ExternInterruptTickCount;

void EXTI15_10_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR13); //Сброс флага прерывания 
    if(ExternInterruptTickCount >= DELAY_BUTTON_FILTER)
    { //Выполнится, когда пройдёт 100 мс с момента обнуления данной переменной 
        BtnCount++; //Изменение состояния кнопки 
        ExternInterruptTickCount = 0;
        if(BtnCount == 1 )BtnStartTick = GlobalTickCount;
    }
    
    if(BtnCount >= 2)
    {
        BtnCount = 0;
        if(BtnStartTick - GlobalTickCount >= 2000000)
        {
            if(freq_mode <3)freq_mode++;
            else freq_mode = 0;
        }
        else
        {
            if(mode < 2) mode++;
            else mode = 1;
        }
        
    }


}

void SysTick_Handler(void)
{
    ExternInterruptTickCount++;
    GlobalTickCount++;

}

void milis(uint32_t delay)
{
    uint16_t StartTickCount;
    StartTickCount= GlobalTickCount;
    while(GlobalTickCount - StartTickCount < delay*1000){}

}