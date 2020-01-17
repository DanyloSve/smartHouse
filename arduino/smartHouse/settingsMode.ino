#define SETTINGS_WORD_COL 0
#define SETTINGS_WORD_ROW 0
#define SETTINGS_WORD_NUMB 8

#define SETTINGS_UPPER_LINE_BEGGINING_COL 8
#define SETTINGS_UPPER_LINE_END_COL       14
#define SETTINGS_UPPER_LINE_ROW           0

#define SETTINGS_HORIZONTAL_LINE_BEGIN_ROW 1
#define SETTINGS_HORIZONTAL_LINE_END_ROW   3
#define SETTINGS_HORIZONTAL_LINE_COL       7


uint8_t LEFT_POINTER[8] = {
                            0b11000,
                            0b11100,  
                            0b11110,  
                            0b11111,  
                            0b11111,  
                            0b11110,  
                            0b11100,  
                            0b11000
                           };

uint8_t HORIZONTAL_LINE[8] = {
                                    0b11000,
                                    0b11000,  
                                    0b11000,  
                                    0b11000,  
                                    0b11000,  
                                    0b11000,  
                                    0b11000,  
                                    0b11000
                                   };

uint8_t HORIZONTAL_CURSOR_LINE[8] = {
                                    0b11111,
                                    0b11111,  
                                    0b11111,  
                                    0b11111,  
                                    0b11111,  
                                    0b11111,  
                                    0b11111,  
                                    0b11111
                                    
                                   };


// reverse numbers
uint8_t ONE[8] = {
                                    0b11011,
                                    0b10011,  
                                    0b11011,  
                                    0b11011,  
                                    0b11011,  
                                    0b11011,  
                                    0b10001,  
                                    0b11111
                                   };
                                   
uint8_t TWO[8] = {
                                    0b10001,
                                    0b01110,  
                                    0b11110,  
                                    0b11101,  
                                    0b11011,  
                                    0b10111,  
                                    0b00000,  
                                    0b11111
                                   };

                                                                      
uint8_t THREE[8] = {
                                    0b00000,
                                    0b11101,  
                                    0b11011,  
                                    0b11101,  
                                    0b11110,  
                                    0b01110,  
                                    0b10001,  
                                    0b11111
                                   };

                                   
uint8_t FOUR[8] = {
                                    0b11101,
                                    0b11001,  
                                    0b10101,  
                                    0b01101,  
                                    0b00000,  
                                    0b11101,  
                                    0b11101,  
                                    0b11111
                                   };

                                   
uint8_t FIVE[8] = {
                                    0b00000,
                                    0b01111,  
                                    0b00011,  
                                    0b11110,  
                                    0b11110,  
                                    0b01110,  
                                    0b10001,  
                                    0b11111
                                   };

uint8_t SIX[8] = {
                                    0b11001,
                                    0b10111,  
                                    0b01111,  
                                    0b00001,  
                                    0b01110,  
                                    0b01110,
                                    0b10001,  
                                    0b11111
                                   };

uint8_t SEVEN[8] = {
                                    0b00000,
                                    0b11110,  
                                    0b11101,  
                                    0b11011,  
                                    0b10111,  
                                    0b10111,  
                                    0b10111,  
                                    0b11111
                                   };

uint8_t EIGHT[8] = {
                                    0b10001,
                                    0b01110,  
                                    0b01110,  
                                    0b10001,  
                                    0b01110,  
                                    0b01110,  
                                    0b10001,  
                                    0b11111
                                   };

uint8_t NINE[8] = {
                                    0b10001,
                                    0b01110,  
                                    0b01110,  
                                    0b10000,  
                                    0b11110,  
                                    0b11101,  
                                    0b10011,  
                                    0b11111
                                   };
                                   

uint8_t ZERO[8] = {
                                    0b10001,
                                    0b01110,  
                                    0b01100,  
                                    0b01010,  
                                    0b00110,  
                                    0b01110,  
                                    0b10001,  
                                    0b11111
                                   };

uint8_t *gpInvertedNumber = NINE;

void convertToInverseColor(byte number)
{
  switch(number)
  {
    case 0:
    {
      gpInvertedNumber = ZERO;
    }
    break;

    case 1:
    {
      gpInvertedNumber = ONE;
    }
    break;

    case 2:
    {
      gpInvertedNumber = TWO;
    }
    break;

    case 3:
    {
      gpInvertedNumber = THREE;
    } 
    break;

    case 4:
    {
      gpInvertedNumber = FOUR;
    }
    break;

    case 5:
    {
      gpInvertedNumber = FIVE;
    }
    break;

    case 6:
    {
      gpInvertedNumber = SIX;
    }
    break;

    case 7:
    {
      gpInvertedNumber = SEVEN;
    }
    break;

    case 8:
    {
      gpInvertedNumber = EIGHT;
    }
    break;

    case 9:
    {
      gpInvertedNumber = NINE;
    }
    break;

    default: gpInvertedNumber = ZERO;
  }
}

void loadSegments()
{
  lcd.createChar(0, LEFT_POINTER);
  lcd.createChar(1, HORIZONTAL_LINE);
  lcd.createChar(2, HORIZONTAL_CURSOR_LINE);
  lcd.createChar(3, gpInvertedNumber);
  
}                                   

void loadSettingsForm()
{
  //lcd.noCursor();   
  loadSegments();
  lcd.clear();
  
  gSettingsPointerRow = 1;
  gSettingsPointerCol = 0;
  gSettingsConfirmAdjustment = 0;                                   
  
  lcd.setCursor(0,0);
  lcd.print(F("SETTINGS"));
  
  for (byte i = SETTINGS_UPPER_LINE_BEGGINING_COL; i <= SETTINGS_UPPER_LINE_END_COL; i++)
  {
    lcd.setCursor(i, SETTINGS_UPPER_LINE_ROW);
    lcd.print(F("_"));
  }  
  backupTimers();
  backupMinute();
  backupHour();

  gAdjustingHour   = gHour;
  gAdjustingMinute = gMinute;
  gAdjustingDay    = gDay;
  gAdjustingMonth  = gMonth;
  gAdjustingYear   = gYear;
  
  lcd.setCursor(1, 1);
  lcd.print(F("Date"));
  lcd.setCursor(1, 2);
  lcd.print(F("Sensors"));
  lcd.setCursor(1, 3);
  lcd.print(F("EXIT"));
}

void clearAdjustMenu()
{
  #define EMPTY_BAR 32 
  
  for (byte i = SETTINGS_HORIZONTAL_LINE_COL +  1; i <= 19; i++)
  {
    for (byte j = 1; j <= 3; j++)
    {
      lcd.setCursor(i, j);
      lcd.write(EMPTY_BAR);
    }
  }
}

void adjustRTCtimeForm()
{
  clearAdjustMenu();
  lcd.setCursor(12, 1);

  // годинник
  if (gHour < 10)
  {
    lcd.print(0);
  }

  lcd.print(gHour);
  lcd.print(F(":"));
  
  if (gMinute < 10)
  {
    lcd.print(0);
  }
  lcd.print(gMinute);
  
  lcd.setCursor(9, 2);

  if (gDay < 10)
  {
    lcd.print(0);
  }
  
  lcd.print(gDay);
  lcd.print(F("/"));
  
  if (gMonth < 10)
  {
    lcd.print(0);
  }
  lcd.print(gMonth);
  lcd.print(F("/"));
  lcd.print(gYear);

}

void adjustRTCtime()
{  
  switch (gSettingsConfirmAdjustment)
  {
    // час hh:mm //////////////////////////////////////////////////////////////////
    // години
    case 0:
    {
      // виділення цифри, яку змінюємо   
      // налаштування годин - сотні від год

      //оновлення іншої цифри години
      lcd.setCursor(13, 1);
      lcd.print(gAdjustingHour % 10);
      
      convertToInverseColor(gAdjustingHour / 10); // встановлення вказівника на потрібну цифру
      lcd.createChar(3, gpInvertedNumber);        // занесення в пам'ять
    
      lcd.setCursor(12, 1);                       // виставлення курсору на потрібне місце
      lcd.write(3);                // виведення на екран потрібну цифру

      if (*gpSettingsAdjustValue != gAdjustingHour)
      {
        gpSettingsAdjustValue = &gAdjustingHour;
      }
    }
    break;

    case 1:
    {
      // перероблюємо попередню  цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(12, 1); 
      lcd.print(gAdjustingHour / 10);

      // виділення цифри, яку змінюємо      
      // налаштування годин - десятки від год
      convertToInverseColor(gAdjustingHour % 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(13, 1);
      lcd.write(3);  

      if (*gpSettingsAdjustValue != gAdjustingHour)
      {
        gpSettingsAdjustValue = &gAdjustingHour;
      }
    }
    break;
    
    // хвилини 
    case 2:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(13, 1); 
      lcd.print(gAdjustingHour % 10);

      // оновлення іншої цифри хвилин
      lcd.setCursor(16, 1);
      lcd.print(gAdjustingMinute % 10);
      
      // виділення цифри, яку змінюємо      
      // налаштування хвилин - десятки від хв
      convertToInverseColor(gAdjustingMinute / 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(15, 1);
      lcd.write(3);  
        
      if (*gpSettingsAdjustValue != gAdjustingMinute)
      {
        gpSettingsAdjustValue = &gAdjustingMinute;
      }
    }
    break;

    case 3:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(15, 1); 
      lcd.print(gAdjustingMinute / 10);

      // виділення цифри, яку змінюємо      
      // налаштування хвилин - десятки від хв
      convertToInverseColor(gAdjustingMinute % 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(16, 1);
      lcd.write(3);

      if (*gpSettingsAdjustValue != gAdjustingMinute)
      {
        gpSettingsAdjustValue = &gAdjustingMinute;
      }
    }
    break;

    // дата dd/mm/yyyy ////////////////////////////////////////////////////
    
    // день
    case 4:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(16, 1); 
      lcd.print(gAdjustingMinute % 10);

      // оновлення іншої цифри дня
      lcd.setCursor(10, 2);
      lcd.print(gAdjustingDay % 10);

      // виділення цифри, яку змінюємо      
      // налаштування дня - десятки від дня
      convertToInverseColor(gAdjustingDay / 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(9, 2);
      lcd.write(3);  

      if (*gpSettingsAdjustValue != gAdjustingDay)
      {
        gpSettingsAdjustValue = &gAdjustingDay;
      }
    }
    break;

    case 5:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(9, 2); 
      lcd.print(gAdjustingDay / 10);

      // виділення цифри, яку змінюємо      
      // налаштування дня
      convertToInverseColor(gAdjustingDay % 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(10, 2);
      lcd.write(3);  

      if (*gpSettingsAdjustValue !=gAdjustingDay)
      {
         gpSettingsAdjustValue = &gAdjustingDay;
      }
    }
    break;

    // місяць
    case 6:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(10, 2); 
      lcd.print(gAdjustingDay % 10);

      // оновлення іншої цифри місяця
      lcd.setCursor(13, 2);
      lcd.print(gAdjustingMonth % 10);

      // виділення цифри, яку змінюємо      
      // налаштування годин - десятки від год
      convertToInverseColor(gAdjustingMonth / 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(12, 2);
      lcd.write(3);    

      if (*gpSettingsAdjustValue != gAdjustingMonth)
      {
        gpSettingsAdjustValue = &gAdjustingMonth;
      }
    }
    break;
  
    case 7:
    {
      // перероблюємо попередню цифру на нормальний колір
      // попередня цифра
      lcd.setCursor(12, 2); 
      lcd.print(gAdjustingMonth / 10);

      // виділення цифри, яку змінюємо      
      // налаштування місяця
      convertToInverseColor(gAdjustingMonth % 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(13, 2);
      lcd.write(3); 

      if (*gpSettingsAdjustValue != gAdjustingMonth)
      {
        gpSettingsAdjustValue = &gAdjustingMonth;
      }
    }
    break;

    // рік
    case 8:
    {
      // оновлення інших цифри року
      lcd.setCursor(15, 2);
      lcd.print(gAdjustingYear / 1000);

      lcd.setCursor(16, 2);
      lcd.print((gAdjustingYear / 100) %10);

      lcd.setCursor(17, 2);
      lcd.print((gAdjustingYear / 10) %100);

      lcd.setCursor(18, 2);
      lcd.print(gAdjustingYear % 10);
      
      // перероблюємо попередню місяця
      // попередня цифра
      lcd.setCursor(13, 2); 
      lcd.print(gAdjustingMonth % 10);

      // виділення цифри, яку змінюємо      
      // налаштування годин - десятки від год
      convertToInverseColor(gAdjustingYear / 1000);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(15, 2);
      lcd.write(3);   

      if (*gpSettingsAdjustValue != gAdjustingYear)
      {
        gpSettingsAdjustValue = &gAdjustingYear;
      }
    }
    break;

    case 9:
    {
      // оновлення інших цифри року
      // та перероблення попередньої цифри на нормальний колір
      lcd.setCursor(15, 2);
      lcd.print(gAdjustingYear / 1000);

      lcd.setCursor(16, 2);
      lcd.print((gAdjustingYear / 100) %10);

      lcd.setCursor(17, 2);
      lcd.print((gAdjustingYear / 10) %100);

      lcd.setCursor(18, 2);
      lcd.print(gAdjustingYear % 10);

      // виділення цифри, яку змінюємо      
      // налаштування року
      convertToInverseColor((gAdjustingYear / 100) %10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(16, 2);
      lcd.write(3);      


      if (*gpSettingsAdjustValue != gAdjustingYear)
      {
         gpSettingsAdjustValue = &gAdjustingYear;      
      }
    }
    break;

     case 10:
    {
            // оновлення інших цифри року
      // та перероблення попередньої цифри на нормальний колір
      lcd.setCursor(15, 2);
      lcd.print(gAdjustingYear / 1000);

      lcd.setCursor(16, 2);
      lcd.print((gAdjustingYear / 100) %10);

      lcd.setCursor(17, 2);
      lcd.print((gAdjustingYear / 10) %100);

      lcd.setCursor(18, 2);
      lcd.print(gAdjustingYear % 10);

      // виділення цифри, яку змінюємо      
      // налаштування року
      convertToInverseColor((gAdjustingYear / 10) %100);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(17, 2);
      lcd.write(3);  

      if (*gpSettingsAdjustValue != gAdjustingYear)
      {
        gpSettingsAdjustValue = &gAdjustingYear;
      }
    }
    break;

    case 11:
    {
      // оновлення інших цифри року
      // та перероблення попередньої цифри на нормальний колір
      lcd.setCursor(15, 2);
      lcd.print(gAdjustingYear / 1000);

      lcd.setCursor(16, 2);
      lcd.print((gAdjustingYear / 100) %10);

      lcd.setCursor(17, 2);
      lcd.print((gAdjustingYear / 10) %100);

      lcd.setCursor(18, 2);
      lcd.print(gAdjustingYear % 10);

      // виділення цифри, яку змінюємо      
      // налаштування року
      convertToInverseColor(gAdjustingYear % 10);
      lcd.createChar(3, gpInvertedNumber);
      
      lcd.setCursor(18, 2);
      lcd.write(3);

      if (*gpSettingsAdjustValue != gAdjustingYear)
      {
        gpSettingsAdjustValue = &gAdjustingYear;
      }
    }
    break;

    // встановити та вийти з даного режиму
    case 12:
    {
      // rtc.adjust(DateTime(yyyy, mm, dd, hh, mm, ss = 0));
      rtc.adjust(DateTime(gAdjustingYear, gAdjustingMonth, gAdjustingDay, gAdjustingHour, gAdjustingMinute, 0));    
    }
    break;
  }
}

void adjustSensor()
{
  
}

void adjustSensorForm()
{
  lcd.setCursor(8, 1);
  lcd.print(F("Time Domain"));   // часовий проміжок 
  lcd.setCursor(8, 3);
  lcd.print(F("Number")); 
}

void loadSettingsMenu()
{
  if (gMode == MODE_SETTINGS_ADJUST_DATE || gMode == MODE_SETTINGS_ADJUST_SENS)
  {
    lcd.setCursor(SETTINGS_CHOISE_COL, gSettingsPointerRow);
    lcd.write(2);
  }
  
  lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
  lcd.write(0);

  for (byte i = SETTINGS_HORIZONTAL_LINE_BEGIN_ROW; i <= SETTINGS_HORIZONTAL_LINE_END_ROW; i++)
  {
    if (i == gSettingsPointerRow && gSettingsPointerCol == SETTINGS_HORIZONTAL_LINE_COL)
    {
      continue;
    }
    lcd.setCursor(SETTINGS_HORIZONTAL_LINE_COL, i);
    lcd.write(1);
  }
}
