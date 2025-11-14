#include "main.h"
//1 кнопка 3 частоты
//2 кнопка включает последовательно 4 светодиода(циклично, короткое нажатие 1 12 123 1234 1 )
//выбор светодиода, для которого выбирается частота(длинное нажатие имзенеие порядкового номера, если не настраивать, то базовя, можно настроить свтодтод. даже если он сейчас не горит) без таймеров и прерываний


 static void delay_cycles(volatile uint32_t t)
{
    while (t--) __NOP();
}

static uint8_t debounce(uint32_t bitmask, uint32_t time)
{

    for (int i = 0; i < 5; i++)
    {
        if (READ_BIT(GPIOC_IDR, bitmask))
            return 0;
        delay_cycles(time);
    }
    return 1;
}

static uint8_t upndown(uint32_t bitmask)
{
    uint8_t flag = 0;
    if(debounce(bitmask, 10))
    {
        flag++;
    }
    if(!debounce(bitmask, 10))
    {flag++;}
    if(flag>=2){return 1;}
    else{return 0;}
}

static uint8_t upndown_l(uint32_t bitmask)
{
    uint8_t flag = 0;
    if(debounce(bitmask, 8))
    {
        flag++;
    }
    if(!debounce(bitmask, 8))
    {flag++;}
    if(flag>=2){return 1;}
    else{return 0;}
}

static void blink(uint32_t bitmask, uint8_t speed)
{
    SET_BIT(GPIOB->BSRR, bitmask);
    switch(speed)
    {
        case 1 : delay_cycles(100000); break;
        case 2: delay_cycles(500000); break;
        case 3: delay_cycles(2500000); break;
    }
    BIT_SET(GPIOB->BSRR, bitmask << (16U));
    switch(speed)
    {
        case 1 : delay_cycles(100000); break;
        case 2: delay_cycles(500000); break;
        case 3: delay_cycles(250000); break;
    }
}

//  GPIO_BSRR_BR0
//  GPIO_BSRR_BS0
static void spdup( uint8_t *var )
{
   uint8_t spd  = *var;
   spd++;
    if(spd>3)
    {
        spd =1 ;
    }

}

// static void quant( uint8_t *var )
// {
//    uint8_t spd  = *var;
//    spd++;
//     if(spd>4)
//     {
//         spd =1 ;
//     }

// }

uint8_t btn1 = 0;
uint8_t btn2 = 0;
uint8_t choose = 1;
uint8_t quanty = 1;
uint8_t PB11_spd = 1;
uint8_t PB12_spd = 1;
uint8_t PB13_spd = 1;
uint8_t PB15_spd = 1;


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



/*while (1)
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