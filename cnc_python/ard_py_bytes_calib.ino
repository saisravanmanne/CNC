void setup() {
  Serial.begin(9600);

 pinMode(13,OUTPUT);
 pinMode(12,OUTPUT);
}
unsigned int integerValue=0;  // Max value is 65535
char incomingByte;
 
void loop() {
  integerValue=200;
  digitalWrite(12,LOW);
  if (Serial.available() > 0) {   // something came across serial
    integerValue = 0;         // throw away previous integerValue
    while(1) {            // force into a loop until 'n' is received
      incomingByte = Serial.read();
      if (incomingByte == 'a') break;   // exit the while(1), we're done receiving
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
      integerValue *= 10;  // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      integerValue = ((incomingByte - 48) + integerValue);
      
    }
    Serial.println(integerValue);   // Do something with the value
  }
  
  delay(integerValue);
  digitalWrite(13,LOW);
  delay(integerValue);
  digitalWrite(13,HIGH);
  
}
