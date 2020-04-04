int b;
float a,y=0;
void setup()
{
pinMode(A0,INPUT); // set pin a0 as input pin
Serial.begin(9600);// begin serial communication between arduino and pc
}
void loop()
{
b=analogRead(A0);// read analog values from pin A0 across capacitor
a=(b* 0.304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
delay(100);
if(y!=a)
{
Serial.print(" analaog input " ) ; // specify name to the corresponding value to be printed
Serial.print(b) ; // print input analog value on serial monitor
Serial.print(" ac voltage ") ; // specify name to the corresponding value to be printed
Serial.print(a/sqrt(2)) ; // prints the ac value on Serial monitor
Serial.println();
y=a;
}
else
delay(100);
}
