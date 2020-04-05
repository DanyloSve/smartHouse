//const String wifiName{"Elenika"};
//const String wifiPass{"ursaursa"};

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() 
{
  Serial.begin(57600);
  mySerial.begin(57600);
  delay(5000);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  String incommingStr = "";
  bool stringReady{0};

  while(mySerial.available() == 0)
  {
  }
  incommingStr = mySerial.readString();

//  while(Serial.available() == 0)
//  {
//  }
//  incommingStr = Serial.readString();
  removeR(incommingStr);

  if (incommingStr.equals("hello"))
  {
    Serial.println("Ok");
  }
  else
  {
    Serial.println("No information");
  }
  serialFlush();
}

void serialFlush()
{
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
} 

void removeR(String &s)
{
  for(int i{0}; s[i] !=  '\0'; i++)
  {
    if (s[i] == '\r')
    {
      s.remove(i);
      break;
    }
  }
}
