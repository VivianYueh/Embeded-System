#include<reg52.h> //�]�t���Y�ɡA�@�뱡�p���ݭn��ʡA���Y�ɥ]�t�S��\��H�s�����w�q 
#include <string.h>                       
#define MAX 10
#define DataPort P0 //�w�q��ư� �{�����J��DataPort �h��P0 ����
typedef unsigned char byte;
typedef unsigned int  word;

byte buf[MAX];
byte head = 0;

byte get_0d = 0;
byte rec_flag = 0;
sbit k1 = P1^0;
sbit k2 = P1^1;
sbit LATCH1=P2^2;//�w�q��s�ϯ�� �q��s
sbit LATCH2=P2^3;//                 ����s

unsigned char code dofly_DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	         0x77,0x7c,0x39,0x5e,0x79,0x71,0x54,0x79};// ��ܬq�X��0~F
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//���O�����������ƽX���I�G,�Y��X

unsigned char TempData[10]; //�s�x��ܭȪ������ܼ�
unsigned char Ans[5];
unsigned char g[5];
void Display(unsigned char FirstBit,unsigned char Num);//�ƽX����ܨ��
void DelayUs2x(unsigned char t);//us�ũ��ɨ禡�ŧi 
void DelayMs(unsigned char t); //ms�ũ���
void delay(unsigned char t);
void Song(void);
/*------------------------------------------------
                   �禡�ŧi
------------------------------------------------*/
void SendStr(unsigned char *s);

/*------------------------------------------------
                    ��f��l��
------------------------------------------------*/
void InitUART  (void)
{

    SCON  = 0x50;		        // SCON: �Ҧ� 1, 8-bit UART, �ϯ౵��  
    TMOD |= 0x21;               // TMOD: timer 1, mode 2, 8-bit ����,timer 0 , mode 1
    TH1   = 0xFD;               // TH1:  ���˭� 9600 ��C�ǿ�t�v ���� 11.0592MHz  
    TR1   = 1;                  // TR1:  timer 1 ���}                         
    EA    = 1;                  //���}�`���_
	ET0=1;           //�p�ɾ����_���}
 	TR0=1;           //�p�ɾ��}�����}
   // ES    = 1;                  //���}��f���_
}                            
/*------------------------------------------------
                    �D���
------------------------------------------------*/
void main (void)
{
bit set=0;
unsigned char j,a,b;
word i;
InitUART();
SendStr("UART test�A�޳N�׾¡Gwww.doflye.net �Цb�o�e�Ͽ�J���N��T\r\n");
ES    = 1;                  //���}��f���_
		while (1)                       
		    {
					if (rec_flag == 1)
					{ 
						buf[head] = '\0';
						rec_flag = 0;
						head = 0;
						if(buf[0]=='s'){ 	//�]�m����
							for(j=0;j<4;j++){
								Ans[j]=buf[j+1]-'0';
							}
							SendStr("HELLO SHIN\r\n");
						}
						else if(buf[0]=='g'){	//Ū���q��
							a=0;
							b=0;
							g[0]=buf[1]-'0';
							g[1]=buf[2]-'0';
							g[2]=buf[3]-'0';
							g[3]=buf[4]-'0';
							TempData[0]=dofly_DuanMa[g[0]];
							TempData[1]=dofly_DuanMa[g[1]];
							TempData[2]=dofly_DuanMa[g[2]];
							TempData[3]=dofly_DuanMa[g[3]];
							SendStr("DOIT SHIN\r\n");

							if(g[0]==Ans[0])	a++;
							else if(g[0]==Ans[1]||g[0]==Ans[2]||g[0]==Ans[3])	b++;

							if(g[1]==Ans[1])	a++;
							else if(g[1]==Ans[0]||g[1]==Ans[2]||g[1]==Ans[3])	b++;

							if(g[2]==Ans[2])	a++;
							else if(g[2]==Ans[0]||g[2]==Ans[1]||g[2]==Ans[3])	b++;

							if(g[3]==Ans[3])	a++;
							else if(g[3]==Ans[0]||g[3]==Ans[1]||g[3]==Ans[2])	b++;

							if(a==4){
								TempData[4]=dofly_DuanMa[13];
								TempData[5]=dofly_DuanMa[0];
								TempData[6]=dofly_DuanMa[16];
								TempData[7]=dofly_DuanMa[14];
								SendStr("Finish\r\n");
							}
							else{
								TempData[4]=dofly_DuanMa[a];	//�X��A
								TempData[5]=dofly_DuanMa[10];
								TempData[6]=dofly_DuanMa[b];	//�X��B
								TempData[7]=dofly_DuanMa[11];
							}
							//Display(0,8);
						}
						
						/*if (strcmp(buf,"HELLO") == 0)
						{
							SendStr("HELLO SHIN\r\n");

						}
						else if (strcmp(buf,"DOIT") == 0)
						{
							SendStr("DOIT SHIN\r\n");
						}
						else 						
						{
							SendStr(buf);
							SendStr("\r\n");
						}		*/				
					}
					if (k1 == 0)	//���m
					{
						for(i=0;i<2000;i++);
						if(k1==0)	SendStr("Reset");
						while(k1 == 0);
						for(i=0;i<2000;i++);
						for(j=0;j<8;j++)	TempData[j]=0;
						Display(0,8);
					}
					
		    	
		    }
}

/*------------------------------------------------
                    �o�e�@�Ӧ줸��
------------------------------------------------*/
void SendByte(unsigned char dat)
{
 SBUF = dat;
 while(!TI);
      TI = 0;
}
/*------------------------------------------------
                    �o�e�@�Ӧr��
------------------------------------------------*/
void SendStr(unsigned char *s)
{
 while(*s!='\0')// \0 ��ܦr�굲���лx�A�q�L�˴��O�_�r�꥽��
  {
  SendByte(*s);
  s++;
  }
}
/*------------------------------------------------
                     ��f���_�{��
------------------------------------------------*/
void UART_SER (void) interrupt 4 //��C���_�A�ȵ{��
{
    unsigned char tmp;          //�w�q�{���ܼ� 
   
   if(RI)                        //�P�_�O�������_����
     {
			RI=0;                      //�лx�줸�M�s
			tmp=SBUF;                 //Ū�J�w�İϪ���
			if (get_0d == 0)
			{
					if (tmp == 0x0d) get_0d = 1;
					else
					{
						buf[head]=tmp;              
						head++;
						if (head == MAX) head = 0;	
					}
							     
			}
			else if (get_0d == 1)
			{
				if (tmp != 0x0a)
				{
						head = 0;
						get_0d = 0;
						
				}
				else
				{
					rec_flag = 1;
					get_0d = 0;
				}
			}	
			
		
		//	SBUF=tmp;                 //�Ⱶ���쪺�ȦA�o�^�q����
	 }
//   if(TI)                        //�p�G�O�o�e�лx�줸�A�M�s
//     TI=0;
} 

/*------------------------------------------------
 ��ܨ�ơA�Ω�ʺA���˼ƽX��
 ��J�Ѽ� FirstBit ��ܻݭn��ܪ��Ĥ@��A�p���2��ܱq�ĤT�ӼƽX�޶}�l���
 �p��J0��ܱq�Ĥ@����ܡC
 Num��ܻݭn��ܪ��줸�ơA�p�ݭn���99��줸�ƭȫh�ӭȿ�J2
------------------------------------------------*/
void Display(unsigned char FirstBit,unsigned char Num)
{
      static unsigned char i=0;
	  

	   DataPort=0;   //�M�Ÿ�ơA���������v
       LATCH1=1;     //�q��s
       LATCH1=0;

       DataPort=dofly_WeiMa[i+FirstBit]; //����X 
       LATCH2=1;     //����s
       LATCH2=0;

       DataPort=TempData[i]; //����ܸ�ơA�q�X
       LATCH1=1;     //�q��s
       LATCH1=0;
       
	   i++;
       if(i==Num)
	      i=0;


}

/*------------------------------------------------
                 �p�ɾ����_�Ƶ{��
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
 TH0=(65536-2000)/256;		  //���s��� 2ms
 TL0=(65536-2000)%256;
 
 Display(0,8);       // �եμƽX�ޱ���

}
