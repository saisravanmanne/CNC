#include <Servo.h>
int x = 9;
int preval = 13;
int sra = 0;
int xDir = 13;
int y = 6;
int yDir = 5;
int k = 0;
Servo zAxis;
#define up 110
#define down 94
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(x, OUTPUT);
  pinMode(xDir, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(yDir, OUTPUT);
  digitalWrite(x, LOW);
  digitalWrite(y, LOW);
  digitalWrite(xDir, LOW);
  digitalWrite(yDir, LOW);
  zAxis.attach(10);   //servo
   zAxis.write(up);
}

void loop()
{

  while (Serial.available()>0)
  {
    int val = Serial.parseInt();

    if (preval == val)
    {
      k = 0;
    }
    if ((preval != val)||(val==3)||(val==9))
    {
      k = 1;
      sra = sra + 1;
      delay(10);
      Serial.println(val);
    }
    //Serial.begin(9600);
    if (sra == 100)
    {
      //delay(400);
      sra = 0;
    }
    //Serial.println(val);
    preval = val;
    if ((val >= 1000 && val < 4000) && k)
    {
      
        val = val - 1000;
        xAxis(val, 1); // for positive direction of xAxis
        //Serial.println("X-axis");
      }
     if ((val >= 4000 && val < 7000)&& k)
      {
        val = val - 4000;
        xAxis(abs(val), -1); //for negative direction of xAxis
        //Serial.println("X-axis");
      }
    
    if ((val >= 7000 &&  val < 10000) && k)
      {
        val = val - 7000;
        yAxis(val, 1); // for positive direction of y Axis
        //Serial.println("Y-axis");
      }
    if ((val >= 10000 && val < 13000) && k)
      {
        val = val - 10000;
        yAxis(abs(val), -1); // for negitive direction of y Axis
        //Serial.println("Y-axis");
      }
    
    else if ((val == 9) && k)
    {
      zAxis.write(up);
      delay(15);
      //Serial.println("Z-axis");
    }
    else if ((val == 3) && k)
    {
      zAxis.write(down);
      delay(15);
      //Serial.println("Z-axis");
    }


  }
  //Serial.print("1\n");
  // put your main code here, to run repeatedly:
}
int xAxis(int xSteps, int dirOfX)
{
  if (dirOfX == 1)
  {
    digitalWrite(xDir, HIGH);
  }
  else if (dirOfX == -1)
  {
    digitalWrite(xDir, LOW);
  }
  // Serial.println(dirOfX);
  while (xSteps != 0)
  {
    digitalWrite(x, HIGH);
    delay(1);
    digitalWrite(x, LOW);
    delay(1);
    xSteps = xSteps - 1;
    //Serial.print("xais\n");
    // Serial.println(xSteps);
  }
  //Serial.print("xais\n");
}
int yAxis(int ySteps, int dirOfY)
{
  if (dirOfY == 1)
  {
    digitalWrite(yDir, HIGH);
  }
  else if (dirOfY == -1)
  {
    digitalWrite(yDir, LOW);
  }
  //Serial.println(dirOfY);
  while (ySteps != 0)
  {
    digitalWrite(y, HIGH);
    delay(1);
    digitalWrite(y, LOW);
    delay(1);
    ySteps = ySteps - 1;
    //Serial.print("yais\n");
    // Serial.println(ySteps);
  }
  //Serial.print("yais\n");
}


