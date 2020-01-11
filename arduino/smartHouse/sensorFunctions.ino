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

byte SETTINGS_HORIZONTAL_LINE_COL    =   7;//------------------
// buttonOK
void clickOk()
{
    // якщо початковий, "домашній" режим, то переходимо до налаштувань
    if (gMode == MODE_HOME) 
    {
      gMode = MODE_SETTINGS;
      loadSettingsForm();
      loadSettingsMenu(); 
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
          //gSettingsPointerCol = SETTINGS_ADJUST_SENSOR_COL;
          gSettingsPointerCol = 2;//-----------------
          gMode = MODE_SETTINGS_ADJUST_DATE;

          SETTINGS_HORIZONTAL_LINE_COL = 2;//----------------
          adjustRTCTime();
          loadSettingsMenu(); 
          //adjustRTCTime();
          SETTINGS_HORIZONTAL_LINE_COL = 7;//---------------
        }
        break;

        // налаштування сенсорів (BME)
        case MODE_SETTINGS_ADJUST_SENS_ROW : 
        {
          gSettingsPointerCol = SETTINGS_ADJUST_SENSOR_COL;
          gMode = MODE_SETTINGS_ADJUST_SENS;
          loadSettingsMenu();  
        }
        break;

        // вихід з меню налаштувань
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
  
  clearAdjustMenu();//-----------
  
  loadNames();
  loadSettingsMenu();
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
  if (gMode == MODE_SETTINGS)
  {
    #define EMPTY_BAR 32
   
    lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
    lcd.write(EMPTY_BAR);
    
    if (gSettingsPointerRow == EXIT_SETTING_MODE_ROW)
    {
      gSettingsPointerRow = MODE_SETTINGS_ADJUST_DATE_ROW;
    }
    else
    {
      gSettingsPointerRow++;
    }
    loadSettingsMenu();
  }
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
  if (gMode == MODE_SETTINGS)
  {
    #define EMPTY_BAR 32
   
    lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
    lcd.write(EMPTY_BAR);
    
    if (gSettingsPointerRow == MODE_SETTINGS_ADJUST_DATE_ROW)
    {
      gSettingsPointerRow = EXIT_SETTING_MODE_ROW;
    }
    else
    {
      gSettingsPointerRow--;
    }
    loadSettingsMenu();
  }
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
