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
      adjustRTCtime();  // оновлюємо меню adjustSensorForm
    }

    // якщо такий режим, то переходимо до наступної цифри, що маємо змінити у даному режимі
    else if (gMode == MODE_SETTINGS_ADJUST_SENS)
    {
      gSettingsConfirmAdjustment++;
      adjustSensorForm(); // оновлюємо меню adjustSensorForm
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

  /*
  gSettingsPointerCol = SETTINGS_CHOISE_COL;
  gSettingsConfirmAdjustment = 0;
  gMode = MODE_SETTINGS;
  
  clearAdjustMenu();

  loadSettingsMenu();
  */
}

void longPressStartOk()
{
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
    
  loadSettingsMenu();
}

int getMultiplier() // отримання множника для редагування одиниць, десятків, сотнів та тисячнів числа 1 10 100 1000
{
  switch(gSettingsRank)
    {
      case 0:
      {
        return 1;
      }
      break;

      case 1:
      {
        return 10;
      }
      break;

      case 2:
      {
        return 100;
      }
      break;

      case 3:
      {
        return 1000;
      }
      break;
    }
}

int getDigit(const int number)
{
  if (number >= 1000) // тисячні
  {
    return number / 1000;
  }
  else if (number >= 100) // сотні
  {
    return ((number / 100) % 10);
  }
  else if (number >= 10) // десятки
  {
    return ((number / 10) % 100);
  }
  else // одиниці
  {
    return number % 10;
  }
}

// buttonInc
void clickInc()
{
  #define MAX_NUMBER 9
  
  if (gMode == MODE_SETTINGS)
  {
    #define EMPTY_BAR 32
   // зачищення місця, де був повзунок 
    lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
    lcd.write(EMPTY_BAR);

    // якщо повзунок на найнижчому варіанті вибору, то переводимо на перший
    if (gSettingsPointerRow == MODE_SETTINGS_ADJUST_DATE_ROW)
    {
      gSettingsPointerRow = EXIT_SETTING_MODE_ROW;;
    }
    else
    {
      gSettingsPointerRow--;
    }
    loadSettingsMenu();
  }
  if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    if (getDigit(*gpSettingsAdjustValue) < MAX_NUMBER)//==============
    {
      *gpSettingsAdjustValue += 1 * getMultiplier();
      adjustRTCtime();
    }
    
  }
  else if (gMode == MODE_SETTINGS_ADJUST_SENS)
  {
    if (getDigit(*gpSettingsAdjustValue) < MAX_NUMBER)//-----------------------
    {
      *gpSettingsAdjustValue += 1 * getMultiplier(); 
      adjustSensorForm();
    }
  }
}


void longPressStartIncOrDec() // повертає попереднє значення години, хвилин і тд
{
  if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    switch (gSettingsConfirmAdjustment)
    {
      // час hh:mm //////////////////////////////////////////////////////////////////
      // години
      case 0:
      case 1:
      {    
        gAdjustingHour = gHour;
      }
      break;
      
      // хвилини 
      case 2:  
      case 3:
      {
        gAdjustingMinute = gMinute;
      }
      break;
  
      // дата dd/mm/yyyy ////////////////////////////////////////////////////
      
      // день
      case 4:
      case 5:
      {
        gAdjustingDay = gDay;
      }
      break;
  
      // місяць
      case 6:    
      case 7:
      {
        gAdjustingMonth = gMonth;
      }
      break;
  
      // рік
      case 8:
      case 9:
      case 10:  
      case 11:
      {
        gAdjustingYear = gYear;
      }
      break;
    }
    adjustRTCtime();
  }
  else if (gMode == MODE_SETTINGS_ADJUST_SENS)
  {
  
  }
}

// buttonDec
void clickDec()
{
  #define MIN_NUMBER 0
  
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
    if (getDigit(*gpSettingsAdjustValue) > MIN_NUMBER)
    {
      *gpSettingsAdjustValue -= 1 * getMultiplier(); 
      adjustRTCtime();
    }
  }
  else if (getDigit(*gpSettingsAdjustValue) > MIN_NUMBER)
  {
    if (*gpSettingsAdjustValue > MIN_NUMBER * getMultiplier())
    {
      *gpSettingsAdjustValue -= 1 * getMultiplier();
      adjustSensorForm(); 
    }
  }
}
