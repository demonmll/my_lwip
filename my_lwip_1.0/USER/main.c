#include "mysys.h"
#include "delay.h"
#include "usart.h"
//#include "led.h"
#include "spi.h"
#include "enc28j60.h"
//#include "malloc.h"
//#include "timer.h"



//ALIENTEK 探索者STM32F407开发板 实验25
//SPI通信接口实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


//extern functions	
extern void lwip_demo(void *pdata);

unsigned int system_tick_num = 0;
 

int main(void)
{ 

	u16 retry = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	delay_init(168);     //初始化延时函数
	uart_init(9600);	//初始化串口波特率为115200
//LED_Init();					//初始化LED 
//	my_mem_init(SRAMIN);	

	/* 配置systic作为20ms中断 */
	if (SysTick_Config(20*168000))		//时钟节拍中断，20ms一次
    { 
    	/* error handle*/ 
     	while (1);
    }
	
	
//	TIM3_Int_Init(100, 8400-1);
   		  
	/* 向串口1发送开机字符 */
    printf("****       (C) COPYRIGHT 2013 制造者科技    *******\r\n");    	  //。
    printf("*                                                 *\r\n");  
    printf("*                                                 *\r\n");    	  	
    printf("*     MCU平台:STM32F103VET6                       *\r\n");    	
    printf("*     以太网硬件:ENC28J60                         *\r\n");    	  	
    printf("*     固件库：3.5                                 *\r\n");    	
    printf("*     例程版本: 0.2                               *\r\n");     
    printf("*                                                 *\r\n");    	 	
    printf("***************************************************\r\n");  	
				
	SPI1_Init();	      //SPI口初始化，用于网卡间传输数�
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
	
	ENC28J60_RST=0;			//复位ENC28J60
	for(int i = 6555;i<0;i--);
	ENC28J60_RST=1;			//复位结束		
	for(int i = 6555;i<0;i--);
	
	//delay_ms(10);	
	
	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//软件复位
	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//等待时钟稳定
	{
		retry++;
	}	
	if(retry>=250)printf("fail \r\n"); //ENC28J60初始化失败	
		
	
	lwip_demo(NULL);	  //初始化内核，启动LwIP相关
	 
	while (1)
	{
	    //exit(0);	
	}
	
		
		
		
//TEST SPI	



//	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
//	
//	ENC28J60_RST=0;			//复位ENC28J60
//	delay_ms(10);	 
//	ENC28J60_RST=1;			//复位结束				    
//	delay_ms(10);	
//	
//	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//软件复位
//	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//等待时钟稳定
//	{
//		retry++;
//		delay_ms(1);
//	}	
//	if(retry>=250)printf("fail \r\n"); //ENC28J60初始化失败
//	
//	
//	
//while(1)
//{

//	test = enc28j60getrev();
//	printf("version %d \r\n", test);
//	delay_ms(10000);
//	
//}
//		
		
		
		

   
}



