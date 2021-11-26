#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
uchar num[3];
uint i,flag,sum;
/*****************
����:init
����:��ʼ��
*****************/
void init()
{
	TMOD=0x20;  //�趨��ʱ��������ʽ2
	SCON=0x50;  //����scon
	TH1=TL1=0xfd;  //װ�벨����9600��Ӧ�ĳ�ֵ
	TR1=1;  //��ʼ��ʱ
	EA=1;  //�������ж�
	ES=1; //���������ж�
}
/*****************
����:ser
����:�����ַ���
******************/
void ser() interrupt 4
{
	RI=0;
	num[i++]=SBUF;  //�����ַ���
	flag++;
}
/******************
����:main
����:������
******************/
void main()
{
	init();
	while(1)
	{
		 if(flag==3)
		 {
			 ES=0;   //�رմ����ж�
			 sum=(num[0]-'0')*100+(num[1]-'0')*10+num[2]-'0'+15;
			 TI=1;
			 printf("%d",sum);   //����ַ�
			 while(!TI);
			 TI=0;   //��TI��0
			 ES=1; 
			 flag=0;
		 }
	 }
}

			 
	
	