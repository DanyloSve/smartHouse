// координати виведення даних з датчика
#define HOME_TEMP_ROW 2
#define HOME_TEMP_COL 0
#define HOME_HUM_ROW  3 
#define HOME_HUM_COL  0 
#define HOME_PRES_ROW 2
#define HOME_PRES_COL 12
#define HOME_ALT_ROW  3
#define HOME_ALT_COL  12

// номер градуса
#define HOME_TEMP_DEGREE 223
//////////////////////////////////////

void loadHomeForm()
{
  lcd.clear();
  
  // температура  
  lcd.setCursor(HOME_TEMP_COL + 5, HOME_TEMP_ROW);
  lcd.write(HOME_TEMP_DEGREE);
  lcd.print(F("C"));
  
  // вологість
  lcd.setCursor(HOME_HUM_COL + 5, HOME_HUM_ROW);
  lcd.print(F("%"));

  // тиск
  lcd.setCursor(HOME_PRES_COL + 6, HOME_PRES_ROW);
  lcd.print(F("mm"));
  
  // висота над рівним моря
  lcd.setCursor(HOME_ALT_COL + 6, HOME_ALT_ROW);
  lcd.print(F("m"));

  // таймер
  backupTimers();
  
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
  lcd.setCursor(HOME_TEMP_COL, HOME_TEMP_ROW);
  lcd.print(gTemp);
  
  // вологість
  lcd.setCursor(HOME_HUM_COL, HOME_HUM_ROW);
  lcd.print(gHum);
  
  // тиск
  lcd.setCursor(HOME_PRES_COL, HOME_PRES_ROW);
  lcd.print(gPres);
  
  // висота
  lcd.setCursor(HOME_ALT_COL, HOME_ALT_ROW);
  lcd.print(gAlt);
}
