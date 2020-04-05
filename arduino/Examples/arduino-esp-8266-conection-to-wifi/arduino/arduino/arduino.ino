const String wifiName{"Elenika"};
const String wifiPass{"ursaursa"};

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(57600);
  mySerial.begin(57600);
  delay(5000);

  String response = "";
  bool exit{0};

  serialFlush();
  while(true)
  {
    //0000000000000000000000000000000
    Serial.println("I am waiting");
    while(mySerial.available() == 0)
    {
           
    }

    response = mySerial.readString();
    
    removeR(response);
        
    if(response.equals("ready"))
    {
      // 00000000000000000
      Serial.println("Get ready signal");
      break;
    }
  }

  while(true)
  {
      //000000000000000000
      delay(2000);
      mySerial.println(wifiPass);

      delay(2000);
      mySerial.print(wifiName); 

      while(mySerial.available() == 0)
      {
           
      }
      
      response = mySerial.readString();
      serialFlush();
      removeR(response);
      
      
      if (response.equals("$"))
      {
       break;
      }
     
  } 
  delay(2000); 
  Serial.println("Exit from setup");
}

void loop() 
{
  // put your main code here, to run repeatedly:
    while(mySerial.available() == 0)
    {
         
    }
   String response = mySerial.readString();
   Serial.println(response);
}

void removeR(String &s)
{
  for(int i{s.length() - 2}; s[i] !=  '\0'; i++)
  {
    if (s[i] == '\r')
    {
      s.remove(i);
      break;
    }
  }
}
