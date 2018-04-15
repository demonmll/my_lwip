#include "mysys.h"
#include "delay.h"
#include "usart.h"
//#include "led.h"
#include "spi.h"
#include "enc28j60.h"
//#include "malloc.h"
//#include "timer.h"



//ALIENTEK ̽����STM32F407������ ʵ��25
//SPIͨ�Žӿ�ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


//extern functions	
extern void lwip_demo(void *pdata);

unsigned int system_tick_num = 0;
 

int main(void)
{ 

	u16 retry = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	delay_init(168);     //��ʼ����ʱ����
	uart_init(9600);	//��ʼ�����ڲ�����Ϊ115200
//LED_Init();					//��ʼ��LED 
//	my_mem_init(SRAMIN);	

	/* ����systic��Ϊ20ms�ж� */
	if (SysTick_Config(20*168000))		//ʱ�ӽ����жϣ�20msһ��
    { 
    	/* error handle*/ 
     	while (1);
    }
	
	
//	TIM3_Int_Init(100, 8400-1);
   		  
	/* �򴮿�1���Ϳ����ַ� */
    printf("****       (C) COPYRIGHT 2013 �����߿Ƽ�    *******\r\n");    	  //��
    printf("*                                                 *\r\n");  
    printf("*                                                 *\r\n");    	  	
    printf("*     MCUƽ̨:STM32F103VET6                       *\r\n");    	
    printf("*     ��̫��Ӳ��:ENC28J60                         *\r\n");    	  	
    printf("*     �̼��⣺3.5                                 *\r\n");    	
    printf("*     ���̰汾: 0.2                               *\r\n");     
    printf("*                                                 *\r\n");    	 	
    printf("***************************************************\r\n");  	
				
	SPI1_Init();	      //SPI�ڳ�ʼ�������������䴫�����
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
	
	ENC28J60_RST=0;			//��λENC28J60
	for(int i = 6555;i<0;i--);
	ENC28J60_RST=1;			//��λ����		
	for(int i = 6555;i<0;i--);
	
	//delay_ms(10);	
	
	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//�����λ
	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//�ȴ�ʱ���ȶ�
	{
		retry++;
	}	
	if(retry>=250)printf("fail \r\n"); //ENC28J60��ʼ��ʧ��	
		
	
	lwip_demo(NULL);	  //��ʼ���ںˣ�����LwIP���
	 
	while (1)
	{
	    //exit(0);	
	}
	
		
		
		
//TEST SPI	



//	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);	
//	
//	ENC28J60_RST=0;			//��λENC28J60
//	delay_ms(10);	 
//	ENC28J60_RST=1;			//��λ����				    
//	delay_ms(10);	
//	
//	enc28j60WriteOp(ENC28J60_SOFT_RESET,0,ENC28J60_SOFT_RESET);	//�����λ
//	while(!(enc28j60Read(ESTAT)&ESTAT_CLKRDY)&&retry<250)	//�ȴ�ʱ���ȶ�
//	{
//		retry++;
//		delay_ms(1);
//	}	
//	if(retry>=250)printf("fail \r\n"); //ENC28J60��ʼ��ʧ��
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



