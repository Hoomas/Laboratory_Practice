#include "it_handlers.h"

#define DELAY_BUTTON_FILTER 250


uint8_t BtnCount;
extern volatile uint32_t GlobalTickCount;
extern volatile uint32_t BtnStartTick;
extern uint8_t mode;
extern uint8_t freq_mode;

volatile uint32_t ExternInterruptTickCount;

void EXTI15_10_IRQHandler(void)
{

    if(ExternInterruptTickCount >= DELAY_BUTTON_FILTER)
    { 
        BtnCount++; 

    }

    if(BtnCount == 2)
    {
        
        if(ExternInterruptTickCount  >= 2000)
        {
            if(freq_mode <2){freq_mode++;} 
            else{ freq_mode = 0;}


            
        }
        if(ExternInterruptTickCount  < 2000 && ExternInterruptTickCount !=0)
        {
            if(mode < 2) {mode++;}
            else {mode = 1;}
        

        }
         
    }
    if(BtnCount>2)
         { BtnCount = 1; ExternInterruptTickCount = 0;}
    ExternInterruptTickCount = 0;
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
}

void SysTick_Handler(void)
{
    ExternInterruptTickCount++;
    GlobalTickCount++;

}

void milis(uint32_t delay)
{
  uint32_t start = GlobalTickCount;                
while ((uint32_t)(GlobalTickCount - start) < delay) {}
}
