#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config()
{
	RCC->CR |= 0x00030000; // HSEON and HSEONRDY enable
	RCC->CR |= 0x00080000; //CSS enable
	RCC->PLLCFGR |= 0x00040000; // PLL e HSE sectik
	RCC->PLLCFGR |= 0x00000004; // PLL M=4
	RCC->PLLCFGR |= 0x00005A00; // PLL N = 168
	RCC->PLLCFGR |= 0x00000000; // PLL P =2
	RCC->CFGR |= 0x00000000;    //AHB Prescaler =1
	RCC->CFGR |= 0x00080000;    //AHB Prescaler =2
	RCC->CFGR |= 0x00001400;    //AHB Prescaler =4
	RCC->CIR |= 0x00080000;     //HSERDY Flag clear
	RCC->CIR |= 0x00800000;     //CSS Flag clear
}

void GPIO_Config()
{
	RCC->AHB1ENR = 0x00000009; //GPIOA ve GPIOD portlari aktif edildi
	GPIOD->MODER = 0x55000000; //GPIOD pin12...pin15 output
	GPIOD->OTYPER = 0x00000000; //Push-Pull secildi
	GPIOD->OSPEEDR = 0xFF000000; //100MHz secildi
	GPIOD->PUPDR = 0x00000000; //No pull no down
}

void EXTI_Config()
{
	RCC->APB2ENR = 0x00004000; //SYSCFG active

	SYSCFG ->EXTICR[0]= 0x00000000; //Kesme yapmak icin A portu ayarlandi

	NVIC_EnableIRQ(EXTI0_IRQn); //Interruptlar aktif edildi
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	NVIC_SetPriority(EXTI0_IRQn, 0); //Interruplara oncelik siralari verildi
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);

	EXTI->IMR = 0x00000007; //Interruplar interrup olarak ayarladi event olarak degil
	EXTI->RTSR = 0x00000007; //Yukselen kenar tetigi ayarlandi
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler(){

	if(EXTI->PR &0x00000001) //kesme bayragi kontrol edildi
	{
		GPIOD ->ODR =0x00001000; //d portunun 12. pini aktif edildi
		delay(336000000);
		EXTI->PR = 0x00000001; //kesme bayragi temizlendi
	}
}

void EXTI1_IRQHandler(){

	if(EXTI->PR &0x00000002) //kesme bayragi kontrol edildi
	{
		GPIOD ->ODR =0x00002000; //d portunun 13. pini aktif edildi
		delay(336000000);
		EXTI->PR = 0x00000002; //kesme bayragi temizlendi
	}
}

void EXTI2_IRQHandler(){

	if(EXTI->PR &0x00000004) //kesme bayragi kontrol edildi
	{
		GPIOD ->ODR =0x00004000; //d portunun 14. pini aktif edildi
		delay(336000000);
		EXTI->PR = 0x00000004; //kesme bayragi temizlendi
	}
}

int main(void)
{
  CLK_Config();
  GPIO_Config();
  EXTI_Config();
  while (1)
  {
	  GPIOD->ODR = 0x0000F000; //GPIOD pin12...pin15 pinleri aktif edildi board uzerindeki ledler yaniyo
  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
