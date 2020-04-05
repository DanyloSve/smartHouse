const String wifiName = "Moto";
const String wifiPass  = "ursaursa";

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(5000);

  String response = "";
  bool exit{0};

  // flush
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
  
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
  Serial.print("Hello program final version before insertion v2");
  mySerial.print("Hello program final version before insertion v2");
  delay(1000);
}

// для видалення /r символу
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
