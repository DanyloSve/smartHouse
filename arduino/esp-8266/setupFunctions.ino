void connectToWifi()
{
  Serial.begin(115200);
  #define loadingTimeMs 10000
  #define  waitTimeMs 1000
  delay(loadingTimeMs);
  // flush
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
      
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
    removeR(wifiPass) ;
    
   while(Serial.available() == 0)
   {
      
   } 
   String wifiName = Serial.readString();
   removeR(wifiName);  

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

void connectToMySql()
{
   conn.connect(server_addr, 3306, user, password);
   cursor = new MySQL_Cursor(&conn);
}
