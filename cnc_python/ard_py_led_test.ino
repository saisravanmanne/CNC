
int t = 0;
int rece=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(t);
  digitalWrite(13, LOW);
  delay(t);
  //Serial.println("hello sravan");
if(Serial.available()>0)
{
t=t+500;
}
/*if(rece>0)
{
t=rece;
}*/
}


