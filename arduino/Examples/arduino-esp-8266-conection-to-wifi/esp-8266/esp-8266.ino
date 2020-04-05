#include <ESP8266WiFi.h>

// $ - success
// # - unsuccess

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(57600);
  #define loadingTimeMs 10000
  #define  waitTimeMs 1000
  delay(loadingTimeMs);
  
  Serial.println();     
  while (true)
  {   
    unsigned long count{3000000}; 

    while(Serial.available() == 0)
    {
       if(count == 3000000) // wait eppr 20s - 21s
      {
          Serial.print("ready");
          count = 0;
      }
      count++;
    }  
    String wifiPass = Serial.readString(); 
    removeR(wifiPass);
    
   while(Serial.available() == 0)
   {
      
   } 
   String wifiName = Serial.readString();  
   removeR(wifiName);
   Serial.print(wifiName);
   
   Serial.print(wifiPass);
   WiFi.begin(wifiName, wifiPass);
  
    count = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(waitTimeMs);
      if (count == 15)
      {
        break;
      }
      count++;
    }  
  
    if (count !=  15)
    {
      delay(500);
      Serial.print("$");
      
      break;
    }
  }

   delay(2000);
   Serial.print("Connected, IP address: ");
   
   delay(2000);
   Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

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
