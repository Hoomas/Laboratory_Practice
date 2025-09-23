#include <stdint.h>

int main(void){

    *(uint32_t*)(0x40023800 + 0x30) |= 0x02; //TACT B EN 
    //Для включения регистров посылается 16-ти ричная форма двоичного числа нужных регстров(прим. третий и второй регистры, будет число 110 -> 6)
    *(uint32_t*)(0x40020400 + 0x00) |= 0x4000; // GPIO B EN
    *(uint32_t*)(0x40020400 + 0x04) = 0x00; //PURDR to zeroes
    *(uint32_t*)(0x40020400 + 0x08) |= 0x4000; // Speed setup
    *(uint32_t*)(0x40020400 + 0x18) = 0x80; //Light on 
   
 
    while(1){}
  git config --global user.email "you@example.com"
  
}