//#include <stm32f10x_lib.h>
#include "ht1621.h"
#include "delay.h"
#include "key.h"
//#include "led.h"

   /*
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};

u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num11_dp22Seg[]={0X0E,0X05,0X06,0X0E,0X00,0X00,0X0C,0X07,0X02,0X0E,0X07,0X00,0X0E,0X02,0X04,0X0A,0X07,0X04,0X0A,0X07,0X06,0X0E,0X04,0X00,0X0E,0X07,0X06,0X0E,0X07,0X04};
u8 num4_dp3Seg[]={0X0b,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0d,0X06,0X0d,0X0B,0X0f,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};

u8 numHU_prot[]={0X06,0X02,0X06,0X06,0X01,0X06};
u8 numHI_prot[]={0X06,0X02,0X06,0X00,0X00,0X06};

u8 num_set_Seg[]={0x03,0x0F,0X0D};
u8 num_setCT_Seg[]={0x01,0x0F,0X0D};
u8 num_setdelaytime_Seg[]={0x02,0x0F,0X0D};
u8 num_setcos_Seg[]={0x03,0x0E,0X0D};
u8 num_setvoltprot_Seg[]={0x03,0x0D,0X0D};
u8 num_setON0hold_Seg[]={0x03,0x07,0X0D};
u8 num_setON1hold_Seg[]={0x03,0x07,0X05};
u8 num_setOFF0hold_Seg[]={0x03,0x0F,0X05};
u8 num_setOFF1hold_Seg[]={0x03,0x03,0X05};
u8 num_sethuhiprot_Seg[]={0x03,0x0F,0X09};
u8 num_setcommu_Seg[]={0x03,0x0F,0X0C};
*/
extern u8 L_C_flag_A;//感性容性标准变量

//////////////////////////////////////////////////////////////////////////////////	 
//本程序为控制器设计，未经许可，不得复制外传
//实验板栋达电子V3.0-1
//LCD驱动HT1621代码 PB3为595RCLK;PB4为1621WR;PB5为1621CS;PB6为1621DATA和595SCLK	   
//修改日期:2013/3/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 济宁市栋达电子科技有限公司 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   

//初始化PB4 PB5和PB6为输出口.并使能这PE时钟		    
//HT1621 IO初始化
void HT1621_Init(void)
{		

  GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits( GPIOB, GPIO_Pin_9);
   GPIO_SetBits( GPIOB, GPIO_Pin_5);
  GPIO_SetBits( GPIOB, GPIO_Pin_6);
  GPIO_SetBits( GPIOB, GPIO_Pin_7);
 
	SendCmd(LCDOFF);
	SendCmd(BIAS);			
	SendCmd(SYSEN);
	SendCmd(LCDON);
}

void SendBit_1621(u8 data,u8 cnt)	 //data高cnt位写入HT1621,高位在前
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
void SendDataBit_1621(u8 data,u8 cnt)	 //data低cnt位写入HT1621,低位在前
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



void Graf_con_u(u8 cos,u16 volt)
{
	u8 temp,coszhengshu,cosshifen,cosbaifen;
	u16 voltbaiwei,voltshiwei,voltgewei;
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

		Write_1621(12,0x04);   //显示U(v)
	Write_1621(14,0x01);   //显示cos
	Write_1621(17,0x01);   //显示dot.
	
	temp=cos;

	coszhengshu=temp/100;
	WriteAll_1621(16,num12345Seg+2*coszhengshu,2);	//显示cos整数部分

	cosshifen=(temp%100)/10;
	WriteAll_1621(18,num12345Seg+2*cosshifen,2);	 	//显示cos十分位部分

	cosbaifen=(temp%10)%10;
	WriteAll_1621(20,num12345Seg+2*cosbaifen,2);	   //显示cos百分位部分
	


	voltbaiwei=volt/100;
	WriteAll_1621(2,num12345Seg+2*voltbaiwei,2);	  //显示volt百位部分

	
	voltshiwei=(volt%100)/10;
	WriteAll_1621(10,num67Seg+2*voltshiwei,2);	  //显示volt十位部分

	voltgewei=volt%10;
	WriteAll_1621(8,num67Seg+2*voltgewei,2);	  //显示volt个位部分


//	Write_1621(7,0x08);   //显示auto
//	Write_1621(16,0x08);   //BLOG
//	WriteAll_1621(4,num67Seg+8,2);	  //
//	WriteAll_1621(19,num67Seg+8,4);	  //显示volt个位部分
}

void Graf_cuirrent(u32 current)
{
   u32 temp;
   u16 currshiwei,currgewei,currshifenwei,currbaifenwei,currqianfenwei;
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

	Write_1621(12,0x01);	//显示C-I(A)
//	Write_1621(13,0x08);	//显示dot4 .
	Write_1621(17,0x08);	//显示auto

   temp=current;

   currshiwei=temp/10000;
   WriteAll_1621(15,num12345Seg+2*currshiwei,2);	//显示C-I(A)整数部分十位

   currgewei=(temp%10000)/1000;
   WriteAll_1621(19,num12345Seg+2*currgewei,2);	//显示C-I(A)整数部分个位

   currshifenwei=(temp%1000)/100;
   WriteAll_1621(17,num12345Seg+2*currshifenwei,2);	//显示C-I(A)小数部分十分位

   currbaifenwei=(temp%100)/10;
   WriteAll_1621(0,num67Seg+2*currbaifenwei,2);	//显示C-I(A)小数部分百分位

   currqianfenwei=temp%10;
   WriteAll_1621(2,num67Seg+2*currqianfenwei,2);	//显示C-I(A)小数部分千分位

}

void Graf_qkvar(u16 qkvar)
{
   u32 temp;
   u16 qkvarshiwei,qkvargewei,qkvarshifenwei,qkvarbaifenwei,qkvarqianfenwei;
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

	Write_1621(10,0x01);	//显示Q(Kvar)
//	Write_1621(11,0x08);	//显示dot8 .
	Write_1621(17,0x08);	//显示auto

   temp=qkvar;

   qkvarshiwei=temp/10000;
   WriteAll_1621(17,num12345Seg+2*qkvarshiwei,2);	//显示Q(Kvar)整数部分十位

   qkvargewei=(temp%10000)/1000;
   WriteAll_1621(0,num67Seg+2*qkvargewei,2);	//显示Q(Kvar)整数部分个位

   qkvarshifenwei=(temp%1000)/100;
   WriteAll_1621(2,num67Seg+2*qkvarshifenwei,2);	//显示Q(Kvar)小数部分十分位

   qkvarbaifenwei=(temp%100)/10;
   WriteAll_1621(5,num67Seg+2*qkvarbaifenwei,2);	//显示Q(Kvar)小数部分百分位

   qkvarqianfenwei=temp%10;
   WriteAll_1621(8,num12345Seg+2*qkvarqianfenwei,2);	//显示Q(Kvar)小数部分千分位

}

void Graf_temp(u8 temp)
{
	u8 tempbaiwei,tempshiwei,tempgewei;
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

	Write_1621(4,0x01);	//显示TEMP
	Write_1621(17,0x08);	//显示auto

	tempbaiwei=temp/100;
	WriteAll_1621(2,num67Seg+2*tempbaiwei,2);	//显示TEMP百数位

	tempshiwei=(temp%100)/10;
	WriteAll_1621(5,num67Seg+2*tempshiwei,2);	//显示TEMP十数位

	tempgewei=temp%10;
	WriteAll_1621(8,num12345Seg+2*tempgewei,2);	//显示TEMP个数位

}

void Graf_id(u8 hostguest,u8 id)
{
	u8 h_gbaiwei,h_gshiwei,h_ggewei,idbaiwei,idshiwei,idgewei;
u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

	Write_1621(7,0x04);	//显示ID
	Write_1621(17,0x08);	//显示auto

	h_gbaiwei=hostguest/100;
	WriteAll_1621(15,num12345Seg+2*h_gbaiwei,2);	//显示机号百位数

	h_gshiwei=(hostguest%100)/10;
	WriteAll_1621(19,num12345Seg+2*h_gshiwei,2);	//显示机号十位数

	h_ggewei=hostguest%10;
	WriteAll_1621(17,num12345Seg+2*h_ggewei,2);	//显示机号个位数

	idbaiwei=id/100;
	WriteAll_1621(2,num67Seg+2*idbaiwei,2);	//显示ID百数位

	idshiwei=(id%100)/10;
	WriteAll_1621(5,num67Seg+2*idshiwei,2);	//显示ID十数位

	idgewei=id%10;
	WriteAll_1621(8,num67Seg+2*idgewei,2);	//显示ID个数位

}

void Graf_ver(u8 ver)
{
   u8 verbaiwei,vershiwei,vergewei;
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};
   
   Write_1621(4,0x04);	//显示dot10.
   Write_1621(10,0x02);	//显示ver
   Write_1621(17,0x08);	//显示auto

   verbaiwei=ver/100;
   WriteAll_1621(2,num67Seg+2*verbaiwei,2);	//显示VER百数位

   vershiwei=(ver%100)/10;
   WriteAll_1621(5,num67Seg+2*vershiwei,2);	//显示VER十数位

   vergewei=ver%10;
   WriteAll_1621(8,num67Seg+2*vergewei,2);	//显示VER个数位
}

void Graf_setid(u8 idnum)
{   
   u8 idnumbaiwei,idnumshiwei,idnumgewei;
  u8 num12345Seg[]={0x0F,0x0A,0x00,0x0A,0x0B,0x0C,0x09,0x0E,0x0E,0x0E,0x0D,0x06,0x0F,0x06,0x08,0x0A,0x0F,0x0E,0x0D,0x0E};
u8 num67Seg[]={0x0A,0x0F,0x0A,0x00,0x0C,0x0B,0x0E,0x09,0x0E,0x04,0x06,0x0B,0x06,0x0F,0x0A,0x08,0x0E,0x0F,0x0E,0x0D};

   Write_1621(7,0x01);	//显示set
   Write_1621(8,0x01);	//显示ID
   
   idnumbaiwei=idnum/100;
   WriteAll_1621(3,num12345Seg+2*idnumbaiwei,2);	//显示idnum百数位

   idnumshiwei=(idnum%100)/10;
   WriteAll_1621(11,num67Seg+2*idnumshiwei,2);	//显示idnum十数位

   idnumgewei=idnum%10;
   WriteAll_1621(9,num67Seg+2*idnumgewei,2);	//显示idnum个数位

}
void Graf_cos_volt_current(u8 PF,u16 volt_para,u16 current_para)
{
  u8 PF_zhengshu,PF_shifenwei,PF_baifenwei;
  u8 volt_para_baiwei,volt_para_shiwei,volt_para_gewei;
  u8 current_para_baiwei,current_para_shiwei,current_para_gewei;
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};

  Write_1621(24,0x01);	//显示dot
  Write_1621(28,0x08);	//

  PF_zhengshu=PF/100;
  PF_shifenwei=(PF%100)/10;
  PF_baifenwei=	PF%10;
  WriteAll_1621(25,num9_12Seg+3*PF_zhengshu,3);	//
  WriteAll_1621(22,num9_12Seg+3*PF_shifenwei,3);	//
  WriteAll_1621(19,num9_12Seg+3*PF_baifenwei,3);	//

  volt_para_baiwei=volt_para/100;
  volt_para_shiwei=(volt_para%100)/10;
  volt_para_gewei=volt_para%10;
  WriteAll_1621(12,num567Seg+2*volt_para_baiwei,2);	//
  WriteAll_1621(10,num567Seg+2*volt_para_shiwei,2);	//
  WriteAll_1621(8,num567Seg+2*volt_para_gewei,2);	//

  current_para_baiwei=current_para/100;
  current_para_shiwei=(current_para%100)/10;
  current_para_gewei=current_para%10;
  WriteAll_1621(0,num1234Seg+2*current_para_baiwei,2);	//
  WriteAll_1621(2,num1234Seg+2*current_para_shiwei,2);	//
  WriteAll_1621(4,num1234Seg+2*current_para_gewei,2);	//


}

void Graf_powuse_poweunuse_freq(u16 powunuse,u16 powuse,u16 freq)
{
	u8 powunuse_baiwei,powunuse_shiwei,powunuse_gewei,powunuse_shifenwei;
	u8 powuse_baiwei,powuse_shiwei,powuse_gewei,powuse_shifenwei;
	u8 freq_shiwei,freq_gewei,freq_shifenwei;
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};

    Write_1621(6,0x01);	//
    Write_1621(14,0x08);	//
	Write_1621(18,0x01);	//
    Write_1621(28,0x04);	//

	powunuse_baiwei=powunuse/1000;
	powunuse_shiwei=(powunuse%1000)/100;
	powunuse_gewei=(powunuse%100)/10;
	powunuse_shifenwei=powunuse%10;
	WriteAll_1621(25,num9_12Seg+3*powunuse_baiwei,3);	//
    WriteAll_1621(22,num9_12Seg+3*powunuse_shiwei,3);	//
    WriteAll_1621(19,num9_12Seg+3*powunuse_gewei,3);	//
	WriteAll_1621(16,num9_12Seg+3*powunuse_shifenwei,3);	//

	powuse_baiwei=powuse/1000;
	powuse_shiwei=(powuse%1000)/100;
	powuse_gewei=(powuse%100)/10;
	powuse_shifenwei=powuse%10;
	WriteAll_1621(12,num567Seg+2*powuse_baiwei,2);	//
	WriteAll_1621(10,num567Seg+2*powuse_shiwei,2);	//
	WriteAll_1621(8,num567Seg+2*powuse_gewei,2);	//
	WriteAll_1621(14,num8Seg+2*powuse_shifenwei,2);	//

	freq_shiwei=freq/100;
	freq_gewei=(freq%100)/10;
	freq_shifenwei=freq%10;
	WriteAll_1621(2,num1234Seg+2*freq_shiwei,2);	//
    WriteAll_1621(4,num1234Seg+2*freq_gewei,2);	//
    WriteAll_1621(6,num1234Seg+2*freq_shifenwei,2);

}

void Graf_temp_hv_hi(u16 TEMP,u16 HV,u16 HI)
{
	u8 	TEMP_baiwei,TEMP_shiwei,TEMP_gewei,TEMP_shifenwei;
	u8  HV_shiwei, HV_gewei,HV_shifenwei;
	u8  HI_shiwei, HI_gewei,HI_shifenwei;
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};

	Write_1621(6,0x01);	//
    Write_1621(14,0x08);	//
	Write_1621(18,0x01);	//
    Write_1621(28,0x02);	//

	TEMP_baiwei=TEMP/1000;
	TEMP_shiwei=(TEMP%1000)/100;
	TEMP_gewei=(TEMP%100)/10;
	TEMP_shifenwei=TEMP%10;
	WriteAll_1621(25,num9_12Seg+3*TEMP_baiwei,3);	//
    WriteAll_1621(22,num9_12Seg+3*TEMP_shiwei,3);	//
    WriteAll_1621(19,num9_12Seg+3*TEMP_gewei,3);	//
	WriteAll_1621(16,num9_12Seg+3*TEMP_shifenwei,3);	//

	HV_shiwei=HV/100;
	HV_gewei=(HV%100)/10;
	HV_shifenwei=HV%10;
	WriteAll_1621(10,num567Seg+2*HV_shiwei,2);	//
	WriteAll_1621(8,num567Seg+2*HV_gewei,2);	//
	WriteAll_1621(14,num8Seg+2*HV_shifenwei,2);	//

	HI_shiwei=HI/100;
	HI_gewei=(HI%100)/10;
	HI_shifenwei=HI%10;
	WriteAll_1621(2,num1234Seg+2*HI_shiwei,2);	//
	WriteAll_1621(4,num1234Seg+2*HI_gewei,2);	//
	WriteAll_1621(6,num1234Seg+2*HI_shifenwei,2);	//


}
void Graf_set_para(void)
{
u8 num_set_Seg[]={0x03,0x0F,0X0D};
u8 num_setCT_Seg[]={0x01,0x0F,0X0D};

	WriteAll_1621(29,num_set_Seg,3);	//
	delay_ms(200);
	WriteAll_1621(29,num_setCT_Seg,3);
	delay_ms(200);
}


void HT595_Send_Byte(u8 state)
{                        
    u8 t; 
		RCLK_595_0;		    
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
	RCLK_595_1;
}
