#define SETTINGS_WORD_COL 0
#define SETTINGS_WORD_ROW 0
#define SETTINGS_WORD_NUMB 8

#define SETTINGS_UPPER_LINE_BEGGINING_COL 8
#define SETTINGS_UPPER_LINE_END_COL       14
#define SETTINGS_UPPER_LINE_ROW           0

#define SETTINGS_HORIZONTAL_LINE


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

uint8_t RIGTH_POINTER[8] = {
                            0b00011,
                            0b00111,  
                            0b01111,  
                            0b11111,  
                            0b11111,  
                            0b01111,  
                            0b00111,  
                            0b00011
                           };

uint8_t REVERSE_LEFT_POINTER[8] = {
                                    0b00111,
                                    0b00011,  
                                    0b00001,  
                                    0b00000,  
                                    0b00001,  
                                    0b00011,  
                                    0b00111,  
                                    0b11111
                                   };

uint8_t LOWER_LINE[8] = {
                                    0b00000,
                                    0b00000,  
                                    0b00000,  
                                    0b00000,  
                                    0b00000,  
                                    0b00000,  
                                    0b00000,  
                                    0b11111
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
  lcd.createChar(2, LOWER_LINE);
  lcd.createChar(3, HORIZONTAL_CURSOR_LINE);
}                                   

void loadSettingsForm()
{
  gSettingsPointerRow = 1;
  gSettingsPointerCol = 0;
  
  loadSegments();                                   
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(F("SETTINGS"));
  for (byte i = SETTINGS_UPPER_LINE_BEGGINING_COL; i <= SETTINGS_UPPER_LINE_END_COL; i++)
  {
    lcd.setCursor(i, SETTINGS_UPPER_LINE_ROW);
    lcd.write(2);
  }  
  
  backupTimers();
  backupMinute();
  backupHour();

  lcd.setCursor(1, 1);
  lcd.print(F("Clock"));
  lcd.setCursor(1, 2);
  lcd.print(F("Sensors"));
  lcd.setCursor(1, 3);
  lcd.print(F("EXIT"));
}
void drawUpperLine()
{
  
}

void drawHorizontalLine()
{
  
}
void adjustRTCTime()
{
  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void adjustSensors()
{
  lcd.print(F(""));
}

void setPointer()
{
  if (isPressedButtOk)
  {
    isPressedButtOk = 0;
    gSettingsPointerCol = 7; 
    lcd.setCursor(0, 1);
    lcd.write(3);
  }
  
  loadSegments();
  
  lcd.setCursor(gSettingsPointerCol, gSettingsPointerRow);
  lcd.write(0);


  for (byte i = 1; i <= 3; i++)
  {
    if (i == gSettingsPointerRow && gSettingsPointerCol == 7)
    {
      continue;
    }
    lcd.setCursor(7, i);
    lcd.write(1);
  }
}
