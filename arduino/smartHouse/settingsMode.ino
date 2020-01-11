#define SETTINGS_WORD_COL 0
#define SETTINGS_WORD_ROW 0
#define SETTINGS_WORD_NUMB 8

#define SETTINGS_UPPER_LINE_BEGGINING_COL 8
#define SETTINGS_UPPER_LINE_END_COL       14
#define SETTINGS_UPPER_LINE_ROW           0

#define SETTINGS_HORIZONTAL_LINE_BEGIN_ROW 1
#define SETTINGS_HORIZONTAL_LINE_END_ROW   3
//#define SETTINGS_HORIZONTAL_LINE_COL       7//-----------------


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
                                   
void loadSegments()
{
  lcd.createChar(0, LEFT_POINTER);
  lcd.createChar(1, HORIZONTAL_LINE);
  lcd.createChar(3, HORIZONTAL_CURSOR_LINE);
}                                   

void loadSettingsForm()
{
  lcd.noCursor();
  lcd.clear();
  
  gSettingsPointerRow = 1;
  gSettingsPointerCol = 0;
  
  loadSegments();                                   
  
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
  
  loadNames();
}

void loadNames()
{
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
  
  for (byte i = 2; i <= 19; i++)
  {
    for (byte j = 1; j <= 3; j++)////-------------
    {
      lcd.setCursor(i, j);
      lcd.write(EMPTY_BAR);
    }
  }
}

void adjustRTCTime()
{
  clearAdjustMenu();
  lcd.setCursor(8, 1);

  // годинник
  if (gHour < 10)
  {
    lcd.print(0);
  }

  lcd.print(gHour);
  lcd.print(":");
  
  if (gMinute < 10)
  {
    lcd.print(0);
  }
  lcd.print(gMinute);

  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void adjustSensors()
{
  lcd.print(F(""));
}

void loadSettingsMenu()
{
  loadSegments();

  if (gMode == MODE_SETTINGS_ADJUST_DATE || gMode == MODE_SETTINGS_ADJUST_SENS)
  {
    lcd.setCursor(SETTINGS_CHOSE_SENSOR_COL, gSettingsPointerRow);
    lcd.write(3);
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
