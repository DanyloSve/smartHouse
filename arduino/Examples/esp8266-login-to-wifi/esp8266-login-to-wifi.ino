#include <ESP8266WiFi.h>

void setup()
{
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println();

  serialFlush();
  Serial.print("ready");
  serialFlush();

  String wifiName;
  String wifiPass;
  bool exit{1};
  while (exit)
  {
     while(Serial.available() == 0)
     {
     
     }
     
    wifiName = Serial.readString();
    if (wifiName.length() >= 8)
    {
     serialFlush();
     while(Serial.available() == 0)
     {
     
     }
     wifiPass = Serial.readString(); 
     exit = 0;    
    }
    serialFlush();
  }
  Serial.println("Ok");

  // remove /r
  removeR(wifiName);
   removeR(wifiPass);
  
  Serial.println(wifiName);
  Serial.println(wifiPass);

  WiFi.begin(wifiName, wifiPass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
  
void removeR(String &s)
{
  int j{0};
  for(int i{0}; s[i] !=  '\r'; i++)
  {
    j = i;
  }
  s.remove(j + 1);
}

void serialFlush(){
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
}  

void loop() 
{
  // put your main code here, to run repeatedly:

}
