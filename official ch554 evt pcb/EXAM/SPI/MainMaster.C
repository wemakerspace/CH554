
/********************************** (C) COPYRIGHT *******************************
* File Name          : MainMaster.C
* Author             : WCH
* Version            : V1.0
* Date               : 2017/07/06
* Description        : CH554 SPI������CH376ͨѶ������CH376�������CH376ȡ������ 
*******************************************************************************/
#include "..\Public\CH554.H"                                                  
#include "..\Public\Debug.H"
#include "SPI.H"
#include "stdio.h"
#include <string.h>

/*Ӳ���ӿڶ���*/
/******************************************************************************
ʹ��CH554 Ӳ��SPI�ӿ� 
         CH554               
         P1.4        =       SCS
         P1.5        =       MOSI
         P1.6        =       MISO
         P1.7        =       SCK
*******************************************************************************/


void main()
{ 
    UINT8 ret,i=0;
    CfgFsys( ); 
    mDelaymS(5);                                                               //������Ƶ�������Լ���ʱ�ȴ��ڲ�ʱ���ȶ�   
    mInitSTDIO( );                                                             //����0��ʼ��
    printf("start ...\n");  
	
    SPIMasterModeSet(3);                                                         //SPI����ģʽ���ã�ģʽ3
	
    SPI_CK_SET(2);                                                             //2��Ƶ�����
#ifdef SPI0Interrupt
    CH554SPIInterruptInit();                                                //SPI�жϳ�ʼ��
    EA  = 1;                                                                //ʹ��ȫ���ж�
#endif
    while(1)
    {   
	      SCS = 0; 
        CH554SPIMasterWrite(0x06);                                             //CH554��CH376ͨѶ��CH376��������
        mDelayuS(2);                                                           //����������յ�CH376ȡ�����ص�����
        CH554SPIMasterWrite(i);                                                      
        mDelayuS(2);
        ret = CH554SPIMasterRead();                                            //����CH376���ص�����
        SCS = 1;
        if(ret != (i^0xff))
        {
		        printf("Err: %02X  %02X  \n",(UINT16)i,(UINT16)ret);               //��������ڷ������ݵ�ȡ������ӡ������Ϣ					
        }
		    mDelaymS(50);
	     	i = i+1;
        if((i%40)==0)
        {
            printf("success %02x\n",(UINT16)i);                                //ÿ�ɹ�40�δ�ӡһ��										
        }
    }
}