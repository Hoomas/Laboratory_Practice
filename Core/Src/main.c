#include "main.h"


static void delay_cycles(volatile uint32_t t) //time in ms
{
    while (t--) __NOP();
}

static uint8_t debounce(uint32_t bitmask)
{
    for (int i = 0; i < 5; i++)
    {
        if (BIT_READ(GPIOB->IDR, bitmask))
            return 0;
        delay_cycles(5000);
    }
    return 1;
}


uint8_t btn1 = 0;
uint8_t btn2 = 0;
uint8_t btn2_state = 0;   // 0 = PB10 input, 1 = PB10 output
uint8_t led_flag = 0;
int main(void)
{
    Led_init();
    Buttons_Init();
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR10);    

    while (1)
    {
        
        if (debounce(GPIO_IDR_ID6))
        {
            btn2 = 1;
                
                btn2_state = !btn2_state;
                delay_cycles(500);
        }
        btn2 = 0;

        if (btn2_state == 0)
        {
 
            PB10_inp();

            if (debounce(GPIO_IDR_ID10))
            {
                btn1++;
                
                    switch(btn1)
                    {
                    case 1:
                        SET_BIT(GPIOB->BSRR, GPIO_PIN_SET_11);
                        SET_BIT(GPIOB->BSRR,  GPIO_PIN_RESET_12);
                        break;
                    case 2:
                        SET_BIT(GPIOB->BSRR, GPIO_PIN_SET_11);
                        SET_BIT(GPIOB->BSRR,  GPIO_PIN_SET_12);
                        break;
                    case 3:
                        btn1 = 0;
                        SET_BIT(GPIOB->BSRR,  GPIO_PIN_RESET_11);
                        SET_BIT(GPIOB->BSRR,  GPIO_PIN_RESET_12);
                        break;
                    }
                    delay_cycles(5000);
                
            }
            
        }
        else
        {
            PB10_out();

            BIT_SET(GPIOB_BSRR, GPIO_BSRR_BS10);
            BIT_SET(GPIOB_BSRR, GPIO_BSRR_BR11);
            BIT_SET(GPIOB_BSRR, GPIO_BSRR_BR12);

    
            while (1)
            {
                
                if (debounce(GPIO_IDR_ID6))
                {
                        btn2 = 1;
                        BIT_SET(GPIOB_BSRR, GPIO_BSRR_BR10);
                        PB10_inp();
                        btn2_state = 0;
                        delay_cycles(500000);
                        break;
                }
                
            }
        }
    }
}

/*
uint8_t flag = 0 ;
int main()
{
    Led_init();
    Buttons_Init();
    PB10_out();
   
    while(1)
    {
        
           
             SET_BIT(GPIOB->BSRR, GPIO_PIN_SET_12);
             SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS11);
             SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS10);
        

        SET_BIT(GPIOB->BSRR, GPIO_PIN_RESET_12);
        if(!READ_BIT(GPIOB->IDR, GPIO_IDR_ID6))
        {flag++;}

    }
    
} 
    */
