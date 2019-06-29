#include <Servo.h>
int x=9;
int sra=0;
int xDir=8;
int y=7;
int k=0;
int yDir=6;
Servo zAxis; 
#define up 180
#define down 175
void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(x,OUTPUT);
pinMode(xDir,OUTPUT);
pinMode(y,OUTPUT);
pinMode(yDir,OUTPUT);
digitalWrite(x,LOW);
digitalWrite(y,LOW);
digitalWrite(xDir,LOW);
digitalWrite(yDir,LOW);
zAxis.attach(10);   //servo
}

void loop() 
{
 while(Serial.available())
 {
  int val = Serial.parseInt();
  sra=0;
  k=1;
  
 while(val==13)
  {
Serial.println(val);
   while(Serial.available()&&(k==1))
   {
  val = Serial.parseInt();
  Serial.println(val);
  sra=sra+1;
   if(sra==10)
   {
    k=0;
   }
   if ((val>=1000 && val<4000) || (val<=-1000&&val>=-4000))
    {
      if (val>=1000 && val<4000)
      {
        val=val-1000;
        xAxis(val,1);  // for positive direction of xAxis
        //Serial.println("X-axis");
      }
      else if (val<=-1000&&val>-4000)
      {
        val=val+1000;
        xAxis(abs(val),-1); //for negative direction of xAxis
        //Serial.println("X-axis");
      }
    }
    else if (val>=4000 || val<=-4000)
    {
      if (val>=4000)
      {
        val=val-4000;
        yAxis(val,1); // for positive direction of y Axis
        //Serial.println("Y-axis");
      }
      else if (val<=-4000)
      {
        val=val+4000;
        yAxis(abs(val),-1); // for negitive direction of y Axis
        //Serial.println("Y-axis");
      }
    }
     else if (val==1)
      {
        zAxis.write(up);
        //Serial.println("Z-axis");
      }
     else if (val==0)
      {
        zAxis.write(down);
       // Serial.println("Z-axis");
      }//
  }
  }
  }
 //Serial.print("1\n");
  // put your main code here, to run repeatedly:
 }
int xAxis(int xSteps,int dirOfX)
 {
  if(dirOfX==1)
  {
    digitalWrite(xDir,HIGH);
  }
  else if (dirOfX==-1)
  {
    digitalWrite(xDir,LOW);
  }
 // Serial.println(dirOfX);
  while(xSteps!=0)
  {
  digitalWrite(x,HIGH);
  delay(1);
  digitalWrite(x,LOW);
  delay(1);
  xSteps=xSteps-1;
 //Serial.print("1\n");
 // Serial.println(xSteps);
  }
 }
 int yAxis(int ySteps,int dirOfY)
 {
  if(dirOfY==1)
  {
    digitalWrite(yDir,HIGH);
  }
  else if (dirOfY==-1)
  {
    digitalWrite(yDir,LOW);
  }
  //Serial.println(dirOfY);
  while(ySteps!=0)
  {
  digitalWrite(y,HIGH);
  delay(1);
  digitalWrite(y,LOW);
  delay(1);
  ySteps=ySteps-1;
  //Serial.print("1\n");
 // Serial.println(ySteps);
  }

 }
 


