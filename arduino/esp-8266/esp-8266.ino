#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// налаштування сервера
IPAddress server_addr(45,87,0,162);        
char user[] = "station";              
char password[] = "@@@gENNADIymELNYk+lINUx==4eVEr2020";

WiFiClient client;                 
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

// $ - success
// # - unsuccess

// для дебагу: не забути забрати /r/n у кінці рядка
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  #define loadingTimeMs 10000
  #define  waitTimeMs 1000
  delay(loadingTimeMs);
  
  Serial.println(); 
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
          Serial.write("ready");
          count = 0;
      }
      count++;
    }  
    String wifiPass = Serial.readString(); 
    
   while(Serial.available() == 0)
   {
      
   } 
   String wifiName = Serial.readString();  

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
      Serial.write("$");
      
      break;
    }
  }
 conn.connect(server_addr, 3306, user, password);
  cursor = new MySQL_Cursor(&conn);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  while(Serial.available() == 0)
  {
    
  }
  String incommingStr = Serial.readString();
  char buff[incommingStr.length() + 1];
  incommingStr.toCharArray(buff, incommingStr.length() + 1);
  char query[85 + incommingStr.length() + 1];
  sprintf (query, "INSERT INTO smartHouse.tblCollectedData(placeId,time,tempr,hum,press,alt)VALUES(%s)", buff);
  cursor->execute(query);
}
