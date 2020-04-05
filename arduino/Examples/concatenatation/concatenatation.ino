#include <stdio.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  char buff[110];
  char hum[] = "smartHouse";
  char temp[] = "testTable";
  char pres[] = "pressure";
  char alt[] = "height"; 
  sprintf (buff, "INSERT INTO smartHouse.testTable(text) VALUES ('%s, %s, %s, %s')", hum, temp, pres, alt);
  Serial.write(buff);

}

void loop() {
  // put your main code here, to run repeatedly:

}
