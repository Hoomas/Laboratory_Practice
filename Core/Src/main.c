#include "main.h"

int main(void)
{
    GPIO_init_With_Myself_Macros ();
    GPIO_init_With_Myself_Macros2 ();
    while (1)
    {
        BIT_SET (GPIOB_BSRR, GPIO_PIN_SET_14);
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_13)) // опереатор if, в котором логически умножается IDR на значение
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_7);
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);   // Включает светодиод BSSR, если нажата кнопка
        }
        else
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_14);
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_7);
        }
    }
}