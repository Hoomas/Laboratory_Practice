#include "it_handlers.h"

uint8_t BtnCount;
extern uint8_t LedState;

void EXTI15_10_IRQHandler(void)
{
    BtnCount ++; 
    if(BtnCount >= 2)
    {
        LedState = !LedState;
        BtnCount = 0;
    }

    SET_BIT(EXTI->PR, EXTI_PR_PR13); 
}

