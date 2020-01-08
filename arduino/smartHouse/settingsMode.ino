#define SETTINGS_WORD_COL 0
#define SETTINGS_WORD_ROW 0
#define SETTINGS_WORD_NUMB 8

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

uint8_t CURSOR_LINE[8] = {
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
  lcd.createChar(2, CURSOR_LINE);
  lcd.createChar(3, HORIZONTAL_CURSOR_LINE);
}                                   

void loadSettingsForm()
{
  loadSegments();
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(F("SETTINGS"));
  for (byte i = 8; i <= 19; i++)
  {
    lcd.setCursor(i, 0);
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
  loadSegments();
  
  lcd.setCursor(7, 1);
  lcd.write(0);

  for (byte i = 2; i <= 3; i++)
  {
    lcd.setCursor(7, i);
    lcd.write(1);
  }
  lcd.setCursor(0, 1);
  lcd.write(3);
}
