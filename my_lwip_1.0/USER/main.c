#include "mysys.h"
#include "delay.h"
#include "usart.h"
//#include "led.h"
#include "spi.h"
#include "enc28j60.h"
//#include "malloc.h"
//#include "timer.h"



//ALIENTEK Ì½Ë÷ÕßSTM32F407¿ª·¢°å ÊµÑé25
//SPIÍ¨ÐÅ½Ó¿ÚÊµÑé-¿âº¯Êý°æ±¾
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//ÌÔ±¦µêÆÌ£ºhttp://eboard.taobao.com  
//¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾  
//×÷Õß£ºÕýµãÔ­×Ó @ALIENTEK


//extern functions	
extern void lwip_demo(void *pdata);

unsigned int system_tick_num = 0;
 

int main(void)
{ 

	u16 retry = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
//	delay_init(168);     //³õÊ¼»¯ÑÓÊ±º¯Êý
	uart_init(9600);	//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
//LED_Init();					//³õÊ¼»¯LED 
//	my_mem_init(SRAMIN);	

	/* ÅäÖÃsystic×÷Îª20msÖÐ¶Ï */
	if (SysTick_Config(20*168000))		//Ê±ÖÓ½ÚÅÄÖÐ¶Ï£¬20msÒ»´Î
    { 
    	/* error handle*/ 
     	while (1);
    }
	
	
//	TIM3_Int_Init(100, 8400-1);
   		  
	/* Ïò´®¿Ú1·¢ËÍ¿ª»ú×Ö·û */
    printf("****       (C) COPYRIGHT 2013 ÖÆÔìÕß¿Æ¼¼    *******\r\n");    	  //¡£
    printf("*                                                 *\r\n");  
    printf("*                                                 *\r\n");    	  	
    printf("*     MCUÆ½Ì¨:STM32F103VET6                       *\r\n");    	
    printf("*     ÒÔÌ«ÍøÓ²¼þ:ENC28J60                         *\r\n");    	  	
    printf("*     ¹Ì¼þ¿â£º3.5                                 *\r\n");    	
    printf("*     Àý³Ì°æ±¾: 0.2                               *\r\n");     
    printf("*                                                 *\r\n");    	 	
    printf("***************************************************\r\n");  	
				
	SPI1_Init();	      //SPI¿Ú³õÊ¼»¯£¬ÓÃÓÚÍø¿¨¼ä´«ÊäÊý¾
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
	
	ENC28J60_RST=0;			//¸´Î»ENC28J60
	for(int i = 6555;i<0;i--);
	ENC28J60_RST=1;			//¸´Î»½áÊø		
	for(int i = 6555;i<0;i--);
	
	//delay_ms(10);	
	
	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//Èí¼þ¸´Î»
	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//µÈ´ýÊ±ÖÓÎÈ¶¨
	{
		retry++;
	}	
	if(retry>=250)printf("fail \r\n"); //ENC28J60³õÊ¼»¯Ê§°Ü	
		
	
	lwip_demo(NULL);	  //³õÊ¼»¯ÄÚºË£¬Æô¶¯LwIPÏà¹Ø
	 
	while (1)
	{
	    //exit(0);	
	}
	
		
		
		
//TEST SPI	



//	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
//	
//	ENC28J60_RST=0;			//¸´Î»ENC28J60
//	delay_ms(10);	 
//	ENC28J60_RST=1;			//¸´Î»½áÊø				    
//	delay_ms(10);	
//	
//	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//Èí¼þ¸´Î»
//	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//µÈ´ýÊ±ÖÓÎÈ¶¨
//	{
//		retry++;
//		delay_ms(1);
//	}	
//	if(retry>=250)printf("fail \r\n"); //ENC28J60³õÊ¼»¯Ê§°Ü
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



