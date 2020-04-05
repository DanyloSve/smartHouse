void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Start");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  while(Serial.available() == 0)
  {
  }

   String incomming = Serial.readString();
   char array[incomming.length()];
   Serial.println(incomming[i]);
  
}
