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

void clearBar(byte startCol, byte startRow)
{
 #define EMPTY_BAR 32 // пустий сегмент, блок
 lcd.setCursor(startCol, startRow);
 lcd.write(EMPTY_BAR);
}

void loadHomeForm()
{
  // температура  
  lcd.setCursor(TEMP_COL + 5, TEMP_ROW);
  lcd.write(TEMP_DEGREE);
  lcd.print(F("C"));
  
  // вологість
  lcd.setCursor(HUM_COL + 5, HUM_ROW);
  lcd.print(F("%"));

  // тиск
  lcd.setCursor(PRES_COL + 6, PRES_ROW);
  lcd.print(F("mm"));
  
  // висота над рівним моря
  lcd.setCursor(ALT_COL + 6, ALT_ROW);
  lcd.print(F("m"));

  // годинник
  loadClockSegments();
  backupMinute();
  backupHour();
  backupDay();
  backupMonth();
}

void loadSensors()
{
  // температура
  lcd.setCursor(TEMP_COL, TEMP_ROW);
  lcd.print(gTemp);
  
  // вологість
  lcd.setCursor(HUM_COL, HUM_ROW);
  lcd.print(gHum);
  
  // тиск
  lcd.setCursor(PRES_COL, PRES_ROW);
  lcd.print(gPres);
  
  // висота
  lcd.setCursor(ALT_COL, ALT_ROW);
  lcd.print(gAlt);
}

void tickClock()
{
   if (showTick)
  {
    lcd.setCursor(TICK_DOTS_COL, TICK_UPPER_DOT_ROW);
    lcd.write(TICK_DOT_NUMBER);
    lcd.setCursor(TICK_DOTS_COL, TICK_LOWER_DOT_ROW);
    lcd.write(TICK_DOT_NUMBER);
  }
  else
  {
    clearBar(TICK_DOTS_COL, TICK_UPPER_DOT_ROW);
    clearBar(TICK_DOTS_COL, TICK_LOWER_DOT_ROW);
  }

  showTick = !showTick;
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
  loadClockSegments();  
  gMinute++;

  if (gMinute == 60)
  {   
    gMinute = 0;
    gHour++;

    if (gHour == 24) // кожного дня зчитуються дані з RTC
    { 
      byte tempHour = gHour;
      byte tempMinute = gMinute;
      byte tempDay = gDay;
      byte tempMounth = gMounth; 
          
      readRTC();

      if (tempHour != gHour)
      {
       backupHour();
      }
    
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

void backupMinute()
{
  convertToBigNumber(gMinute, MINUTES_COL, MINUTES_ROW); // виведення хвилин
  
}

void backupHour()
{
  convertToBigNumber(gHour, HOURS_COL, HOURS_ROW);       // виведення годин
}

void backupMonth()
{
  lcd.setCursor(MOUNTH_COL, MOUNTH_ROW);
  if (gMounth < 10)
  {
    lcd.print(0);
  }
  lcd.print(gMounth);
}

void backupDay()
{
  lcd.setCursor(DAY_COL, DAY_ROW);
  if (gDay < 10)
  {
    lcd.print(0);
  }
  
  lcd.print(gDay);
  lcd.print(".");
  
  lcd.setCursor(DAY_NAME_COL, DAY_NAME_ROW);
  lcd.print(daysOfTheWeek[gDayName]);
}
