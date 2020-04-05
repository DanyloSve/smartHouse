/*
  MySQL Connector/Arduino Example : connect by wifi
  This example demonstrates how to connect to a MySQL server from an
  Arduino using an Arduino-compatible Wifi shield. Note that "compatible"
  means it must conform to the Ethernet class library or be a derivative
  thereof. See the documentation located in the /docs folder for more
  details.
  INSTRUCTIONS FOR USE
  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Change the SSID and pass to match your WiFi network
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe
  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.
  Created by: Dr. Charles A. Bell
*/
#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(45,87,0,162);  // IP of the MySQL *server* here
char user[] = "meteostation";              // MySQL user login username
char password[] = "@@@gENNADIymELNYk+lINUx==4eVEr2020";        // MySQL user login password

// Sample query
char INSERT_SQL[] = "INSERT INTO smartHouse.testTable(text) VALUES ('Hello from Arduino');";

// WiFi card example
char ssid[] = "Elenika";         // your SSID
char pass[] = "ursaursa";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{  
  while(Serial.available() == 0)
  {
    
  }
  String incommingStr = Serial.readString();
  char buff[incommingStr.length() + 1];
  incommingStr.toCharArray(buff, incommingStr.length() + 1);
  char query[100];
  sprintf (query, "INSERT INTO smartHouse.testTable(text) VALUES ('%s')",buff);
  
  cursor->execute(query);
  Serial.println(query);
}
