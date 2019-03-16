#include "os.h"

void delay(unsigned int nCount);
void blinky (void* d);

GPIO_InitTypeDef GPIO_InitStruct;

int main(){
int delay=50;
int delay2=1000;
os_init();
_save_state();
uint32_t* stack=(uint32_t*)malloc(256);
uint32_t* stack2=(uint32_t*)malloc(256);
os_task_init(blinky,(void*)&delay,stack,sizeof(stack));
os_task_init(blinky,(void*)&delay2,stack,sizeof(stack));
os_start(100);
return 0;
}

void blinky (void* d)
{
	int temp=*((int*)d);
    // Enable clock for GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 
    // Configure PA0 as push-pull output
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
 
    while (1)
    {
        /* Toggle LED on PA0 */
        // Reset bit will turn on LED (because the logic is interved)
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        delay(temp);
        // Set bit will turn off LED (because the logic is interved)
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        delay(temp);
    }
}
 
// Delay function
void delay(unsigned int nCount)
{
    unsigned int i, j;
 
    for (i = 0; i < nCount; i++)
        for (j = 0; j < 0x2AFF; j++);
}
