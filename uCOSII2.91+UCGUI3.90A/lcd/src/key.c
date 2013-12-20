
/* Includes ------------------------------------------------------------------*/
#include <includes.h>

/* Private variables ---------------------------------------------------------*/	
extern u8 Work_Flag;

u8 Work_num=0;	  //   设置参数页面数
u8 Display_num=1;	  //正常显示页面数
 u16 CT_para=1;
 u8 DELAY_ON_para=1;
 u8 DELAY_OFF_para=1;
 u8 COS_ON_para=1;
 u8 COS_OFF_para=1;
 u16 V_PROT_para=1;
 u8 ON_HOLD_para=1;
 u8 OFF_HOLD_para=1;
 u8 HU_PROT_para=1;
 u8 HI_PROT_para=1;
 u8 COMMCAT_para=1;
//#endif
/*************************************/
static u8 grafnum=1;
u8 zhongduan_flag=1;
u8 id_num=0;
u8 grafnum,tempshuzhi,vernum=101,hguestnum=222,gonglvshishu=0;
u16 dianya_zhi=0,wugongkvar=0;
u32	dianliuzhi=0;
//#if (FUNCTION_MODULE == DF_THREE)
u16 dianya_zhi_A=0,dianya_zhi_B=0,dianya_zhi_C=0,wugongkvar_A=0,wugongkvar_B=0,wugongkvar_C=0;
u32	dianliuzhi_A=0,dianliuzhi_B=0	,dianliuzhi_C=0;
u8 gonglvshishu_A=0,gonglvshishu_B=0,gonglvshishu_C=0;
//#endif


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
{/*
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	GPIOA->CRH&=0XFFF00FFF;	//PA11 PA12设置成输入	  
	GPIOA->CRH|=0X00088000; 
	GPIOA->ODR|=1<11;		// 上拉
	GPIOA->ODR|=1<12;		  //上拉
	*/
		 GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

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

	 u8 CT_para_baiwei,CT_para_shiwei,CT_para_gewei;
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
		 

		  
		  CT_para_baiwei=CT_para/100;
		  CT_para_shiwei=(CT_para%100)/10;
		  CT_para_gewei=CT_para%10;

		  WriteAll_1621(10,num567Seg+2*CT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*CT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*CT_para_gewei,2);	//

		  if(KEY_up==0)
		 {
			CT_para++;
			while(KEY_up==0);
		    if(CT_para>1200)CT_para=1200;
		 }
		 if(KEY_down==0)
		 {
		    CT_para--;
			while(KEY_down==0);
			if(CT_para<10)CT_para=10;
		 }
		  
		  //存储CT_para到eeprom
		 break;

	  }
	  case 2:				//投入延时参数设置
	  {
	  	 Clera_lcd();
		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setdelaytime_Seg,3);

		 Write_1621(19,0x08);	//

		 

		  
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
		  
		  //存储CT_para到eeprom
		 break;
	  }
	  case 3:		  //切除延时参数设置
	  {
	  	 Clera_lcd();
	   	 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setdelaytime_Seg,3);

		  Write_1621(16,0x08);	//

		
		  
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

		  //存储CT_para到eeprom

		  break;
	  }
	  case 4:	  //投入COS参数设置
	  {
	  	 Clera_lcd();

		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setcos_Seg,3);

		

		  
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
		  //存储CT_para到eeprom
		 break;

	  }
	  case 5:		//切除COS参数设置
	  {
	  	 Clera_lcd();
		 if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		 if(Work_Flag==0)WriteAll_1621(29,num_setcos_Seg,3);
		 
		 Write_1621(16,0x08);	//

		 

		  
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
		  //存储CT_para到eeprom
		 break;

	  }
	  case 6:	   //电压保护参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setvoltprot_Seg,3);

		//CT_para从eeprom读出

		

		  
		  V_PROT_para_baiwei=V_PROT_para/100;
		  V_PROT_para_shiwei=(V_PROT_para%100)/10;
		  V_PROT_para_gewei=V_PROT_para%10;

		  WriteAll_1621(10,num567Seg+2*V_PROT_para_baiwei,2);	//
  		  WriteAll_1621(8,num567Seg+2*V_PROT_para_shiwei,2);	//
		  WriteAll_1621(14,num8Seg+2*V_PROT_para_gewei,2);	//
		  
		   if(KEY_up==0)
		 {
			if(V_PROT_para==0)V_PROT_para=400;
			if((V_PROT_para>=400)&&(V_PROT_para<480))V_PROT_para=V_PROT_para+10;
			while(KEY_up==0);
			if(V_PROT_para>=490)V_PROT_para=0;
		 }
		 if(KEY_down==0)
		 {
			if(V_PROT_para==0)V_PROT_para=480;
			if((V_PROT_para>400)&&(V_PROT_para<=480))V_PROT_para=V_PROT_para-10;
			while(KEY_down==0);
			if(V_PROT_para<=390)V_PROT_para=0;

		 }
		  //存储CT_para到eeprom


		 break;
	  }
	  case 7:	   //投入门限参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_setON0hold_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setON1hold_Seg,3);

		 

		  
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

		break;

	  }
	  case 8:	  //切除门限参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_setOFF0hold_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_setOFF1hold_Seg,3);

	

		 

		  
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

		break;

	  }
	  case 9:	 //谐波电压参数设置
	  {
	  	Clera_lcd();
		if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
		if(Work_Flag==0)WriteAll_1621(29,num_sethuhiprot_Seg,3);

		WriteAll_1621(25,numHU_prot,3);
		WriteAll_1621(22,numHU_prot+3,3);

		  

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
		break;

	  }

	  case 10:		 //谐波电流参数设置
	  {
	   Clera_lcd();
	   if(Work_Flag==1)WriteAll_1621(29,num_set_Seg,3);
	   if(Work_Flag==0)WriteAll_1621(29,num_sethuhiprot_Seg,3);

	   WriteAll_1621(25,numHI_prot,3);
	   WriteAll_1621(22,numHI_prot+3,3);

	   

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
   	 case 1:
		 Clera_lcd();
		 Graf_cos_volt_current(98,380,532);
		 break;

	 case 2:
		 Clera_lcd();
		 Graf_powuse_poweunuse_freq(2536,5431,501);
		 break;
	 case 3:
   		 Clera_lcd();
		 Graf_temp_hv_hi(65,99,98);
		 break;
	 case 4:
		  Clera_lcd();
		 Graf_cos_volt_current(98,380,532);
		 break;

	 case 5:
		  Clera_lcd();
		 Graf_powuse_poweunuse_freq(2536,5431,501);
		  break;

	 case 6:

	 Clera_lcd();
	 Graf_temp_hv_hi(65,99,98);
	 break;
   
   }

}

