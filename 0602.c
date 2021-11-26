#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
uchar num[3];
uint i,flag,sum;
/*****************
函数:init
功能:初始化
*****************/
void init()
{
	TMOD=0x20;  //设定定时器工作方式2
	SCON=0x50;  //设置scon
	TH1=TL1=0xfd;  //装入波特率9600对应的初值
	TR1=1;  //开始计时
	EA=1;  //开启总中断
	ES=1; //开启串口中断
}
/*****************
函数:ser
功能:接收字符串
******************/
void ser() interrupt 4
{
	RI=0;
	num[i++]=SBUF;  //接收字符串
	flag++;
}
/******************
函数:main
功能:主函数
******************/
void main()
{
	init();
	while(1)
	{
		 if(flag==3)
		 {
			 ES=0;   //关闭串口中断
			 sum=(num[0]-'0')*100+(num[1]-'0')*10+num[2]-'0'+15;
			 TI=1;
			 printf("%d",sum);   //输出字符
			 while(!TI);
			 TI=0;   //将TI归0
			 ES=1; 
			 flag=0;
		 }
	 }
}

			 
	
	