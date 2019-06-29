#include <Servo.h>
Servo zAxis;
void setup() {
   Serial.begin(9600);
  // put your setup code here, to run once:
 zAxis.attach(10);
 zAxis.write(110);
}

void loop() {
while (Serial.available()>0)
{
 
  int val = Serial.parseInt();
  if (val>0)
  {
zAxis.write(val);
  }
delay(15);
 Serial.println(val);
}


  

}
