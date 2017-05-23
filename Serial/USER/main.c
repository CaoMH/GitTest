#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruce;
	USART_InitTypeDef USART_Initstruce;
	NVIC_InitTypeDef NVIC_Initstruce;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_Initstruce.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstruce.GPIO_Pin = GPIO_Pin_9;
	GPIO_Initstruce.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_Initstruce);
	
	
	GPIO_Initstruce.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Initstruce.GPIO_Pin = GPIO_Pin_10;
	GPIO_Initstruce.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_Initstruce);

	USART_Initstruce.USART_BaudRate = 115200;
	USART_Initstruce.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstruce.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Initstruce.USART_Parity = USART_Parity_No;
	USART_Initstruce.USART_StopBits = USART_StopBits_1;
	USART_Initstruce.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_Initstruce);
	USART_Cmd(USART1,ENABLE);
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_Initstruce.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Initstruce.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstruce.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstruce.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_Initstruce);



}
	void USART1_IRQHandler(void)
	{
		u8 Res;
		if(USART_GetITStatus(USART1,USART_IT_RXNE))
		{
			Res = USART_ReceiveData(USART1);	
			USART_SendData(USART1,Res);
			if(Res==0xcc)
			{
				LED1=0;
				delay_ms(300);
				LED1=1;
				delay_ms(300);
				LED1=0;
			}
		}	
	}

 int main(void)
 {	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 My_USART1_Init();
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 while(1)
	 {
		/*LED0=1;
		LED1=0;
		 USART_SendData(USART1,0xff);
		delay_ms(3000);	 //延时300ms
		LED0=0;
		LED1=1;
		delay_ms(300);	//延时300ms8*/
	 }
	 
	 
	 
 }
