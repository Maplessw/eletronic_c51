/********************
*LCD1602显示
*三个灯闪烁
*呼吸灯
********************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit lcden=P2^7;
sbit lcdrs=P2^6;
sbit lcdwr=P2^5;
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;
sbit key1=P3^2;
bit ison;  //定义全局变量
uchar id[11]="2020216191";
uchar sign[15]="sun riseing...";
uchar ssw[11]="Go for it!";
int num1,num,num2,num3;
/********************
*函数:delay
*功能:延时
********************/
void delay(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
	{
		for(j=110;j>0;j--)
		{
		}
	}
}
/********************
*函数:write_com
*功能:写入指令
********************/
void write_com(uchar com)
{
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
/********************
*函数:write_data
*功能:写入数据
********************/
void write_data(uchar date)
{
	lcdrs=1;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
/*******************
*函数:T0_time
*功能:定时器0中断
*******************/
void T0_time() interrupt 1
{
	TH0=(65536-9216)/256; //重装初值
	TL0=(65536-9216)%256;
	num1++;
	num2--;
	if(num2==-1)
		num2=60;
	if(num1==100)  //到达一秒时
		{
			num--;
      led3=~led3;			
			num1=0;   //赋值为0重新计数
			if(num==-1)  
			{
				num=60;
			}
		}
	if(!(num1%20))
		led1=~led1;
	if(!(num1%50))
		led2=~led2;
}
/*******************
*函数:INT_0
*功能:外部中断0
*******************/
void INT_0() interrupt 0
{
	if(key1==0)
	{
		delay(5);
		if(key1==0)
		{
			ison=~ison;
			while(!key1);
		}
	}
}
/*********************
*函数:init
*功能:初始化
*********************/
void init()
{
	lcdwr=0;
	lcden=0;
	led4=0;
	TMOD=0x21;  //选择01工作方式
	TH0=(65536-9216)/256;  //装入初始值
	TL0=(65536-9216)%256;
	TH1=TL1=256-92;
	write_com(0x38);   
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	EA=1;  
	ET0=1;
	TR0=1;
	ET1=0;  //没有打开定时器1
	EX0=1;  //打开外部中断0
	IT0=1;  //下降沿
	TR1=0;  //没有开始计时
}
/*******************
*函数:T1_time
*功能:计时
*******************/
void T1_time() interrupt 3
{
	num3++;         //构造呼吸灯
	if(num3<=20)
		led4=0;
	else if(num3<=50)
		led4=1;
	else if(num3<=80)
		led4=1;
	else if(num3<100)
		led4=0;
	else
		num3=0;
}
/*********************
*函数:main
*功能:主函数
*********************/
void main()
{
	uint shi,ge,i,dian1,dian2;
	init();
	num=60,num2=10;
	while(1)
	{
		write_com(0x80);
		shi=num/10;
		ge=num%10;
		dian1=num2/10;
		dian2=num2%10;
		write_data(shi+'0');  //输入十位
		write_data(ge+'0');  //输入个位
		write_data(':');
		write_data(dian1+'0');
		write_data(dian2+'0');
		write_com(0x80+0x40);  
		for(i=0;i<10;i++)
	  {
		  write_data(id[i]);  //输入学号
			delay(5);
	  }
		if(ison)  //开始呼吸
		{
			ET1=1;
			TR1=1;
		}
		else   //停止呼吸
		{
			TR1=0;
			ET1=0;
		}
		write_com(0x80+0x10);
		for(i=0;i<10;i++)
		{
			write_data(ssw[i]);
			delay(5);
		}
		write_com(0x80+0x50);
		for(i=0;i<14;i++)
		{
			write_data(sign[i]);
			delay(5);
		}
		for(i=0;i<16;i++)
		{
			write_com(0x18);
			delay(200);
		}
	}
}
		
		
		
	
	
	
	

	