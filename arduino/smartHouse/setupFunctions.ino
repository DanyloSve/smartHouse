void setupSerial()
{
  lcd.setCursor(0,0); 
  lcd.print(F("WIFI "));
  lcd.print(F(wifiName));
  
  mySerial.begin(115200);
  delay(5000);

  String response = "";
  bool exit{0};
  
  while(true)
  {
    while(mySerial.available() == 0)
    {
           
    }

    response = mySerial.readString();
    removeR(response);
         
    if(response.equals("ready"))
    {
      break;
    }
  }

  while(true)
  {
      
      mySerial.print(wifiPass);

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
      delay(2000);
     
  } 
  delay(2000); 
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

void setupBME()
{  
  delay(5000);
  lcd.setCursor(0,1); 
  lcd.print(F("BME280....... "));
  delay(50);
  
  if (bme.begin(&Wire)) 
  {
    lcd.print(F("OK"));
  }
  else 
  {
    lcd.print(F("ERROR"));
  }
  
  bme.begin(&Wire);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF   );
   delay(50);
}

void setupRTC()
{
  lcd.setCursor(0, 2); 
  lcd.print(F("DS3231 RTC... "));
  delay(50);
  
  if (rtc.begin()) 
  {
    lcd.print(F("OK"));
  }
  else 
  {
    lcd.print(F("ERROR"));//  // put your setup code here, to run once:
  }

  if (rtc.lostPower() || RESET_CLOCK)
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }
  delay(3000);
}


void setupLCD()
{
  // Initialise the LCD: turn on backlight and ensure cursor top left
  lcd.init();
  lcd.backlight();
}

void setupMsTimer()
{
  MsTimer2::set(ONE_SECOND_MILLI_SEC, toTimer); 
  MsTimer2::start();
}

void setupOneButton()
{
 
  buttOk.attachClick(clickOk);
  buttOk.attachLongPressStart(longPressStartOk);


  buttInc.attachClick(clickInc);
  buttInc.attachLongPressStart(longPressStartIncOrDec);

  buttDec.attachClick(clickDec); 
  buttDec.attachLongPressStart(longPressStartIncOrDec); 
}
