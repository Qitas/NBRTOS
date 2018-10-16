/**
 * Copyright (c) 2017 China Mobile IOT.
 * All rights reserved.
**/
#include "platform.h"
#include "NB_BC95.h"
#include "usart1.h"
#include "usart3.h"
#include "delay.h"

#include "led.h"
#include "beep.h"
#include "BH1750.h"
#include "i2c.h"
#include "key.h"
#include "adxl345.h"
#include "BMP180.h"
#include "SHT20.h"

void Peripheral_Init(void)
{
	
	Led_Init();											//LED�ӿڳ�ʼ��
	
//	Beep_Init();                                         //��������ʼ��
	
// 	Key_Init();											//�����ӿڳ�ʼ��
	

	IIC_Init();											//I2C���߳�ʼ��
	
	IIC_1750_Init();                                    //BH1750��ʼ��
	
	ADXL345_Init();                                       //ADX345��ʼ��
	
}

static bool _nbiot_init_state = false;

void nbiot_init_environment()
{
    if ( !_nbiot_init_state )
    {
			 nbiot_time_init();
			 USART1_Init();
			 USART3_Init(); 
			 Peripheral_Init();	 	
			 mDelay(5000);			
			 netdev_init();
			 _nbiot_init_state = true;
    }
}

void nbiot_clear_environment( void )
{
    if ( _nbiot_init_state )
    {	
				SendCmd("AT+MIPLDELETE=0","OK",300,0,10); 		
				_nbiot_init_state = false;
    }
}

void nbiot_reset(void)
{

 NVIC_GenerateSystemReset();

}
