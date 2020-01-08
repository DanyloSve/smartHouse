// Home Mode
// години
#define HOME_HOURS_ROW   0
#define HOME_HOURS_COL   0

// хвилин
#define HOME_MINUTES_ROW 0
#define HOME_MINUTES_COL 8

// день 
#define HOME_DAY_ROW 1
#define HOME_DAY_COL 15

//місяць
#define HOME_MONTH_ROW 1
#define HOME_MONTH_COL 18

// назва дня
#define HOME_DAY_NAME_ROW 0
#define HOME_DAY_NAME_COL 15

// координати точок
#define HOME_TICK_UPPER_DOT_ROW 0 // верхня точка
#define HOME_TICK_LOWER_DOT_ROW 1 // нижня точка
#define HOME_TICK_DOTS_COL      7 // стовпець є для них обох одинаковий

// номер точок
#define HOME_TICK_DOT_NUMBER 165

//SettingsMode 
#define SETTINGS_HOURS_COL 15
#define SETTINGS_HOURS_ROW 0 

#define SETTINGS_MINUTES_COL 18
#define SETTINGS_MINUTES_ROW 0

#define SETTINGS_TICK_DOTS_COL 17
#define SETTINGS_TICK_DOTS_ROW 0

// LT, UB, RT, LL, LR, UMB, LMB - користувацькі сегменти 
// користувацькі сегменти - блоки пікселів 5 x 8 пікселів
// максимальна кількість сегментів - 8 [0...7]
// 0b00111 тут 0 - вимк, 1 - увім
// lcd.createChar(0, LT); - створює користувацький символ LT з номером 0
// lcd.write(0); - малює користувацький семент піл номером 0, тобто LT
// та переводить курсор на наступний сегмент

// цифри для годиника
uint8_t LT[8] = {
                  0b00111,
                  0b01111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111
                 };
                 
uint8_t UB[8] = {
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b00000,  
                  0b00000,  
                  0b00000,  
                  0b00000,  
                  0b00000
                 };
                 
uint8_t RT[8] = {
                  0b11100,  
                  0b11110,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111
                 };
                 
uint8_t LL[8] = {
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b01111,  
                  0b00111
                };
                
uint8_t LB[8] = {
                 0b00000,  
                 0b00000,  
                 0b00000,  
                 0b00000,  
                 0b00000,  
                 0b11111,  
                 0b11111,  
                 0b11111
                };

uint8_t LR[8] = {
                 0b11111,  
                 0b11111,  
                 0b11111,  
                 0b11111,  
                 0b11111,  
                 0b11111,  
                 0b11110,  
                 0b11100
                };

uint8_t UMB[8] ={
                  0b11111,  
                  0b11111,  
                  0b11111,  
                  0b00000,  
                  0b00000,  
                  0b00000,  
                  0b11111,  
                  0b11111
                 };

uint8_t LMB[8] ={
                  0b11111,  
                  0b00000,  
                  0b00000,  
                  0b00000, 
                  0b00000,  
                  0b11111, 
                  0b11111,  
                  0b11111
                 };

// масив для виведення назв днів
const char *daysOfTheWeek[]  = 
{
  "SUN",
  "MON",
  "TUES",
  "WED",
  "THUR",
  "FRI",
  "SAT",
};

void printBigNum(byte number, byte startCol, byte startRow) 
{
  // очищення
  lcd.setCursor(startCol, startRow);
      lcd.write(32);
      lcd.write(32);
      lcd.write(32);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(32);
      lcd.write(32);
      lcd.write(32);
      
  switch (number)
  {
  case 0:
      lcd.setCursor(startCol, startRow);      // виставлення курсору в координати 
      lcd.write(0);                           // виклик користувацького сегменту
      lcd.write(1);  
      lcd.write(2);
      lcd.setCursor(startCol, startRow + 1); 
      lcd.write(3);  
      lcd.write(4);  
      lcd.write(5);
      break;      
    case 1:
      lcd.setCursor(startCol + 1, startRow);
      lcd.write(2);
      lcd.setCursor(startCol + 1, startRow + 1);
      lcd.write(3);
      break;
    case 2:
      lcd.setCursor(startCol, startRow);
      lcd.write(6);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(7);
      break;
    case 3:
      lcd.setCursor(startCol, startRow);
      lcd.write(1);
      lcd.write(6);
      lcd.write(5);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(4);
      lcd.write(7);
      lcd.write(5);
      break;
    case 4:
      lcd.setCursor(startCol, startRow);
      lcd.write(3);
      lcd.write(4);
      lcd.write(2);
      lcd.setCursor(startCol + 2, startRow + 1);
      lcd.write(3);
      break;
    case 5:
      lcd.setCursor(startCol, startRow);
      lcd.write(0);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(7);
      lcd.write(7);
      lcd.write(5);
      break;
    case 6:
      lcd.setCursor(startCol, startRow);
      lcd.write(0);
      lcd.write(6);
      lcd.write(6);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(5);
      break;
    case 7:
      lcd.setCursor(startCol, startRow);
      lcd.write(1);
      lcd.write(1);
      lcd.write(5);
      lcd.setCursor(startCol + 1, startRow + 1);
      lcd.write(0);
      break;
    case 8:
      lcd.setCursor(startCol, startRow);
      lcd.write(0);
      lcd.write(6);
      lcd.write(2);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(3);
      lcd.write(7);
      lcd.write(5);
      break;
    case 9:
      lcd.setCursor(startCol, startRow);
      lcd.write(0);
      lcd.write(1);
      lcd.write(2);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(7);
      lcd.write(7);
      lcd.write(5);
      break;
    case 10:// очистити велику цифру
      lcd.setCursor(startCol, startRow);
      lcd.write(32);
      lcd.write(32);
      lcd.write(32);
      lcd.setCursor(startCol, startRow + 1);
      lcd.write(32);
      lcd.write(32);
      lcd.write(32);
      break;
  }
}

void toTimer()
{
  gTotalSec++;
}

void convertToBigNumber(byte number, byte startCol, byte startRow)
{
  if (number < 10)
  {
    printBigNum(0, startCol, startRow);
    printBigNum(number, startCol + 4, startRow);
  }
  else
  {
    printBigNum(number / 10, startCol, startRow);
    printBigNum(number % 10, startCol + 4, startRow);
  }
  
}

void loadClockSegments()
{
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
}

void backupClock()
{ 
  gSecond++;
  
  if (gSecond >= 60)
  {   
    gSecond = 0;
    gMinute++;
    loadClockSegments(); 
    
    if (gMinute == 30 || gMinute >= 60) // кожного дня зчитуються дані з RTC
    { 
      backupTimers();
      byte tempHour = gHour;
      byte tempDay = gDay;
      byte tempMounth = gMounth; 
          
      readRTC();

      if (tempHour != gHour)
      {
       backupHour();
      }

      if (MODE_HOME)
      {
        if (tempMounth != gMounth)
        {
         backupMonth();
        }
      
        if (tempDay != gDay)
        {
         backupDay();
        } 
      }     
    }
    backupMinute();                  
  }    
}

void backupMinute()
{
  if (gMode == MODE_HOME)
  {
    convertToBigNumber(gMinute, HOME_MINUTES_COL, HOME_MINUTES_ROW); // виведення хвилин 
  }
  else if (gMode == MODE_SETTINGS)
  {
    lcd.setCursor(SETTINGS_MINUTES_COL, SETTINGS_MINUTES_ROW);
    if (gMinute < 10)
    {
      lcd.print(0);
    }
    lcd.print(gMinute);
  } 
}

void backupHour()
{
  if (gMode == MODE_HOME)
  {
    convertToBigNumber(gHour,HOME_HOURS_COL, HOME_HOURS_ROW);       // виведення годин
  }
  else if (gMode == MODE_SETTINGS)
  {
    lcd.setCursor(SETTINGS_HOURS_COL, SETTINGS_HOURS_ROW);
    lcd.print(gHour);
  }
}

void backupMonth()
{
  lcd.setCursor(HOME_MONTH_COL, HOME_MONTH_ROW);
  if (gMounth < 10)
  {
    lcd.print(0);
  }
  lcd.print(gMounth);
}

void backupDay()
{
  lcd.setCursor(HOME_DAY_COL, HOME_DAY_ROW);
  if (gDay < 10)
  {
    lcd.print(0);
  }
  
  lcd.print(gDay);
  lcd.print(".");
  
  lcd.setCursor(HOME_DAY_NAME_COL, HOME_DAY_NAME_ROW);
  lcd.print(daysOfTheWeek[gDayName]);
}

void tickClock()
{
  #define EMPTY_BAR 32 // пустий сегмент, блок
  
  if (gMode == MODE_HOME)
  {
    if (showTick)
    {
      lcd.setCursor(HOME_TICK_DOTS_COL, HOME_TICK_UPPER_DOT_ROW);
      lcd.write(HOME_TICK_DOT_NUMBER);
      lcd.setCursor(HOME_TICK_DOTS_COL, HOME_TICK_LOWER_DOT_ROW);
      lcd.write(HOME_TICK_DOT_NUMBER);
    }
    else
    {
      lcd.setCursor(HOME_TICK_DOTS_COL, HOME_TICK_UPPER_DOT_ROW);
      lcd.write(EMPTY_BAR);
      lcd.setCursor(HOME_TICK_DOTS_COL, HOME_TICK_LOWER_DOT_ROW);
      lcd.write(EMPTY_BAR);
    }
  }
  else if (gMode == MODE_SETTINGS)
  {
    if (showTick)
    {
      lcd.setCursor(SETTINGS_TICK_DOTS_COL, SETTINGS_TICK_DOTS_ROW);
      lcd.print(":");
    }
    else
    {
      lcd.setCursor(SETTINGS_TICK_DOTS_COL, SETTINGS_TICK_DOTS_ROW);
      lcd.write(EMPTY_BAR);
    }
  }
  showTick = !showTick;
}

void backupTimers()
{
  gTotalSec          = gSecond;
  gTimerSensorBackup = gSecond;
  gTimerTick         = gSecond;
  gTimerClock        = gSecond;
}
