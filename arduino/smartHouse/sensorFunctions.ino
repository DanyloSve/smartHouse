/*
 * void doubleclickOk() - при виході зберігає зміни, переходить до МЕНЮ ВИБОРУ
 * void longPressStartOk() - при виході зміни НЕ зберігає, перехадить на ДОМАШНІЙ РЕЖИМ
 */
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
    gMonth = now.month();
    gYear = now.year(); 

    if (gSecond >= 0 && gSecond <= 5)
    {
      break;
    }
  }
}

// buttonOK
void clickOk()
{   
    // заватнтаження користувацьких сегментів для меню
    loadSegments();
    // якщо початковий, "домашній" режим, то переходимо до налаштувань
    if (gMode == MODE_HOME) 
    {
      gMode = MODE_SETTINGS;
      loadSettingsForm();
      loadSettingsMenu(); 
      return; 
    }

    // режим налаштування
    else if (gMode == MODE_SETTINGS) 
    {
      // відслідковування 'вказівника' (повзунка)
      switch(gSettingsPointerRow)
      {
        // налаштування дати
        case MODE_SETTINGS_ADJUST_DATE_ROW : 
        {
          gSettingsPointerCol = SETTINGS_ADJUSTMENT_COL;
          gMode = MODE_SETTINGS_ADJUST_DATE;

          adjustRTCtimeForm(); 
          loadSettingsMenu(); 
          adjustRTCtime();   
    
        }
        break;
        
        // налаштування сенсорів (BME)
        case MODE_SETTINGS_ADJUST_SENS_ROW : 
        {
          gSettingsPointerCol = SETTINGS_ADJUSTMENT_COL;
          gMode = MODE_SETTINGS_ADJUST_SENS;
          adjustSensorForm();
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
    
    // якщо такий режим, то переходимо до наступної цифри, що маємо змінити у даному режимі
    else if (gMode == MODE_SETTINGS_ADJUST_DATE )
    {
      gSettingsConfirmAdjustment++;
      adjustRTCtime();  
    }

    // якщо такий режим, то переходимо до наступної цифри, що маємо змінити у даному режимі
    else if (gMode == MODE_SETTINGS_ADJUST_SENS)
    {
      gSettingsConfirmAdjustment++;
      adjustSensorForm();
    }
    
}

void doubleclickOk()
{
  // перехід до меню вибору налаштувань(Date, Sensor, EXIT)

  if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    gSettingsConfirmAdjustment = 12;
    adjustRTCtime();
  }
  else if (gMode == MODE_SETTINGS_ADJUST_SENS)
  {
      
  }

  
  gSettingsPointerCol = SETTINGS_CHOISE_COL;
  gSettingsConfirmAdjustment = 0;
  gMode = MODE_SETTINGS;
  
  clearAdjustMenu();
  
  loadMenuOptions();
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
   // зачищення місця, де був повзунок 
    lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
    lcd.write(EMPTY_BAR);

    // якщо повзунок на найнижчому варіанті вибору, то переводимо на перший
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
  
  if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    
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
   // зачищення місця, де був повзунок 
    lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
    lcd.write(EMPTY_BAR);

    // якщо повзунок на найнижчому варіанті вибору, то переводимо на перший
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
  if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    
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
