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
    DateTime now = rtc.now();         
    gSecond = now.second();
    gMinute = now.minute();
    gHour = now.hour();
    gDay = now.day();
    gDayName = now.dayOfTheWeek();
    gMonth = now.month();
    gYear = now.year(); 
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
          adjustSensor();  
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
      adjustSensor();
    }
    
}

int getMultiplier() // отримання множника для редагування одиниць, десятків, сотнів та тисячнів числа 1 10 100 1000
{
  switch(gSettingsRank)
    {
      case 0: return 1;
      case 1: return 10;
      case 2: return 100;
      case 3: return 1000;
    }
}

int getDigit(const int &number, const byte &gSettingsRank) //------------->
{
  switch(gSettingsRank)
  {
    case 0: return number % 10;
    case 1: return ((number % 100) / 10);
    case 2: return ((number % 1000) / 100);
    case 3: return number / 1000;
    }  
}

void longPressStartOk()
{ 
  if (gMode == MODE_SETTINGS_ADJUST_DATE || gMode == MODE_SETTINGS_ADJUST_SENS)
  {    
    gSettingsPointerCol = SETTINGS_CHOISE_COL;
    gSettingsConfirmAdjustment = 0;
    gMode = MODE_SETTINGS;
      
    clearAdjustMenu();
      
    loadSettingsMenu();
    
  }
  else if (gMode == MODE_SETTINGS)
  {    
    gMode = MODE_HOME;
    loadHomeForm();
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
  else if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    if (getDigit(*gpSettingsAdjustValue, gSettingsRank) < MAX_NUMBER)//==============
    {
      *gpSettingsAdjustValue += 1 * getMultiplier();
      adjustRTCtime();
    }
  }
  else if (gMode == MODE_SETTINGS_ADJUST_SENS)
  {
    if (getDigit(*gpSettingsAdjustValue, gSettingsRank) < MAX_NUMBER)//-----------------------
    {
      *gpSettingsAdjustValue += 1 * getMultiplier(); 
      adjustSensor();
    }
  }
}


void longPressStartIncOrDec() // змінює на попередні значення години, хвилин і тд
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
    switch(gSettingsConfirmAdjustment)
    {
      case 0:
      case 1:
      case 2:
      case 3:
      {
        gSettingsAdjustingSensorReadTimeDomainSec = gSensorReadTimeDomainSec; 
      }
      break;
      
      case 4:
      case 5:
      case 6:
      {
        gSettingsAdjustingNumberOfTimeDomains     = gNumberOfTimeDomains; 
      }
      break;
    }
    adjustSensor();
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
  
  else if (gMode == MODE_SETTINGS_ADJUST_DATE)
  {
    if (getDigit(*gpSettingsAdjustValue, gSettingsRank) > MIN_NUMBER)
    {
      *gpSettingsAdjustValue -= 1 * getMultiplier(); 
      adjustRTCtime();
    }
  }
  else if (gMode == MODE_SETTINGS_ADJUST_SENS)
  {
    if (getDigit(*gpSettingsAdjustValue, gSettingsRank) > MIN_NUMBER)
    {
      *gpSettingsAdjustValue -= 1 * getMultiplier();
      adjustSensor(); 
    }
  }
}
