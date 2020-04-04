// Program to make a clock with time setting functionality.

#include<reg51.h>
 sbit dig_ctrl_4=P1^0;        //Declare the control pins of the seven segment
 sbit dig_ctrl_3=P1^1;
 sbit dig_ctrl_2=P1^2;
 sbit dig_ctrl_1=P1^3;
 sbit reset=P1^4;        // Reset pin to reset the clock.
 sbit start=P1^7;        //Start pin to start the clock after the time is set.
 sbit incr=P1^6;        //Increment pin to increase the digits during time setting.
 sbit set=P1^5;        // Set pin to set the time.
 int sel_seg_to_incr=0;
 int ret_seg_to_incre=0;
 int recnt_incr_seg;
 unsigned char dig_disp=0;
 int min2=0;
 int min1=0;
 int sec2=0;
 int sec1=0;
 char dig_val[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};        // to store values corresponding to digits 0 to 9

void delay(int a)        // Function to provide a time delay of approx. 1 second using Timer1.
{
    int i;
    for(i=0;i<a;i++)
    {
        TL1=0xFD;
         TH1=0x4B;
         TR1=1;
         while(TF1==0);
         TR1=0;
         TF1=0;
    }                                   
 }

int setfn()        // Function to select minute and seconds digit to be set.
{                     
    while(set==0)
    {
        switch(recnt_incr_seg)
        {
            case 1:
            if(set==0)        //select the min2 digit
            {
                dig_ctrl_4=1;
                dig_ctrl_3=0;
                dig_ctrl_2=0;
                dig_ctrl_1=0;
                recnt_incr_seg=1;
                ret_seg_to_incre=1;
                P2=dig_val[min2];
                delay(20);
            }

            case 2:
            if(set==0)        // Select the min1 digit
            {
                dig_ctrl_4=0;
                dig_ctrl_3=1;
                dig_ctrl_2=0;
                dig_ctrl_1=0;
                recnt_incr_seg=2;
                ret_seg_to_incre=2;
                P2=dig_val[min1];
                delay(20);
            }
       
            case 3:
            if(set==0)        //Select the sec 2 digit
            {
                dig_ctrl_4=0;
                dig_ctrl_3=0;
                dig_ctrl_2=1;
                dig_ctrl_1=0;
                recnt_incr_seg=3;
                ret_seg_to_incre=3;
                P2=dig_val[sec2];
                delay(20);
            }
       
            case 4:
            if(set==0)        //Select the sec1 digit
            {
                recnt_incr_seg=1;
                dig_ctrl_4=0;
                dig_ctrl_3=0;
                dig_ctrl_2=0;
                dig_ctrl_1=1;
                ret_seg_to_incre=4;
                P2=dig_val[sec1];
                delay(20);
                recnt_incr_seg=1;
            }
        }
    }
    return(ret_seg_to_incre);
}

void increase(int a)        //Function to set the minute or seconds digit
{
    while(incr==0)
    {
        switch(a)
        {
                case 1:        // To set the min2 digit.
                P2=dig_val[min2];        //Display the value of min2
                delay(15);
                min2++;
                if(min2==6)
                min2=0;
                P2=dig_val[min2];
                delay(5);
                break;
               
                case 2:        //To set the min1 digit.
                P2=dig_val[min1];
                delay(15);
                min1++;
                if(min1==10)
                min1=0;
                P2=dig_val[min1];
                delay(5);
                break;
       
                case 3:        // To set the sec2 digit.
                P2=dig_val[sec2];
                delay(15);
                sec2++;
                if(sec2==6)
                sec2=0;
                P2=dig_val[sec2];
                delay(5);
                break;
       
                case 4:        //To set the sec1 digit.
                P2=dig_val[sec1];
                delay(15);
                sec1++;
                if(sec1==10)
                sec1=0;
                P2=dig_val[sec1];
                delay(5);
                break;
        }
    }
}

void resetfn()        // This function brings the clock to reset or set mode.
{
    IE=0x80;        //Disable timer0 interrupt to stop the display of the clock
    sel_seg_to_incr=1;
    recnt_incr_seg=1;
    dig_ctrl_4=1;
    dig_ctrl_3=0;
    dig_ctrl_2=0;
    dig_ctrl_1=0;
    P2=dig_val[min2];
    delay(5);
    while(1)
    {             
        if(start==0)        //check if start pin is pressed
        {
             TMOD=0x11;        //reset the timer0
            TL0=0xf6;
            TH0=0xFf;
            IE=0x82;        //enabling again the timer0 interrupt to start displaying of the clock
            TR0=1;
            break;        // break loop and return to main program
        }
       
        if(set==0)        //if set pin is pressed call set function
        sel_seg_to_incr=setfn();
       
        if(incr==0)        // if incr pin is pressed call incr function
        increase(sel_seg_to_incr);
    }
}
void display() interrupt 1        // function to display the values on seven segmnet. For more details refer seven segment multiplexing.
{
    TL0=0x36;        //reloading timer0
    TH0=0xf6;
       P2=0xFF;
    dig_ctrl_1 = dig_ctrl_3 = dig_ctrl_2 = dig_ctrl_4 = 0;
    dig_disp++;
    dig_disp=dig_disp%4;
    switch(dig_disp)
    {
        case 0:
        P2=dig_val[sec1];
        dig_ctrl_1 = 1;
        break;
   
        case 1:
        P2=    dig_val[sec2];
        dig_ctrl_2 = 1;
        break;
   
        case 2:
        P2=    dig_val[min1];
        dig_ctrl_3 = 1;
        break;
   
        case 3:
        P2=    dig_val[min2];
        dig_ctrl_4 = 1;
        break;
    }
}

void main()        //main function the programs begins from here     
{
    set=1;        //delaring set, reset, start and incr as input pins
    reset=1;
    start=1;
    incr=1;
    TMOD=0x11;        //enabling timer0
    TL0=0xf6;        //loading timer0
    TH0=0xFf;
    IE=0x82;        //initialize timer0 interrupt
    TR0=1;        //triggering timer0
     while(1)        //forward counting of clock
     {
          while(min2<6)
          {                                     
               while(min1<10)
                {   
                 while(sec2<6)
                {
                    while(sec1<10)
                    {
                     if(reset==0)
                     resetfn();
                    delay(20);
                    sec1++;
                    }
                sec1=0;
                sec2++;
                }
            sec1=0;
            sec2=0;
            min1++;
            }
        sec1=0;
        sec2=0;
        min1=0;
        min2++;
        }
    min2=0;
    }
}