void readBME()
{
  bme.takeForcedMeasurement();
  gTemp = bme.readTemperature();
  gHum = bme.readHumidity();
  gPres = (float)bme.readPressure() * 0.00750062;
  gAlt = bme.readAltitude(SEALEVELPRESSURE_HPA);  
}

void readRTC()
{   
  while (true)
  {
    DateTime now = rtc.now();         
    gSecond = now.second();
    gMinute = now.minute();
    gHour = now.hour();
    gDay = now.day();
    gDayName = now.dayOfTheWeek();
    gMounth = now.month(); 

    if (gSecond >= 0 && gSecond <= 5)
    {
      break;
    }
  }
}

// buttonOK
void clickOk()
{
  isPressedButtOk = 1;
}

void doubleclickOk()
{
  isDoublePressOk = 1;
}

void longPressStartOk()
{
  isLongPressStartOk = 1;
  isLongPressStopOk = 0;
}

void longPressStopOk()
{
  isLongPressStartOk = 0;
  isLongPressStopOk = 1;
}

// buttonInc
void clickInc()
{
  isPressedButtInc = 1;
}

void doubleclickInc()
{
  isDoublePressInc = 1;
}

void longPressStartInc()
{
  isLongPressStartInc = 1;
  isLongPressStopInc = 0;
}

void longPressStopInc()
{
  isLongPressStartInc = 0;
  isLongPressStopInc = 1;
}


// buttonDec
void clickDec()
{
  isPressedButtDec = 1;
}

void doubleclickDec()
{
  isDoublePressInc = 1;
}

void longPressStartDec()
{
  isLongPressStartInc = 1;
  isLongPressStopInc = 0;
}

void longPressStopDec()
{
  isLongPressStartOk = 0;
  isLongPressStopOk = 1;
}
