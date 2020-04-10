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

void setup()
{
  connectToWifi();
  connectToMySql();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (conn.connected())
  {
    while(Serial.available() == 0)
    {
      
    }
    String incommingStr = Serial.readString();
    removeR(incommingStr);
    char buff[incommingStr.length() + 1];
    incommingStr.toCharArray(buff, incommingStr.length() + 1);
    char query[85 + incommingStr.length() + 1];
    sprintf (query, "INSERT INTO smartHouse.tblCollectedData(placeId,time,tempr,hum,press,alt)VALUES(%s)", buff);
    cursor->execute(query);
  }
  else
  {
    connectToMySql();
  }
}
