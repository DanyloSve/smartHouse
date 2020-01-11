/* 
 *  void setupSerial()
 *  void setupBME()
 *  void setupRTC()
 *  void setupLCD()
 *  
 */

void setupSerial()
{
    Serial.begin(9600);
    delay(3000);
}

void setupBME()
{  
  delay(5000);
  Serial.println();
  lcd.setCursor(0,0); 
  Serial.print(F("BME280....... "));
  lcd.print(F("BME280....... "));
  delay(50);
  
  if (bme.begin(&Wire)) 
  {
    Serial.println(F("OK"));
    lcd.print(F("OK"));
  }
  else 
  {
    Serial.println(F("ERROR"));
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
  lcd.setCursor(0, 1); 
  Serial.print(F("DS3231 RTC... ")); // для зменшення RAM пам'яті
  lcd.print(F("DS3231 RTC... "));
  delay(50);
  
  if (rtc.begin()) 
  {
    Serial.println(F("OK"));
    lcd.print(F("OK"));
  }
  else 
  {
    Serial.println(F("ERROR"));
    lcd.print(F("ERROR"));
  }

  if (rtc.lostPower() || RESET_CLOCK)
  {
    Serial.println("RTC lost power, lets set the time!");
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
  MsTimer2::set(ONE_SECOND, toTimer); // Здесь задаем период 1 секунда
  MsTimer2::start();
}

void setupOneButton()
{
 
  buttOk.attachClick(clickOk);
  buttOk.attachDoubleClick(doubleclickOk);
  buttOk.attachLongPressStart(longPressStartOk);

  buttInc.attachClick(clickInc);
  /*
  buttInc.attachDoubleClick(doubleclickInc);
  buttInc.attachLongPressStart(longPressStartInc);
  buttInc.attachLongPressStop(longPressStopInc);
  */

  buttDec.attachClick(clickDec);
  /*
  buttDec.attachDoubleClick(doubleclickDec);
  buttDec.attachLongPressStart(longPressStartDec);
  buttDec.attachLongPressStop(longPressStopDec);
  */
  
  
}
