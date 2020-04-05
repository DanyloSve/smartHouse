void setup()
{
  // put your setup code here, to run once:
   Serial.begin(115200);
   String responce;
   bool exit{1};
    while (exit)
   {
     while(Serial.available() == 0)
     {
     
     }
     
    responce = Serial.readString();
    if (responce.equals())
    {
     
     exit = 0;    
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
