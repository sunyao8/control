
/* Includes ------------------------------------------------------------------*/
#include <includes.h>

/* Private variables ---------------------------------------------------------*/	

u8 Work_num=0;	  //   设置参数页面数
u8 Display_num=1;	  //正常显示页面数
u8 L1_L2_L3_COS=1;
u8 L1_L2_L3_KAR=1;
u16 CT_para;
 u8 DELAY_ON_para=10;
 u8 DELAY_OFF_para=10;
 u8 COS_ON_para=90;
 u8 COS_OFF_para=95;
 u8 V_PROT_para_L=40;
 u8 V_PROT_para_tri=40;
 u8 ON_HOLD_para=1;
 u8 OFF_HOLD_para=1;
 u8 HU_PROT_para=100;
 u8 HI_PROT_para=100;
 u8 COMMCAT_para=1;
u8 CAPA_num,capa1_value,capa2_value;
u8 capa1_array[33],capa2_array[33];
//#endif
/*************************************/
//#endif
extern u8 Work_Flag;//设置界面的闪烁标志位
extern u16 dianya_zhi;
extern u8 hguestnum,gonglvshishu;
extern u32 idle_time,scan_time,dianliuzhi;
extern u16 wugongkvar,allkvar,HV,HI;
extern s8 L_C_flag;
extern u8 tempshuzhi;
extern u16 dianya_zhi_A,dianya_zhi_B,dianya_zhi_C,wugongkvar_A,wugongkvar_B,wugongkvar_C;
extern u32	dianliuzhi_A,dianliuzhi_B,dianliuzhi_C;
extern u8 gonglvshishu_A,gonglvshishu_B,gonglvshishu_C;
extern status_comm_node Comm_list_1[33];
extern status_comm_node Comm_list_2[33];

//////////////////////////////////////////////////////////////////////////////////	 
//本程序为控制器设计，未经许可，不得复制外传
//实验板栋达电子V3.0-1
//KEY 代码 PA11为显示板设置按键；PA12为手动投切开关	   
//修改日期:2013/3/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 济宁市栋达电子科技有限公司 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void)
{
		 GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

/*************************拨码开关*********************************/
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

} 



void ParaSet(void)
{

u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};

u8 num8_dp7Seg[]={0X0D,0X0F,0X08,0X06,0X0E,0X0B,0X0A,0X0F,0X0B,0X06,0X0B,0X0D,0X0F,0X0D,0X08,0X07,0X0F,0X0F,0X0B,0X0F};
u8 num10dp9_12dp11Seg[]={0X06,0X05,0X07,0X06,0X00,0X01,0X04,0X07,0X03,0X06,0X07,0X01,0X06,0X02,0X05,0X02,0X07,0X05,0X02,0X07,0X07,0X06,0X04,0X01,0X06,0X07,0X07,0X06,0X07,0X05};
u8 num11_dp22Seg[]={0X0E,0X05,0X06,0X0E,0X00,0X00,0X0C,0X07,0X02,0X0E,0X07,0X00,0X0E,0X02,0X04,0X0A,0X07,0X04,0X0A,0X07,0X06,0X0E,0X04,0X00,0X0E,0X07,0X06,0X0E,0X07,0X04};

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





extern u8 L_C_flag_A;//感性容性标准变量
	 u8 CT_para_qianwei,CT_para_baiwei,CT_para_shiwei,CT_para_gewei;
	 u8	DELAY_ON_para_baiwei,DELAY_ON_para_shiwei,DELAY_ON_para_gewei;
	 u8	DELAY_OFF_para_baiwei,DELAY_OFF_para_shiwei,DELAY_OFF_para_gewei;
	 u8	COS_ON_para_baiwei,COS_ON_para_shiwei,COS_ON_para_gewei;
	 u8	COS_OFF_para_baiwei,COS_OFF_para_shiwei,COS_OFF_para_gewei;
	 u8	V_PROT_para_baiwei,V_PROT_para_shiwei,V_PROT_para_gewei;
	 u8	ON_HOLD_para_shiwei,ON_HOLD_para_gewei;
	 u8	OFF_HOLD_para_shiwei,OFF_HOLD_para_gewei;
	 u8 HU_PROT_para_baiwei,HU_PROT_para_shiwei,HU_PROT_para_gewei;
	 u8 HI_PROT_para_baiwei,HI_PROT_para_shiwei,HI_PROT_para_gewei;
	 u8 COMMCAT_para_baiwei,COMMCAT_para_shiwei,COMMCAT_para_gewei;
         s8 a=0;
u16 TR[]={40,50,60,80,100,120,160,200,240,300,400,500,600,800,1000,1200};

	 if(KEY_set==0)
	 {
	    Work_num++;
	   while(KEY_set==0);
	   	if(Work_num>11)
		Work_num=0;
	 }
	  

	 switch(Work_num)
	 {
	 
	  case 1:								//CT互感器参数设置
	  {
		 Clera_lcd();
		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setCT_Seg,3);
   			//CT_para从eeprom读出
a=AT24CXX_ReadOneByte(0xa000);

CT_para=TR[a];
		  CT_para_qianwei=CT_para/1000;
		  CT_para_baiwei=(CT_para%1000)/100;
		  CT_para_shiwei=(CT_para%100)/10;
		  CT_para_gewei=0;
		  WriteAll_1621(12,num567Seg+2*CT_para_qianwei,2);	//
		  WriteAll_1621(10,num567Seg+2*CT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*CT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*CT_para_gewei,2);	//

		  if(KEY_up==0)
		 {
			a++;
			while(KEY_up==0);
		    if(a>15)a=15;
			CT_para=TR[a];
		 }
		 if(KEY_down==0)
		 {
		    a--;
			while(KEY_down==0);
			if(a<1)a=0;
			CT_para=TR[a];
		 }
		  
		  AT24CXX_WriteOneByte(0xa000,a);   //存储CT_para到eeprom
		 break;

	  }
	  case 2:				//投入延时参数设置
	  {
	  	 Clera_lcd();
		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setdelaytime_Seg,3);

		 Write_1621(19,0x08);	//

		 DELAY_ON_para=AT24CXX_ReadOneByte(0x1000);  //存储DELAY_ON_para到eeprom


		  
		  DELAY_ON_para_baiwei=DELAY_ON_para/100;
		  DELAY_ON_para_shiwei=(DELAY_ON_para%100)/10;
		  DELAY_ON_para_gewei=DELAY_ON_para%10;

		  WriteAll_1621(10,num567Seg+2*DELAY_ON_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*DELAY_ON_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*DELAY_ON_para_gewei,2);	//

		  if(KEY_up==0)
		 {
			DELAY_ON_para++;
			while(KEY_up==0);
			if(DELAY_ON_para>100)DELAY_ON_para=100;
		 }
		 if(KEY_down==0)
		 {
			DELAY_ON_para--;
			while(KEY_down==0);
			if(DELAY_ON_para<1)DELAY_ON_para=1;
		 }
		  
		 AT24CXX_WriteOneByte(0x1000,DELAY_ON_para);  //存储DELAY_ON_para到eeprom
		 break;
	  }
	  case 3:		  //切除延时参数设置
	  {
	  	 Clera_lcd();
	   	 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setdelaytime_Seg,3);

		  Write_1621(16,0x08);	//
		 DELAY_OFF_para=AT24CXX_ReadOneByte(0x2000);  //存储DELAY_OFF_para到eeprom

		
		  
		  DELAY_OFF_para_baiwei=DELAY_OFF_para/100;
		  DELAY_OFF_para_shiwei=(DELAY_OFF_para%100)/10;
		  DELAY_OFF_para_gewei=DELAY_OFF_para%10;

		  WriteAll_1621(10,num567Seg+2*DELAY_OFF_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*DELAY_OFF_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*DELAY_OFF_para_gewei,2);	//

		   if(KEY_up==0)
		 {
			DELAY_OFF_para++;
			while(KEY_up==0);
			if(DELAY_OFF_para>100)DELAY_OFF_para=100;
		 }
		 if(KEY_down==0)
		 {
			DELAY_OFF_para--;
			while(KEY_down==0);
			if(DELAY_OFF_para<1)DELAY_OFF_para=1;
		 }

			 AT24CXX_WriteOneByte(0x2000,DELAY_OFF_para);  //存储DELAY_ON_para到eeprom

		  break;
	  }
	  case 4:	  //投入COS参数设置
	  {
	  	 Clera_lcd();

		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setcos_Seg,3);

		
		 COS_ON_para=AT24CXX_ReadOneByte(0x3000);  //存储DELAY_OFF_para到eeprom

		  
		  COS_ON_para_baiwei=COS_ON_para/100;
		  COS_ON_para_shiwei=(COS_ON_para%100)/10;
		  COS_ON_para_gewei=COS_ON_para%10;

 		  WriteAll_1621(25,num9_12Seg+3*COS_ON_para_baiwei,3);	//
  		  WriteAll_1621(22,num10dp9_12dp11Seg+3*COS_ON_para_shiwei,3);	//
		  WriteAll_1621(19,num11_dp22Seg+3*COS_ON_para_gewei,3);	//

  if(KEY_up==0)
		 {
			COS_ON_para++;
			while(KEY_up==0);
			if(COS_ON_para>100)COS_ON_para=100;
		 }
		 if(KEY_down==0)
		 {
			COS_ON_para--;
			while(KEY_down==0);
			if(COS_ON_para<80)COS_ON_para=80;
		 }
			 AT24CXX_WriteOneByte(0x3000,COS_ON_para);  //存储DELAY_ON_para到eeprom
		 break;

	  }
	  case 5:		//切除COS参数设置
	  {
	  	 Clera_lcd();
		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setcos_Seg,3);
		 
		 Write_1621(16,0x08);	//

				 COS_OFF_para=AT24CXX_ReadOneByte(0x4000);  //存储DELAY_OFF_para到eeprom
 

		  
		  COS_OFF_para_baiwei=COS_OFF_para/100;
		  COS_OFF_para_shiwei=(COS_OFF_para%100)/10;
		  COS_OFF_para_gewei=COS_OFF_para%10;

		  WriteAll_1621(25,num9_12Seg+3*COS_OFF_para_baiwei,3);	//
  		  WriteAll_1621(22,num10dp9_12dp11Seg+3*COS_OFF_para_shiwei,3);	//
		  WriteAll_1621(19,num9_12Seg+3*COS_OFF_para_gewei,3);	//

		 if(KEY_up==0)
		 {
			COS_OFF_para++;
			while(KEY_up==0);
			if(COS_OFF_para>100)COS_OFF_para=100;
		 }
		 if(KEY_down==0)
		 {
			COS_OFF_para--;
			while(KEY_down==0);
            if(COS_OFF_para<80)COS_OFF_para=80;
		 } 
					 AT24CXX_WriteOneByte(0x4000,COS_OFF_para);  //存储DELAY_ON_para到eeprom
 
		 break;

	  }
	  case 6:	   //电压保护参数设置
   if(KEY_3==1) 
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setvoltprot_Seg,3);

		//CT_para从eeprom读出

		V_PROT_para_L=AT24CXX_ReadOneByte(0xb000);

		  if(V_PROT_para_L==0)
		  	{V_PROT_para_baiwei=0;
                      V_PROT_para_shiwei=0;
                     V_PROT_para_gewei=0;
		      }
         else
		  {
		  V_PROT_para_baiwei=(V_PROT_para_L+200)/100;
		  V_PROT_para_shiwei=((V_PROT_para_L+200)%100)/10;
		  V_PROT_para_gewei=(V_PROT_para_L+200)%10;
		  	}
		  WriteAll_1621(10,num567Seg+2*V_PROT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*V_PROT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*V_PROT_para_gewei,2);	//
		  
		   if(KEY_up==0)
		 {
			if(V_PROT_para_L==0)V_PROT_para_L=20;
			if((V_PROT_para_L>=20)&&(V_PROT_para_L<90))V_PROT_para_L=V_PROT_para_L+10;
			while(KEY_up==0);
			if(V_PROT_para_L>=90)V_PROT_para_L=0;
		 }
		 if(KEY_down==0)
		 {
			if(V_PROT_para_L==0)V_PROT_para_L=90;
			if((V_PROT_para_L>20)&&(V_PROT_para_L<=90))V_PROT_para_L=V_PROT_para_L-10;
			while(KEY_down==0);
			if(V_PROT_para_L<=20)V_PROT_para_L=0;

		 }
		  //存储CT_para到eeprom
 AT24CXX_WriteOneByte(0xb000,V_PROT_para_L);

		 break;
	  }
	   if(KEY_3==0) 
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setvoltprot_Seg,3);

		//CT_para从eeprom读出

		V_PROT_para_tri=AT24CXX_ReadOneByte(0xc000);

		  if(V_PROT_para_tri==0)
		  	{V_PROT_para_baiwei=0;
                      V_PROT_para_shiwei=0;
                     V_PROT_para_gewei=0;
		      }
         else
		  {
		  V_PROT_para_baiwei=(V_PROT_para_tri+400)/100;
		  V_PROT_para_shiwei=((V_PROT_para_tri+400)%100)/10;
		  V_PROT_para_gewei=(V_PROT_para_tri+400)%10;
		  	}
		  WriteAll_1621(10,num567Seg+2*V_PROT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*V_PROT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*V_PROT_para_gewei,2);	//
		  
		   if(KEY_up==0)
		 {
			if((V_PROT_para_tri>=0)&&(V_PROT_para_tri<90))V_PROT_para_tri=V_PROT_para_tri+10;
			while(KEY_up==0);
			if(V_PROT_para_tri>=90)V_PROT_para_tri=0;
		 }
		 if(KEY_down==0)
		 {
			if((V_PROT_para_tri>0)&&(V_PROT_para_tri<=80))V_PROT_para_tri=V_PROT_para_tri-10;
			while(KEY_down==0);
			if(V_PROT_para_tri==0)V_PROT_para_tri=0;

		 }
		  //存储CT_para到eeprom
 AT24CXX_WriteOneByte(0xc000,V_PROT_para_tri);

		 break;
	  }  
	  case 7:	   //投入门限参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_setON0hold_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setON1hold_Seg,3);

		ON_HOLD_para=AT24CXX_ReadOneByte(0x5000); 
 

		  
		  ON_HOLD_para_shiwei=ON_HOLD_para/10;
		  ON_HOLD_para_gewei=ON_HOLD_para%10;

  		  WriteAll_1621(8,num567Seg+2*ON_HOLD_para_shiwei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*ON_HOLD_para_gewei,2);	//
		  
			if(KEY_up==0)
		 {
		 	delay_ms(10); 
			ON_HOLD_para++;
			while(KEY_up==0);
			delay_ms(10);
			if(ON_HOLD_para>12)ON_HOLD_para=2;
		 }
		 if(KEY_down==0)
		 {
			ON_HOLD_para--;
			while(KEY_down==0);
			if(ON_HOLD_para<2)ON_HOLD_para=12;
		 }
		  //存储CT_para到eeprom
		 AT24CXX_WriteOneByte(0x5000,ON_HOLD_para);  //存储DELAY_ON_para到eeprom

		break;

	  }
	  case 8:	  //切除门限参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_setOFF0hold_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setOFF1hold_Seg,3);

	

		 
		OFF_HOLD_para=AT24CXX_ReadOneByte(0x6000); 

		  
		  OFF_HOLD_para_shiwei=OFF_HOLD_para/10;
		  OFF_HOLD_para_gewei=OFF_HOLD_para%10;

  		  WriteAll_1621(8,num567Seg+2*OFF_HOLD_para_shiwei,2);	//
		  WriteAll_1621(14,num8_dp7Seg+2*OFF_HOLD_para_gewei,2);	//
		  
		    if(KEY_up==0)
		 {
			OFF_HOLD_para++;
			while(KEY_up==0);
			if(OFF_HOLD_para>12)OFF_HOLD_para=2;
		 }
		 if(KEY_down==0)
		 {
			OFF_HOLD_para--;
			while(KEY_down==0);
			if(OFF_HOLD_para<2)OFF_HOLD_para=12;
		 }
		  //存储CT_para到eeprom
		 AT24CXX_WriteOneByte(0x6000,OFF_HOLD_para);  //存储DELAY_ON_para到eeprom

		break;

	  }
	  case 9:	 //谐波电压参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_sethuhiprot_Seg,3);

		WriteAll_1621(25,numHU_prot,3);
		WriteAll_1621(22,numHU_prot+3,3);

			HU_PROT_para=AT24CXX_ReadOneByte(0x7000); 
	  

		  HU_PROT_para_baiwei=HU_PROT_para/100;
		  HU_PROT_para_shiwei=(HU_PROT_para%100)/10;
		  HU_PROT_para_gewei=HU_PROT_para%10;

		  WriteAll_1621(10,num567Seg+2*HU_PROT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*HU_PROT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*HU_PROT_para_gewei,2);	//

		   if(KEY_up==0)
		 {
			HU_PROT_para++;
		    while(KEY_up==0);
			if(HU_PROT_para>100)HU_PROT_para=0;
		 }
		 if(KEY_down==0)
		 {
			HU_PROT_para--;
			while(KEY_down==0);
			if(HU_PROT_para<1)HU_PROT_para=100;
		 }
		 		 AT24CXX_WriteOneByte(0x7000,HU_PROT_para);  //存储DELAY_ON_para到eeprom

		break;

	  }

	  case 10:		 //谐波电流参数设置
	  {
	   Clera_lcd();
	   if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
	   if(Work_Flag==0)WriteAll_1621(29,num_sethuhiprot_Seg,3);

	   WriteAll_1621(25,numHI_prot,3);
	   WriteAll_1621(22,numHI_prot+3,3);

	   			HI_PROT_para=AT24CXX_ReadOneByte(0x8000); 


		  HI_PROT_para_baiwei=HI_PROT_para/100;
		  HI_PROT_para_shiwei=(HI_PROT_para%100)/10;
		  HI_PROT_para_gewei=HI_PROT_para%10;

		  WriteAll_1621(10,num567Seg+2*HI_PROT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*HI_PROT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*HI_PROT_para_gewei,2);	//

		  if(KEY_up==0)
		 {
			HI_PROT_para++;
			while(KEY_up==0);
			if(HI_PROT_para>100)HI_PROT_para=0;
		 }
		 if(KEY_down==0)
		 {
			HI_PROT_para--;
			while(KEY_down==0);
			if(HI_PROT_para<1)HI_PROT_para=100;
		 }
		 		 		 AT24CXX_WriteOneByte(0x8000,HI_PROT_para);  //存储DELAY_ON_para到eeprom

	   break;

	  }
	  case 11:	  //通信地址参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setcommu_Seg,3);
		
			

		 COMMCAT_para_baiwei=COMMCAT_para/100;
		 COMMCAT_para_shiwei=(COMMCAT_para%100)/10;
		 COMMCAT_para_gewei=COMMCAT_para%10;

		 WriteAll_1621(10,num567Seg+2*COMMCAT_para_baiwei,2);	//
  		 WriteAll_1621(8,num567Seg+2*COMMCAT_para_shiwei,2);	//
		 WriteAll_1621(14,num8Seg+2*COMMCAT_para_gewei,2);	//

		   if(KEY_up==0)
		 {
			COMMCAT_para++;
			while(KEY_up==0);
			if(COMMCAT_para>250)COMMCAT_para=250;
		 }
		 if(KEY_down==0)
		 {
			COMMCAT_para--;
			while(KEY_down==0);
			if(COMMCAT_para<1)COMMCAT_para=0;
		 }
		break;

	  }

	  default:	{Graf_display();break;}
	 
	}
}
void Graf_display(void)
{
	u8 CAPA_num_shiwei,CAPA_num_gewei,capa1_value_shiwei,capa1_value_gewei,capa2_value_shiwei,capa2_value_gewei;
	u8 numCAP[]={0X00,0X02,0X00,0X00,0X05,0X06};
u8 num11_p21Seg[]={0X06,0X0D,0X06,0X06,0X08,0X00,0X04,0X0F,0X02,0X06,0X0F,0X00,0X06,0X0A,0X04,0X02,0X0F,0X04,0X02,0X0F,0X06,0X06,0X0C,0X00,0X06,0X0F,0X06,0X06,0X0F,0X04};
 u8 num1234Seg[]={0X0A,0X0F,0X00,0X06,0X06,0X0D,0X04,0X0F,0X0C,0X06,0X0C,0X0B,0X0E,0X0B,0X00,0X0E,0X0E,0X0F,0X0C,0X0F};
u8 num567Seg[]={0X0F,0X05,0X06,0X00,0X0B,0X06,0X0F,0X02,0X06,0X03,0X0D,0X03,0X0D,0X07,0X07,0X00,0X0F,0X07,0X0F,0X03};
u8 num8Seg[]={0X05,0X0F,0X00,0X06,0X06,0X0B,0X02,0X0F,0X03,0X06,0X03,0X0D,0X07,0X0D,0X00,0X07,0X07,0X0F,0X03,0X0F};
u8 num9_12Seg[]={0X06,0X05,0X06,0X06,0X00,0X00,0X04,0X07,0X02,0X06,0X07,0X00,0X06,0X02,0X04,0X02,0X07,0X04,0X02,0X07,0X06,0X06,0X04,0X00,0X06,0X07,0X06,0X06,0X07,0X04};
u8 num3_p11Seg[]={0X0B,0X0F,0X01,0X06,0X07,0X0D,0X05,0X0F,0X0D,0X06,0X0D,0X0B,0X0F,0X0B,0X01,0X0E,0X0F,0X0F,0X0D,0X0F};
	if(KEY_up==0)
 		{
		 Display_num++;
		 while(KEY_up==0);
		 if(Display_num>6)Display_num=1;
	    }
	if(KEY_down==0)
	  {
		 Display_num--;
		 while(KEY_down==0);
		 if(Display_num<1)Display_num=6;
	  }
   switch(Display_num)
   {
   	 case 1:										   //显示功率因数电流电压
     {
  if(KEY_3==0) 
              {
		 Clera_lcd();
		 Graf_cos_volt_current(gonglvshishu*10,dianya_zhi*10,dianliuzhi*10);
            	}
   if(KEY_3==1) 
   	{
	if(KEY_right==0)
 		{
		 L1_L2_L3_COS++;
		 while(KEY_right==0);
		 if(L1_L2_L3_COS>3)L1_L2_L3_COS=1;
	    }
	if(KEY_left==0)
	  {
		 L1_L2_L3_COS--;
		 while(KEY_left==0);
		 if(L1_L2_L3_COS<1)L1_L2_L3_COS=3;
	  }
  if(L1_L2_L3_COS==1)
   	{
		 Clera_lcd();
		 Graf_cos_volt_current_L1(gonglvshishu_A*10,dianya_zhi_A*10,dianliuzhi_A*10);
  	}
  if(L1_L2_L3_COS==2)
   		{ 
   		Clera_lcd();
		 Graf_cos_volt_current_L2(gonglvshishu_B*10,dianya_zhi_B*10,dianliuzhi_B*10);
		}
  if(L1_L2_L3_COS==3)
  	{
		  Clera_lcd();
		 Graf_cos_volt_current_L3(gonglvshishu_C*10,dianya_zhi_C*10,dianliuzhi_C*10);

  	}
   }

break;
     }
	 case 2:	//显示无功有功频率
  if(KEY_3==0) 
		{
		 Clera_lcd();
		 Graf_powuse_poweunuse_freq(wugongkvar*10,allkvar*10,501);
	 	}
  if(KEY_3==1) 
              {
	if(KEY_right==0)
 		{
		 L1_L2_L3_KAR++;
		 while(KEY_right==0);
		 if(L1_L2_L3_KAR>3)L1_L2_L3_KAR=1;
	    }
	if(KEY_left==0)
	  {
		 L1_L2_L3_KAR--;
		 while(KEY_left==0);
		 if(L1_L2_L3_KAR<1)L1_L2_L3_KAR=3;
	  }

		if(L1_L2_L3_KAR==1)
			{
		 Clera_lcd();
		 Graf_powuse_poweunuse_freq_L1(wugongkvar_A*10,allkvar*10,501);
			}
		if(L1_L2_L3_KAR==2)
			{
		 Clera_lcd();
		 Graf_powuse_poweunuse_freq_L2(wugongkvar_B*10,allkvar*10,501);
			}
		if(L1_L2_L3_KAR==3)
			{
		 Clera_lcd();
		 Graf_powuse_poweunuse_freq_L3(wugongkvar_C*10,allkvar*10,501);
			}
		}
  
		 break;
	 case 3:											  //显示温度电压谐波电流谐波
           if(KEY_3==0)
           	{
		   Clera_lcd();
		 Graf_temp_hv_hi(tempshuzhi*10,HV*10,HI*10);
           	}
	  if(KEY_3==1)
           	{
           		if(KEY_right==0)
 		{
		 L1_L2_L3_KAR++;
		 while(KEY_right==0);
		 if(L1_L2_L3_KAR>3)L1_L2_L3_KAR=1;
	    }
	if(KEY_left==0)
	  {
		 L1_L2_L3_KAR--;
		 while(KEY_left==0);
		 if(L1_L2_L3_KAR<1)L1_L2_L3_KAR=3;
	  }
	
		 if(L1_L2_L3_KAR==1)
		 	{
		 	Clera_lcd();
		 Graf_temp_hv_hi_L1(tempshuzhi*10,HV*10,HI*10);
		 	}
		  if(L1_L2_L3_KAR==2)
		 	{
		 	Clera_lcd();
		 Graf_temp_hv_hi_L2(tempshuzhi*10,HV*10,HI*10);
		 	}
		  if(L1_L2_L3_KAR==3)
		 	{
		 	Clera_lcd();
		 Graf_temp_hv_hi_L3(tempshuzhi*10,HV*10,HI*10);
		 	}
		 }	   
		 break;
	 case 4:											//显示版本号
		  Clera_lcd();
		  Graf_VER(1);
		 break;

	 case 5:											//显示电容组号及容量
		  Clera_lcd();

			Write_1621(29,0x04);	//	p0显示电容符号		
			Write_1621(28,0x01);	//	p25显示“动控制”
			

		  WriteAll_1621(22,numCAP,6);

   		  CAPA_num_shiwei=CAPA_num/10;
		  CAPA_num_gewei=CAPA_num%10;
	   	  capa1_value_shiwei=capa1_value/10;
		  capa1_value_gewei=capa1_value%10;
		  capa2_value_shiwei=capa2_value/10;
		  capa2_value_gewei=capa2_value%10;

		  WriteAll_1621(19,num11_p21Seg+3*CAPA_num_shiwei,3);
		  WriteAll_1621(16,num9_12Seg+3*CAPA_num_gewei,3);
		  WriteAll_1621(8,num567Seg+2*capa1_value_shiwei,2);
		  WriteAll_1621(14,num8Seg+2*capa1_value_gewei,2);
		  WriteAll_1621(4,num3_p11Seg+2*capa2_value_shiwei,2);
		  WriteAll_1621(6,num1234Seg+2*capa2_value_gewei,2);
//		  Graf_capa_value(0,15,35);
		  
		  if(KEY_right==0)
		  {
			CAPA_num++;
			while(KEY_right==0);
		  	if(CAPA_num>32)CAPA_num=1;

				capa1_value=capa1_array[CAPA_num];
				capa2_value=capa2_array[CAPA_num];

		  }
		  if(KEY_left==0)
		  {
			CAPA_num--;
			while(KEY_left==0);
		  	if(CAPA_num<1)CAPA_num=32;
				capa1_value=capa1_array[CAPA_num];
			capa2_value=capa2_array[CAPA_num];

			
		  }

		  break;

	 case 6:										   //显示进柜三相电流

	 Clera_lcd();
	 Graf_current_value(dianya_zhi_A*10,dianya_zhi_B*10,dianya_zhi_C*10);
	 break;
   
   }

}

