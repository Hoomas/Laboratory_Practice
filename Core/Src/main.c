#include "main.h"
//1 кнопка 3 частоты
//2 кнопка включает последовательно 4 светодиода(циклично, короткое нажатие 1 12 123 1234 1 )
//выбор светодиода, для которого выбирается частота(длинное нажатие имзенеие порядкового номера, если не настраивать, то базовя, можно настроить свтодтод. даже если он сейчас не горит) без таймеров и прерываний



//  GPIO_BSRR_BR0
//  GPIO_BSRR_BS0


// PB0, PB7, PB14 - plate
// Pb8, PbB10, Pb11 - added

//PC6 - button


/*
int main(void)
{
    Led_init();
    Buttons_Init();
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR10);    

    while (1)
    {
        
        if (upndown(GPIO_IDR_ID6))
        {
            btn2 = 1;
                
                btn2_state = !btn2_state;
                delay_cycles(500);
        }
        btn2 = 0;

        if (btn2_state == 0)
        {
 
            PB10_inp();

            if (upndown(GPIO_IDR_ID10))
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
                
                if (upndown(GPIO_IDR_ID6))
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


/*
uint8_t flag1 =0;
uint8_t flag2 =0;
uint8_t current_led_indx = 2;
uint8_t led_count = 0;
uint8_t timerbutton1,timerbutton2,led_index = 0;
   


uint32_t i =0;
int main(void)
{
   
 GPIO_init_led_pb7_blue ();
 GPIO_init_led_pb14_red ();
 GPIO_init_led_pb0_green ();
 Buttons_Init();
 
        while (1)
    {


       if(READ_BIT(GPIOC_IDR,GPIO_IDR_ID12 ))
       {
            btn1 = 1;
            timerbutton1++;
       }
       else
       {
        if(timerbutton1>= 5)
        {
           
            
            
            btn1 = 1;
            if(choose<3){choose++;}
            else{choose = 1;}
            
        }
        if(timerbutton1>= 1 && timerbutton1 < 5)
        {
            if(quanty<3){quanty++;}
            else{quanty=1;}
        }
        
        timerbutton1 = 0;
        flag1 = 0;
        btn1 =0;
       }
       if (READ_BIT(GPIOC_IDR, GPIO_IDR_ID13))
       {
        btn2 = 1;
            switch(choose)
            {
                case 1:
                if(PB11_spd<3) {PB11_spd++;}
                else{PB11_spd = 1;}
                
                break;
                case 2: 
                if(PB12_spd<3) {PB12_spd++;}
                else{PB12_spd = 1;}
                break;
                case 3: 
                if(PB13_spd<3) {PB13_spd++;}
                else{PB13_spd = 1;}

                break;

            }
       }
       btn2 =0;
        switch(quanty)
        {
            case 1: 
            blink(GPIO_BSRR_BS0, PB11_spd);
            break;
            case 2:
            blink(GPIO_BSRR_BS0, PB11_spd);
            blink(GPIO_BSRR_BS7, PB12_spd);
            break;
            case 3:
            blink(GPIO_BSRR_BS0, PB11_spd);
            blink(GPIO_BSRR_BS7, PB12_spd);
            blink(GPIO_BSRR_BS14, PB13_spd);
            break;
            


        }

    
    }
    return 1;
}



while (1)
    {
       if (BIT_READ(GPIOC_IDR, GPIO_PIN_8))
       {
        flag1 = 1;
        current_led_indx = (current_led_indx + 1) % 3;
        if(led_count == 2){
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0 |GPIO_BSRR_BR7 | GPIO_BSRR_BR14 );
            for(volatile uint32_t i = 0; i < 100000; i++){}}
        UpdateLEDs();
        for(volatile uint32_t i = 0; i < 1000000; i++);
       }
       else
       {
        flag1 = 0;
       }
       if (BIT_READ(GPIOC_IDR, GPIO_PIN_13))
       {
        flag2 = 1;
        led_count = ((led_count+1))%3;
       
    
        UpdateLEDs();
    
       for(volatile uint32_t i = 0; i < 1000000; i++);
       }
       else
       {
        flag2 = 0;
       }
    }
       */


volatile uint32_t GlobalTickCount;
uint8_t mode = 1;
uint8_t freq_mode;
uint8_t LedState = 0;
volatile uint32_t BtnStartTick;
uint8_t i;
void blink(uint32_t bitmask, uint8_t freq) //Freq in ms
{
    SET_BIT(GPIOB->BSRR, bitmask);
    milis(freq);
    SET_BIT(GPIOB->BSRR, bitmask<<16U);
}

void blink2(uint32_t bitmask1, uint32_t bitmask2, uint8_t freq) //Freq in ms
{
    SET_BIT(GPIOB->BSRR, bitmask1);
    SET_BIT(GPIOB->BSRR, bitmask2);
    milis(freq/2);
    SET_BIT(GPIOB->BSRR, bitmask1<<16U);
    SET_BIT(GPIOB->BSRR, bitmask2<<16U);
    milis(freq/2);
}

int main(void)
{
    uint32_t led_bitmasks[6] = {GPIO_BSRR_BS0, GPIO_BSRR_BS7, GPIO_BSRR_BS14, GPIO_BSRR_BS8, GPIO_BSRR_BS10, GPIO_BSRR_BS11};
    uint16_t freq1[3] = {2500, 526, 385};
    uint16_t freq2[3] = {3300, 625, 435};
    GPIO_Init();
    CLK_CLEAR();
    RCC_Init();
    ITR_init();
    SysTick_Init();

    while(1)
    {
        switch( mode)
        {
            case 1:
                for( i = 0; i<6; i++)
                {
                    blink(led_bitmasks[i],freq1[freq_mode]);
                }
            break;

            case 2:
                
            for(i = 0; i<6; i++)
            {
                blink2(led_bitmasks[i], led_bitmasks[i+3],freq2[freq_mode]);
            }
            break;
        }
    }


}