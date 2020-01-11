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
    // якщо початковий, "домашній" режим, то переходимо до налаштувань
    if (gMode == MODE_HOME) 
    {
      gMode = MODE_SETTINGS;
      loadSettingsForm();
      settingsMenu(); 
      return; 
    }

    // режим налаштування
    if (gMode == MODE_SETTINGS) 
    {
      switch(gSettingsPointerRow)
      {
        // налаштування дати
        case MODE_SETTINGS_ADJUST_DATE_ROW : 
        {
          gSettingsPointerCol = SETTINGS_ADJUST_SENSOR_COL;
          gMode = MODE_SETTINGS_ADJUST_DATE;
          settingsMenu();  
        }
        break;

        // налаштування сенсорів (BME)
        case MODE_SETTINGS_ADJUST_SENS_ROW : 
        {
          gSettingsPointerCol = SETTINGS_ADJUST_SENSOR_COL;
          gMode = MODE_SETTINGS_ADJUST_SENS;
          settingsMenu();  
        }
        break;

        case EXIT_SETTING_MODE_ROW:
        {
          gMode = MODE_HOME;
          loadHomeForm();
        }
        break;
      } 
    }  
}

void doubleclickOk()
{
  gSettingsPointerCol = SETTINGS_CHOSE_SENSOR_COL;
  gMode = MODE_SETTINGS;
  settingsMenu();
}

void longPressStartOk()
{
  if (gMode != MODE_HOME)
  {
    gMode = MODE_HOME;
    loadHomeForm();
  }
}


// buttonInc
void clickInc()
{
  //isPressedButtInc = 1;
}

void doubleclickInc()
{
//  isDoublePressInc = 1;
}

void longPressStartInc()
{
  //isLongPressStartInc = 1;
  //isLongPressStopInc = 0;
}

void longPressStopInc()
{
//  isLongPressStartInc = 0;
//  isLongPressStopInc = 1;
}


// buttonDec
void clickDec()
{
//  isPressedButtDec = 1;
}

void doubleclickDec()
{
  //isDoublePressInc = 1;
}

void longPressStartDec()
{
  //isLongPressStartInc = 1;
  //isLongPressStopInc = 0;
}

void longPressStopDec()
{
 // isLongPressStartOk = 0;
  //isLongPressStopOk = 1;
}
