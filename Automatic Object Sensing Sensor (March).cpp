#include<Servo.h>
Servo s;
int pir=4;
void setup()
{
  pinMode(pir,INPUT);
  s.attach(3);
  Serial.begin(9600);
}
void loop()
{
  int val=digitalRead(pir);
  Serial.println(val);
  if(val==HIGH)
  {
    s.write(180);
  }
    else
  {
    s.write(-200);
  }
  delay(100);
}
