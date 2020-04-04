//created by ABHRO //
#include<reg51.h>
sbit DIM=P2^0;
sbit FAN=P2^1;
sbit LIGHT=P2^2;
sbit AIR=P2^3;
sbit WM=P2^4;
sbit FR=P2^5;
 char str;
 char Charin=0;
void delay(int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
 for(j=0;j<1275;j++);
}
void Serialwrite(char byte)
{
  SBUF=byte;
  while(!TI);
  TI=0;
}
void Serialprintln(char *p)
{
  while(*p)
  {
    Serialwrite(*p);
    p++;
  }
  Serialwrite(0x0d);
}
void Serialbegin()
{
   TMOD=0x20;
   SCON=0x50;
   TH1=0xfd;
   TR1=1;
}
void main()
{
  l:
	P2=0x00;
  Serialbegin();
	Charin=SBUF;
  str=Charin;
  Serialprintln("HOME AUTOMATION-- ONLINE ***@bhro***\r\n");
  delay(50);
  while(1)
  {
    while(!RI);
    Charin=SBUF;
    str=Charin;
    RI=0;
      if(str=='1')
      {
        DIM=1;
        Serialprintln(" DIM LIGHT ON \r\n");
        delay(50);
      }
      else if(str=='2')
      {
        DIM=0;
        Serialprintln(" DIM LIGHT OFF \r\n");
        delay(50);
      }
       else if(str=='3')
      {
        FAN=1;
        Serialprintln(" FAN ON \r\n");
        delay(50);
      }
       else if(str=='4')
      {
        FAN=0;
        Serialprintln(" FAN OFF \r\n");
        delay(50);
      }
       else if(str=='5')
      {
        LIGHT=1;
        Serialprintln(" LIGHT ON \r\n");
        delay(50);
      }
       else if(str=='6')
      {
        LIGHT=0;
        Serialprintln(" LIGHT OFF \r\n");
        delay(50);
      }
			 else if(str=='7')
      {
        AIR=1;
        Serialprintln(" AIR ON \r\n");
        delay(50);
      }
       else if(str=='8')
      {
        AIR=0;
        Serialprintln(" AIR OFF \r\n");
        delay(50);
      }
			 else if(str=='9')
      {
        WM=1;
        Serialprintln(" WM ON \r\n");
        delay(50);
      }
       else if(str=='a')
      {
        WM=0;
        Serialprintln(" WM OFF \r\n");
        delay(50);
      }
			 else if(str=='b')
      {
        FR=1;
        Serialprintln(" FR ON \r\n");
        delay(50);
      }
       else if(str=='c')
      {
        FR=0;
        Serialprintln(" FR OFF \r\n");
        delay(50);
      }
				else if(str=='d')
				{
					goto l;
				}
      str=0;
  }
}