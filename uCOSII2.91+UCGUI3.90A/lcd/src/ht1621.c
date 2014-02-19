//#include <stm32f10x_lib.h>
#include "ht1621.h"
#include "delay.h"
#include "key.h"
//#include "led.h"

 //u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
//u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
//u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};
//u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};

//u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
//u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
//u8 num11_dp22Seg[]={0X0E,0X05,0X06,0X0E,0X00,0X00,0X0C,0X07,0X02,0X0E,0X07,0X00,0X0E,0X02,0X04,0X0A,0X07,0X04,0X0A,0X07,0X06,0X0E,0X04,0X00,0X0E,0X07,0X06,0X0E,0X07,0X04};
//u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
//u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0C,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
//u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
//u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};





//////////////////////////////////////////////////////////////////////////////////	 
//������Ϊ��������ƣ�δ����ɣ����ø����⴫
//ʵ��嶰�����V3.0-1
//LCD����HT1621���� PB3Ϊ595RCLK;PB4Ϊ1621WR;PB5Ϊ1621CS;PB6Ϊ1621DATA��595SCLK	   
//�޸�����:2013/3/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �����ж�����ӿƼ����޹�˾ 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   

//��ʼ��PB4 PB5��PB6Ϊ�����.��ʹ����PEʱ��		    
//HT1621 IO��ʼ��
extern u8 L_C_flag_A;//�������Ա�׼����
extern u8 COMMCAT_para;

void HT1621_Init(void)
{		

  GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_SetBits( GPIOB, GPIO_Pin_5);
  GPIO_SetBits( GPIOB, GPIO_Pin_6);
  GPIO_SetBits( GPIOB, GPIO_Pin_7);
 
	SendCmd(LCDOFF);
	SendCmd(BIAS);			
	SendCmd(SYSEN);
	SendCmd(LCDON);
}

void SendBit_1621(u8 data,u8 cnt)	 //data��cntλд��HT1621,��λ��ǰ
{
  u8 i;
  for(i=0;i<cnt;i++)
  {
   if((data&0x80)==0)DATA_0;
   else DATA_1;
   WR_0;
   delay_us(1);
   WR_1;
      delay_us(1);
   data<<=1;
  }
}
void SendDataBit_1621(u8 data,u8 cnt)	 //data��cntλд��HT1621,��λ��ǰ
{
  u8 i;
  for(i=0;i<cnt;i++)
  {
   if((data&0x01)==0)DATA_0;
   else DATA_1;
   WR_0;
   delay_us(1);
   WR_1;
      delay_us(1);
   data>>=1;
  }
}

void SendCmd(u8 command)
{
   CS_0;
   SendBit_1621(0x80,3);
   SendBit_1621(command,9);
   CS_1;
   
}

void Write_1621(u8 addr,u8 data)
{
   CS_0;
   SendBit_1621(0xa0,3);
   SendBit_1621(addr<<2,6);
   SendDataBit_1621(data,4);
   CS_1;
}

void WriteAll_1621(u8 addr,u8 *p,u8 cnt)
{
   u8 i;
   CS_0;
   SendBit_1621(0xa0,3);
   SendBit_1621(addr<<2,6);
   for(i=0;i<cnt;i++,p++)
   {
   	   SendDataBit_1621(*p,4);
   }
   CS_1;
}

void Clera_lcd(void)
{
	 u8 t;
	 for(t=0;t<32;t++)
	 {
	   u8 i;
	   for(i=0;i<4;i++)
	   {		  
	   	Write_1621(t,0x00<<i);
	   }
	 }
}



void Graf_cos_volt_current(u16 PF,u16 volt_para,u32 current_para)		 //��ʾ����������ѹ����
{
  u8 PF_zhengshu,PF_shifenwei,PF_baifenwei,PF_qianfenwei;
  u8 volt_para_qianwei,volt_para_baiwei,volt_para_shiwei,volt_para_gewei;
  u8 current_para_qianwei,current_para_baiwei,current_para_shiwei,current_para_gewei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};


  WriteAll_1621(28,numcontr_auto,1);//	��ʾP14����������ѹ������P12�������ơ�����

  PF_zhengshu=PF/1000;
  PF_shifenwei=(PF%1000)/100;
  PF_baifenwei=	(PF%100)/10;
  PF_qianfenwei=PF%10;
  if(L_C_flag_A==1)WriteAll_1621(25,num9_12Seg+3*PF_zhengshu,3);				//
	  if(L_C_flag_A==0)Write_1621(26,0x02);	//	p25��ʾ�������ơ�
   
  WriteAll_1621(22,num10dp9_12dp11Seg+3*PF_shifenwei,3);	//
WriteAll_1621(19,num11_p21Seg+3*PF_baifenwei,3);		//	��P21��P22Ͷ�����
  	
  WriteAll_1621(16,num9_12Seg+3*PF_qianfenwei,3);			//

  volt_para_qianwei=volt_para/1000;
  volt_para_baiwei=(volt_para%1000)/100;
  volt_para_shiwei=(volt_para%100)/10;
  volt_para_gewei=volt_para%10;
  if(volt_para_qianwei>0)
    {
	  WriteAll_1621(12,num567Seg+2*volt_para_qianwei,2);	//
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
  	}
	else if(volt_para_baiwei>0)
	{
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
	}
	 else
	 {
	   WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	   WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//	 
	 }
  
  current_para_qianwei=current_para/1000;
  current_para_baiwei=(current_para%1000)/100;
  current_para_shiwei=(current_para%100)/10;
  current_para_gewei=current_para%10;
   if(COMMCAT_para==0)
	  	  	{
	  	  	Write_1621(4,0x01);
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  	  Write_1621(2,0x01);

	  	  	}
  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
  if(current_para_qianwei>0)
    {
	  WriteAll_1621(0,num1234Seg+2*current_para_qianwei,2);	//
	  	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
    }
	 else if(current_para_baiwei>0)
	 {
	 	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}
	   WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }
	 else
	 {
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  		  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//

	  	  	}
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }

}

void Graf_cos_volt_current_L1(u16 PF,u16 volt_para,u32 current_para)		 //��ʾ����������ѹ����

{
  u8 PF_zhengshu,PF_shifenwei,PF_baifenwei,PF_qianfenwei;
  u8 volt_para_qianwei,volt_para_baiwei,volt_para_shiwei,volt_para_gewei;
  u8 current_para_qianwei,current_para_baiwei,current_para_shiwei,current_para_gewei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num10_L1_dp9seg[]={0X06,0X0D,0X07,0X06,0X08,0X01,0X04,0X0F,0X03,0X06,0X0F,0X01,0X06,0X0A,0X05,0X02,0X0F,0X05,0X02,0X0F,0X07,0X06,0X0C,0X01,0X06,0X0F,0X07,0X06,0X0F,0X05};

u8 numcontr_auto[]={0X09,0X05,0X03};


  WriteAll_1621(28,numcontr_auto,1);//	��ʾP14����������ѹ������P12�������ơ�����

  PF_zhengshu=PF/1000;
  PF_shifenwei=(PF%1000)/100;
  PF_baifenwei=	(PF%100)/10;
  PF_qianfenwei=PF%10;
  if(L_C_flag_A==1)WriteAll_1621(25,num9_12Seg+3*PF_zhengshu,3);				//
	  if(L_C_flag_A==0)Write_1621(26,0x02);	//	p25��ʾ�������ơ�

  {	WriteAll_1621(22,num10_L1_dp9seg+3*PF_shifenwei,3);	
WriteAll_1621(19,num9_12Seg+3*PF_baifenwei,3);		//	��P21�LL1 P22Ͷ�����

  }
  WriteAll_1621(16,num9_12Seg+3*PF_qianfenwei,3);			//

  volt_para_qianwei=volt_para/1000;
  volt_para_baiwei=(volt_para%1000)/100;
  volt_para_shiwei=(volt_para%100)/10;
  volt_para_gewei=volt_para%10;
  if(volt_para_qianwei>0)
    {
	  WriteAll_1621(12,num567Seg+2*volt_para_qianwei,2);	//
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
  	}
	else if(volt_para_baiwei>0)
	{
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
	}
	 else
	 {
	   WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	   WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//	 
	 }
  
  current_para_qianwei=current_para/1000;
  current_para_baiwei=(current_para%1000)/100;
  current_para_shiwei=(current_para%100)/10;
  current_para_gewei=current_para%10;
  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
  if(current_para_qianwei>0)
    {
	  WriteAll_1621(0,num1234Seg+2*current_para_qianwei,2);	//
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
    }
	 else if(current_para_baiwei>0)
	 {
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	   WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }
	 else
	 {
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  		  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//

	  	  	}
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }

}


void Graf_cos_volt_current_L2(u16 PF,u16 volt_para,u32 current_para)		 //��ʾ����������ѹ����

{
  u8 PF_zhengshu,PF_shifenwei,PF_baifenwei,PF_qianfenwei;
  u8 volt_para_qianwei,volt_para_baiwei,volt_para_shiwei,volt_para_gewei;
  u8 current_para_qianwei,current_para_baiwei,current_para_shiwei,current_para_gewei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num10_L2_dp9seg[]={0X0E,0X05,0X07,0X0E,0X00,0X01,0X0C,0X07,0X03,0X0E,0X07,0X01,0X0E,0X02,0X05,0X0A,0X07,0X05,0X0A,0X07,0X07,0X0E,0X04,0X01,0X0E,0X07,0X07,0X0E,0X07,0X05};

u8 numcontr_auto[]={0X09,0X05,0X03};


  WriteAll_1621(28,numcontr_auto,1);//	��ʾP14����������ѹ������P12�������ơ�����

  PF_zhengshu=PF/1000;
  PF_shifenwei=(PF%1000)/100;
  PF_baifenwei=	(PF%100)/10;
  PF_qianfenwei=PF%10;
  if(L_C_flag_A==1)WriteAll_1621(25,num9_12Seg+3*PF_zhengshu,3);				//
	  if(L_C_flag_A==0)Write_1621(26,0x02);	//	p25��ʾ�������ơ�

  {	WriteAll_1621(22,num10_L2_dp9seg+3*PF_shifenwei,3);	
WriteAll_1621(19,num9_12Seg+3*PF_baifenwei,3);		//	��P21�LL1 P22Ͷ�����

  }
  WriteAll_1621(16,num9_12Seg+3*PF_qianfenwei,3);			//

  volt_para_qianwei=volt_para/1000;
  volt_para_baiwei=(volt_para%1000)/100;
  volt_para_shiwei=(volt_para%100)/10;
  volt_para_gewei=volt_para%10;
  if(volt_para_qianwei>0)
    {
	  WriteAll_1621(12,num567Seg+2*volt_para_qianwei,2);	//
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
  	}
	else if(volt_para_baiwei>0)
	{
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
	}
	 else
	 {
	   WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	   WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//	 
	 }
  
  current_para_qianwei=current_para/1000;
  current_para_baiwei=(current_para%1000)/100;
  current_para_shiwei=(current_para%100)/10;
  current_para_gewei=current_para%10;
  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
  if(current_para_qianwei>0)
    {
	  WriteAll_1621(0,num1234Seg+2*current_para_qianwei,2);	//
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
    }
	 else if(current_para_baiwei>0)
	 {
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	   WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }
	 else
	 {
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  		  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//

	  	  	}
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }

}


void Graf_cos_volt_current_L3(u16 PF,u16 volt_para,u32 current_para)		 //��ʾ����������ѹ����

{
  u8 PF_zhengshu,PF_shifenwei,PF_baifenwei,PF_qianfenwei;
  u8 volt_para_qianwei,volt_para_baiwei,volt_para_shiwei,volt_para_gewei;
  u8 current_para_qianwei,current_para_baiwei,current_para_shiwei,current_para_gewei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_L3seg[]={0X06,0X05,0X0E,0X06,0X00,0X08,0X04,0X07,0X0A,0X06,0X07,0X08,0X06,0X02,0X0C,0X02,0X07,0X0C,0X02,0X07,0X0E,0X06,0X04,0X08,0X06,0X07,0X0E,0X06,0X07,0X0C };
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};

u8 numcontr_auto[]={0X09,0X05,0X03};


  WriteAll_1621(28,numcontr_auto,1);//	��ʾP14����������ѹ������P12�������ơ�����

  PF_zhengshu=PF/1000;
  PF_shifenwei=(PF%1000)/100;
  PF_baifenwei=	(PF%100)/10;
  PF_qianfenwei=PF%10;
  if(L_C_flag_A==1)WriteAll_1621(25,num9_12Seg+3*PF_zhengshu,3);				//
	  if(L_C_flag_A==0)Write_1621(26,0x02);	//	p25��ʾ�������ơ�

  {	WriteAll_1621(22,num10dp9_12dp11Seg+3*PF_shifenwei,3);	
WriteAll_1621(19,num11_L3seg+3*PF_baifenwei,3);		//	��P21�LL1 P22Ͷ�����

  }
  WriteAll_1621(16,num9_12Seg+3*PF_qianfenwei,3);			//

  volt_para_qianwei=volt_para/1000;
  volt_para_baiwei=(volt_para%1000)/100;
  volt_para_shiwei=(volt_para%100)/10;
  volt_para_gewei=volt_para%10;
  if(volt_para_qianwei>0)
    {
	  WriteAll_1621(12,num567Seg+2*volt_para_qianwei,2);	//
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
  	}
	else if(volt_para_baiwei>0)
	{
	  WriteAll_1621(10,num567Seg+2*volt_para_baiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//
	}
	 else
	 {
	   WriteAll_1621(8,num567Seg+2*volt_para_shiwei,2);	//
	   WriteAll_1621(14,num8_dp7Seg+2*volt_para_gewei,2);	//	 
	 }
  
  current_para_qianwei=current_para/1000;
  current_para_baiwei=(current_para%1000)/100;
  current_para_shiwei=(current_para%100)/10;
  current_para_gewei=current_para%10;
  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
  if(current_para_qianwei>0)
    {
	  WriteAll_1621(0,num1234Seg+2*current_para_qianwei,2);	//
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
    }
	 else if(current_para_baiwei>0)
	 {
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//
	  	  	}	  
	   WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }
	 else
	 {
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*current_para_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  		  WriteAll_1621(2,num3_p11Seg+2*current_para_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*current_para_shiwei,2);	//

	  	  	}
	  WriteAll_1621(6,num1234Seg+2*current_para_gewei,2);	//
	 }

}
void Graf_powuse_poweunuse_freq(u16 powunuse,u16 powuse,u16 freq)
{
	u8 powunuse_baiwei,powunuse_shiwei,powunuse_gewei,powunuse_shifenwei;
	u8 powuse_baiwei,powuse_shiwei,powuse_gewei,powuse_shifenwei;
	u8 freq_shiwei,freq_gewei,freq_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};

    WriteAll_1621(28,numcontr_auto+1,1);//	��ʾP15��ʾ�޹��й���Ƶ�ʺ�P12�������ơ�����	

	powunuse_baiwei=powunuse/1000;
	powunuse_shiwei=(powunuse%1000)/100;
	powunuse_gewei=(powunuse%100)/10;
	powunuse_shifenwei=powunuse%10;
	if(powunuse_baiwei>0)
	 {
	  WriteAll_1621(25,num9_12Seg+3*powunuse_baiwei,3);	//
      WriteAll_1621(22,num9_12Seg+3*powunuse_shiwei,3);	//
      WriteAll_1621(19,num11_p21Seg+3*powunuse_gewei,3);	//
	  WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	 else if(powunuse_shiwei>0)
	 {
	   WriteAll_1621(22,num9_12Seg+3*powunuse_shiwei,3);	//
       WriteAll_1621(19,num11_p21Seg+3*powunuse_gewei,3);	//
	   WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	  else
	   {
	     WriteAll_1621(19,num11_p21Seg+3*powunuse_gewei,3);	//
	     WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	   }
	powuse_baiwei=powuse/1000;
	powuse_shiwei=(powuse%1000)/100;
	powuse_gewei=(powuse%100)/10;
	powuse_shifenwei=powuse%10;
	if(powuse_baiwei>0)
	  {
		WriteAll_1621(12,num567Seg+2*powuse_baiwei,2);	//
		WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	  }
	  else if(powuse_shiwei>0)
	   {
	  	WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	   }
	    else 
		{
		  WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
		}

	freq_shiwei=freq/100;
	freq_gewei=(freq%100)/10;
	freq_shifenwei=freq%10;
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*freq_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*freq_gewei,2);	//
	  	  	}
    WriteAll_1621(6,num4_dp3Seg+2*freq_shifenwei,2);

}

void Graf_powuse_poweunuse_freq_L1(u16 powunuse,u16 powuse,u16 freq)

{
	u8 powunuse_baiwei,powunuse_shiwei,powunuse_gewei,powunuse_shifenwei;
	u8 powuse_baiwei,powuse_shiwei,powuse_gewei,powuse_shifenwei;
	u8 freq_shiwei,freq_gewei,freq_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num10_L1_dp9seg[]={0X06,0X0D,0X07,0X06,0X08,0X01,0X04,0X0F,0X03,0X06,0X0F,0X01,0X06,0X0A,0X05,0X02,0X0F,0X05,0X02,0X0F,0X07,0X06,0X0C,0X01,0X06,0X0F,0X07,0X06,0X0F,0X05};

    WriteAll_1621(28,numcontr_auto+1,1);//	��ʾP15��ʾ�޹��й���Ƶ�ʺ�P12�������ơ�����	

	powunuse_baiwei=powunuse/1000;
	powunuse_shiwei=(powunuse%1000)/100;
	powunuse_gewei=(powunuse%100)/10;
	powunuse_shifenwei=powunuse%10;
	if(powunuse_baiwei>0)
	 {
	  WriteAll_1621(25,num9_12Seg+3*powunuse_baiwei,3);	//
      WriteAll_1621(22,num10_L1_dp9seg+3*powunuse_shiwei,3);	//L1
      WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	  WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	 else if(powunuse_shiwei>0)
	 {
	   WriteAll_1621(22,num10_L1_dp9seg+3*powunuse_shiwei,3);	//L1
       WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	   WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	  else
	   {
	   Write_1621(23, 0x08);//L1
	     WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	     WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	   }
	powuse_baiwei=powuse/1000;
	powuse_shiwei=(powuse%1000)/100;
	powuse_gewei=(powuse%100)/10;
	powuse_shifenwei=powuse%10;
	if(powuse_baiwei>0)
	  {
		WriteAll_1621(12,num567Seg+2*powuse_baiwei,2);	//
		WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	  }
	  else if(powuse_shiwei>0)
	   {
	  	WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	   }
	    else 
		{
		  WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
		}

	freq_shiwei=freq/100;
	freq_gewei=(freq%100)/10;
	freq_shifenwei=freq%10;
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*freq_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*freq_gewei,2);	//
	  	  	}
		  WriteAll_1621(6,num4_dp3Seg+2*freq_shifenwei,2);

}


void Graf_powuse_poweunuse_freq_L2(u16 powunuse,u16 powuse,u16 freq)

{
	u8 powunuse_baiwei,powunuse_shiwei,powunuse_gewei,powunuse_shifenwei;
	u8 powuse_baiwei,powuse_shiwei,powuse_gewei,powuse_shifenwei;
	u8 freq_shiwei,freq_gewei,freq_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num10_L2_dp9seg[]={0X0E,0X05,0X07,0X0E,0X00,0X01,0X0C,0X07,0X03,0X0E,0X07,0X01,0X0E,0X02,0X05,0X0A,0X07,0X05,0X0A,0X07,0X07,0X0E,0X04,0X01,0X0E,0X07,0X07,0X0E,0X07,0X05};

    WriteAll_1621(28,numcontr_auto+1,1);//	��ʾP15��ʾ�޹��й���Ƶ�ʺ�P12�������ơ�����	

	powunuse_baiwei=powunuse/1000;
	powunuse_shiwei=(powunuse%1000)/100;
	powunuse_gewei=(powunuse%100)/10;
	powunuse_shifenwei=powunuse%10;
	if(powunuse_baiwei>0)
	 {
	  WriteAll_1621(25,num9_12Seg+3*powunuse_baiwei,3);	//
      WriteAll_1621(22,num10_L2_dp9seg+3*powunuse_shiwei,3);	//L2
      WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	  WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	 else if(powunuse_shiwei>0)
	 {
	   WriteAll_1621(22,num10_L2_dp9seg+3*powunuse_shiwei,3);	//L2
       WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	   WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	  else
	   {
	   Write_1621(22, 0x08);//L2
	     WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	     WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	   }
	powuse_baiwei=powuse/1000;
	powuse_shiwei=(powuse%1000)/100;
	powuse_gewei=(powuse%100)/10;
	powuse_shifenwei=powuse%10;
	if(powuse_baiwei>0)
	  {
		WriteAll_1621(12,num567Seg+2*powuse_baiwei,2);	//
		WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	  }
	  else if(powuse_shiwei>0)
	   {
	  	WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	   }
	    else 
		{
		  WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
		}

	freq_shiwei=freq/100;
	freq_gewei=(freq%100)/10;
	freq_shifenwei=freq%10;
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*freq_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*freq_gewei,2);	//
	  	  	}
		  WriteAll_1621(6,num4_dp3Seg+2*freq_shifenwei,2);

}


void Graf_powuse_poweunuse_freq_L3(u16 powunuse,u16 powuse,u16 freq)

{
	u8 powunuse_baiwei,powunuse_shiwei,powunuse_gewei,powunuse_shifenwei;
	u8 powuse_baiwei,powuse_shiwei,powuse_gewei,powuse_shifenwei;
	u8 freq_shiwei,freq_gewei,freq_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num11_L3seg[]={0X06,0X05,0X0E,0X06,0X00,0X08,0X04,0X07,0X0A,0X06,0X07,0X08,0X06,0X02,0X0C,0X02,0X07,0X0C,0X02,0X07,0X0E,0X06,0X04,0X08,0X06,0X07,0X0E,0X06,0X07,0X0C };

    WriteAll_1621(28,numcontr_auto+1,1);//	��ʾP15��ʾ�޹��й���Ƶ�ʺ�P12�������ơ�����	

	powunuse_baiwei=powunuse/1000;
	powunuse_shiwei=(powunuse%1000)/100;
	powunuse_gewei=(powunuse%100)/10;
	powunuse_shifenwei=powunuse%10;
	if(powunuse_baiwei>0)
	 {
	  WriteAll_1621(25,num9_12Seg+3*powunuse_baiwei,3);	//
      WriteAll_1621(22,num10dp9_12dp11Seg+3*powunuse_shiwei,3);	//L2
      WriteAll_1621(19,num11_L3seg+3*powunuse_gewei,3);	//
	  WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	 else if(powunuse_shiwei>0)
	 {
	   WriteAll_1621(22,num10dp9_12dp11Seg+3*powunuse_shiwei,3);	//L2
       WriteAll_1621(19,num11_L3seg+3*powunuse_gewei,3);	//
	   WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	 }
	  else
	   {
	     WriteAll_1621(19,num11_L3seg+3*powunuse_gewei,3);	//
	     WriteAll_1621(16,num10dp9_12dp11Seg+3*powunuse_shifenwei,3);	//
	   }
	powuse_baiwei=powuse/1000;
	powuse_shiwei=(powuse%1000)/100;
	powuse_gewei=(powuse%100)/10;
	powuse_shifenwei=powuse%10;
	if(powuse_baiwei>0)
	  {
		WriteAll_1621(12,num567Seg+2*powuse_baiwei,2);	//
		WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	  }
	  else if(powuse_shiwei>0)
	   {
	  	WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
		WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
	   }
	    else 
		{
		  WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*powuse_shifenwei,2);	//
		}

	freq_shiwei=freq/100;
	freq_gewei=(freq%100)/10;
	freq_shifenwei=freq%10;
	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*freq_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*freq_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*freq_gewei,2);	//
	  	  	}
		  WriteAll_1621(6,num4_dp3Seg+2*freq_shifenwei,2);

}
void Graf_temp_hv_hi(u16 TEMP,u16 HV,u16 HI)	   //��ʾ�¶ȵ�ѹг������г��
{
	u8 	TEMP_baiwei,TEMP_shiwei,TEMP_gewei,TEMP_shifenwei;
	u8  HV_shiwei, HV_gewei,HV_shifenwei;
	u8  HI_shiwei, HI_gewei,HI_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};

    WriteAll_1621(28,numcontr_auto+2,1);//	��ʾP16��ʾ�¶ȵ�ѹг������г����P12�������ơ�����
Write_1621(4, 0x01);//��   ����    ��
	TEMP_baiwei=TEMP/1000;
	TEMP_shiwei=(TEMP%1000)/100;
	TEMP_gewei=(TEMP%100)/10;
	TEMP_shifenwei=TEMP%10;
	if(TEMP_baiwei>0)
	  {
		WriteAll_1621(25,num9_12Seg+3*TEMP_baiwei,3);	//
    	WriteAll_1621(22,num9_12Seg+3*TEMP_shiwei,3);	//
    	WriteAll_1621(19,num11_p21Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  else if(TEMP_shiwei>0)
	  {
	    WriteAll_1621(22,num9_12Seg+3*TEMP_shiwei,3);	//
    	WriteAll_1621(19,num11_p21Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }	  
	  else
	  {
    	WriteAll_1621(19,num11_p21Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  
	HV_shiwei=HV/100;
	HV_gewei=(HV%100)/10;
	HV_shifenwei=HV%10;
	if(HV_shiwei>0)
	 {
	  WriteAll_1621(10,num567Seg+2*HV_shiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	 else 
	 {
	  	WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	    WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	HI_shiwei=HI/100;
	HI_gewei=(HI%100)/10;
	HI_shifenwei=HI%10;
	if(HI_shiwei>0)
	{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}
else
{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  	  	Write_1621(2,0x01);
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}
}

void Graf_temp_hv_hi_L1(u16 TEMP,u16 HV,u16 HI)	   //��ʾ�¶ȵ�ѹг������г��
{
	u8 	TEMP_baiwei,TEMP_shiwei,TEMP_gewei,TEMP_shifenwei;
	u8  HV_shiwei, HV_gewei,HV_shifenwei;
	u8  HI_shiwei, HI_gewei,HI_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num10_L1seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
    WriteAll_1621(28,numcontr_auto+2,1);//	��ʾP16��ʾ�¶ȵ�ѹг������г����P12�������ơ�����
Write_1621(4, 0x01);//��   ����    ��

	TEMP_baiwei=TEMP/1000;
	TEMP_shiwei=(TEMP%1000)/100;
	TEMP_gewei=(TEMP%100)/10;
	TEMP_shifenwei=TEMP%10;
	if(TEMP_baiwei>0)
	  {
		WriteAll_1621(25,num9_12Seg+3*TEMP_baiwei,3);	//
    	WriteAll_1621(22,num10_L1seg+3*TEMP_shiwei,3);	//L1
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  else if(TEMP_shiwei>0)
	  {
	    WriteAll_1621(22,num10_L1seg+3*TEMP_shiwei,3);	//L1
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }	  
	  else
	  {
	  	   Write_1621(23, 0x08);//L1
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  
	HV_shiwei=HV/100;
	HV_gewei=(HV%100)/10;
	HV_shifenwei=HV%10;
	if(HV_shiwei>0)
	 {
	  WriteAll_1621(10,num567Seg+2*HV_shiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	 else 
	 {
	  	WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	    WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	HI_shiwei=HI/100;
	HI_gewei=(HI%100)/10;
	HI_shifenwei=HI%10;
	if(HI_shiwei>0)
	{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}
else
{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  	  	Write_1621(2,0x01);
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}

}

void Graf_temp_hv_hi_L2(u16 TEMP,u16 HV,u16 HI)	   //��ʾ�¶ȵ�ѹг������г��
{
	u8 	TEMP_baiwei,TEMP_shiwei,TEMP_gewei,TEMP_shifenwei;
	u8  HV_shiwei, HV_gewei,HV_shifenwei;
	u8  HI_shiwei, HI_gewei,HI_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num10_L2seg[]={0X0E,0X05,0X06,0X0E,0X00,0X00,0X0C,0X07,0X02,0X0E,0X07,0X00,0X0E,0X02,0X04,0X0A,0X07,0X04,0X0A,0X07,0X06,0X0E,0X04,0X00,0X0E,0X07,0X06,0X0E,0X07,0X04};
    WriteAll_1621(28,numcontr_auto+2,1);//	��ʾP16��ʾ�¶ȵ�ѹг������г����P12�������ơ�����
Write_1621(4, 0x01);//��   ����    ��

	TEMP_baiwei=TEMP/1000;
	TEMP_shiwei=(TEMP%1000)/100;
	TEMP_gewei=(TEMP%100)/10;
	TEMP_shifenwei=TEMP%10;
	if(TEMP_baiwei>0)
	  {
		WriteAll_1621(25,num9_12Seg+3*TEMP_baiwei,3);	//
    	WriteAll_1621(22,num10_L2seg+3*TEMP_shiwei,3);	//L2
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  else if(TEMP_shiwei>0)
	  {
	    WriteAll_1621(22,num10_L2seg+3*TEMP_shiwei,3);	//L2
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }	  
	  else
	  {
	  	   Write_1621(22, 0x08);//L2
    	WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  
	HV_shiwei=HV/100;
	HV_gewei=(HV%100)/10;
	HV_shifenwei=HV%10;
	if(HV_shiwei>0)
	 {
	  WriteAll_1621(10,num567Seg+2*HV_shiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	 else 
	 {
	  	WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	    WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	HI_shiwei=HI/100;
	HI_gewei=(HI%100)/10;
	HI_shifenwei=HI%10;
	if(HI_shiwei>0)
	{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}
else
{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  	  	Write_1621(2,0x01);
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}

}
void Graf_temp_hv_hi_L3(u16 TEMP,u16 HV,u16 HI)	   //��ʾ�¶ȵ�ѹг������г��
{
	u8 	TEMP_baiwei,TEMP_shiwei,TEMP_gewei,TEMP_shifenwei;
	u8  HV_shiwei, HV_gewei,HV_shifenwei;
	u8  HI_shiwei, HI_gewei,HI_shifenwei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num4_dp3Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
u8 num11_p21_p22Seg[]={0X0E,0X0D,0X06,0X0E,0X08,0X00,0X0C,0X0F,0X02,0X0E,0X0F,0X00,0X0E,0X0A,0X04,0X0A,0X0F,0X04,0X0A,0X0F,0X06,0X0E,0X0C,0X00,0X0E,0X0F,0X06,0X0E,0X0F,0X04};
u8 numcontr_auto[]={0X09,0X05,0X03};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
u8 num11_L3seg[]={0X06,0X05,0X0E,0X06,0X00,0X08,0X04,0X07,0X0A,0X06,0X07,0X08,0X06,0X02,0X0C,0X02,0X07,0X0C,0X02,0X07,0X0E,0X06,0X04,0X08,0X06,0X07,0X0E,0X06,0X07,0X0C };

    WriteAll_1621(28,numcontr_auto+2,1);//	��ʾP16��ʾ�¶ȵ�ѹг������г����P12�������ơ�����
Write_1621(4, 0x01);//��   ����    ��

	TEMP_baiwei=TEMP/1000;
	TEMP_shiwei=(TEMP%1000)/100;
	TEMP_gewei=(TEMP%100)/10;
	TEMP_shifenwei=TEMP%10;
	if(TEMP_baiwei>0)
	  {
		WriteAll_1621(25,num9_12Seg+3*TEMP_baiwei,3);	//
    	WriteAll_1621(22,num9_12Seg+3*TEMP_shiwei,3);	//
    	WriteAll_1621(19,num11_L3seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  else if(TEMP_shiwei>0)
	  {
	    WriteAll_1621(22,num9_12Seg+3*TEMP_shiwei,3);	//
    	WriteAll_1621(19,num11_L3seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }	  
	  else
	  {
    	WriteAll_1621(19,num11_L3seg+3*TEMP_gewei,3);	//
		WriteAll_1621(16,num10dp9_12dp11Seg+3*TEMP_shifenwei,3);	//
	  }
	  
	HV_shiwei=HV/100;
	HV_gewei=(HV%100)/10;
	HV_shifenwei=HV%10;
	if(HV_shiwei>0)
	 {
	  WriteAll_1621(10,num567Seg+2*HV_shiwei,2);	//
	  WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	  WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	 else 
	 {
	  	WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	    WriteAll_1621(14,num8_dp7Seg+2*HV_shifenwei,2);	//
	 }
	HI_shiwei=HI/100;
	HI_gewei=(HI%100)/10;
	HI_shifenwei=HI%10;
	if(HI_shiwei>0)
	{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*HI_shiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}
else
{
		  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(4,num3_p11Seg+2*HI_gewei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  	  	Write_1621(2,0x01);
	  WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	  	  	}
	WriteAll_1621(6,num4_dp3Seg+2*HI_shifenwei,2);	//
	}

}
void Graf_VER(u8 VER)
{
 	u8 VER_baiwei,VER_shiwei,VER_gewei;
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};

	Write_1621(4,0x01);	//	p11��ʾ"��"
 	Write_1621(16,0x01);	//	p25��ʾ�汾��
	//Write_1621(19,0x08);	//	p22��ʾ��Ͷ�롱
//	Write_1621(20,0x08);	//	p21��ʾ��
	Write_1621(28,0x01);	//	p25��ʾ�������ơ�


	VER_baiwei=VER/100;
	VER_shiwei=(VER%100)/10;
	VER_gewei=VER%10;
  if(COMMCAT_para==0)
	  	  	{
	  Write_1621(4,0x01);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  Write_1621(2,0x01);	//
	  	  	}
	WriteAll_1621(10,num567Seg+2*VER_baiwei,2);	//
    WriteAll_1621(8,num567Seg+2*VER_shiwei,2);	//
    WriteAll_1621(14,num8_dp7Seg+2*VER_gewei,2);	//

}
void Graf_current_value(u32 Current_A,u32 Current_B,u32 Current_C)
{
   	u8 Current_A_qianwei,Current_A_baiwei,Current_A_shiwei,Current_A_gewei;
	u8 Current_B_qianwei,Current_B_baiwei,Current_B_shiwei,Current_B_gewei;
	u8 Current_C_qianwei,Current_C_baiwei,Current_C_shiwei,Current_C_gewei;
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};

	Write_1621(29,0x04);	// ��ʾ���ݷ���
	Write_1621(28,0x01);	//	p25��ʾ�������ơ�

	Current_A_qianwei=Current_A/1000;
	Current_A_baiwei=(Current_A%1000)/100;
	Current_A_shiwei=(Current_A%100)/10;
	Current_A_gewei=Current_A%10;
	
	Current_B_qianwei=Current_B/1000;
	Current_B_baiwei=(Current_B%1000)/100;
	Current_B_shiwei=(Current_B%100)/10;
	Current_B_gewei=Current_B%10;
	
	Current_C_qianwei=Current_C/1000;
	Current_C_baiwei=(Current_C%1000)/100;
	Current_C_shiwei=(Current_C%100)/10;
	Current_C_gewei=Current_C%10;

	if(Current_A_qianwei>0)
	{
	  WriteAll_1621(25,num9_12Seg+3*Current_A_qianwei,3);
	  WriteAll_1621(22,num9_12Seg+3*Current_A_baiwei,3);
	  WriteAll_1621(19,num9_12Seg+3*Current_A_shiwei,3);
	  WriteAll_1621(16,num9_12Seg+3*Current_A_gewei,3);
	}
		else if(Current_A_baiwei>0)
		{
		  WriteAll_1621(22,num9_12Seg+3*Current_A_baiwei,3);
		  WriteAll_1621(19,num9_12Seg+3*Current_A_shiwei,3);
		  WriteAll_1621(16,num9_12Seg+3*Current_A_gewei,3);	
		}
		else if(Current_A_shiwei>0)
			{
			  WriteAll_1621(19,num9_12Seg+3*Current_A_shiwei,3);
			  WriteAll_1621(16,num9_12Seg+3*Current_A_gewei,3);	
			}
			else WriteAll_1621(16,num9_12Seg+3*Current_A_gewei,3);	
			
		if(Current_B_qianwei>0)
		{
		  WriteAll_1621(12,num567Seg+2*Current_B_qianwei,2);
		  WriteAll_1621(10,num567Seg+2*Current_B_baiwei,2);
		  WriteAll_1621(8,num567Seg+2*Current_B_shiwei,2);
		  WriteAll_1621(14,num8Seg+2*Current_B_gewei,2);
		}
			else if(Current_B_baiwei>0)
			{
			  WriteAll_1621(10,num567Seg+2*Current_B_baiwei,2);
		  	  WriteAll_1621(8,num567Seg+2*Current_B_shiwei,2);
		  	  WriteAll_1621(14,num8Seg+2*Current_B_gewei,2);	
			}
				else if(Current_B_shiwei>0)
				{
				  WriteAll_1621(8,num567Seg+2*Current_B_shiwei,2);
		  	  	  WriteAll_1621(14,num8Seg+2*Current_B_gewei,2);
				}
					else WriteAll_1621(14,num8Seg+2*Current_B_gewei,2);

	  if(Current_C_qianwei>0)
		{
		  WriteAll_1621(0,num1234Seg+2*Current_C_qianwei,2);
		  	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*Current_C_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*Current_C_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*Current_C_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*Current_C_shiwei,2);	//
	  	  	}
		  WriteAll_1621(6,num1234Seg+2*Current_C_gewei,2);
		}
			else if(Current_C_baiwei>0)
			{
					  	  if(COMMCAT_para==0)
	  	  	{
	  WriteAll_1621(2,num1234Seg+2*Current_C_baiwei,2);	//
	  WriteAll_1621(4,num3_p11Seg+2*Current_C_shiwei,2);	//
	  	  	}
		  if(COMMCAT_para==1)
	  	  	{
	  WriteAll_1621(2,num3_p11Seg+2*Current_C_baiwei,2);	//
	  WriteAll_1621(4,num1234Seg+2*Current_C_shiwei,2);	//
	  	  	}
		  	  WriteAll_1621(6,num1234Seg+2*Current_C_gewei,2);	
			}
				else if(Current_C_shiwei>0)
				{
				
					  if(COMMCAT_para==0)
					  	{
				  WriteAll_1621(4,num3_p11Seg+2*Current_C_shiwei,2);
					  	}
						if(COMMCAT_para==1)
	  	  	{
	  	  	Write_1621(2,0x01);
	  WriteAll_1621(4,num1234Seg+2*Current_C_shiwei,2);	//
	  	  	}
		  	  	  WriteAll_1621(6,num1234Seg+2*Current_C_gewei,2);
				}
					else 
					{
					  if(COMMCAT_para==0) Write_1621(4,0x01);	// ��ʾ"��"����
					   if(COMMCAT_para==1) Write_1621(2,0x01);
					   WriteAll_1621(6,num1234Seg+2*Current_C_gewei,2);
					}


}
void HT595_Send_Byte(u8 state)
{                        
    u8 t; 
    for(t=0;t<8;t++)
    {    
		DATA_0;          
        if((state&0x80)==0)
		WR_0;
		else WR_1;
		delay_us(3);
		DATA_1;
        state<<=1; 	  

    }

	delay_us(10);
}
