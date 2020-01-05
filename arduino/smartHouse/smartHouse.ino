/*
 * void setup()
 * void loop()
 */
// BME280//////////////////////////////
///////////////////////////////////////
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

double gTemp;
double gHum;
double gPres;
double gAlt; // altitude

#define TEMP_ROW 2
#define TEMP_COL 0
#define HUM_ROW  3 
#define HUM_COL  0 
#define PRES_ROW 2
#define PRES_COL 12
#define ALT_ROW  3
#define ALT_COL  12

// номер градуса
#define TEMP_DEGREE 223

// DS3231 RTC/////////////////////////
///////////////////////////////////////
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define RESET_CLOCK 1
// години
#define HOURS_ROW   0
#define HOURS_COL   0

// хвилин
#define MINUTES_ROW 0
#define MINUTES_COL 8
// день 
#define DAY_ROW 1
#define DAY_COL 15
//місяць
#define MOUNTH_ROW 1
#define MOUNTH_COL 18
// назва дня
#define DAY_NAME_ROW 0
#define DAY_NAME_COL 15

// координати точок
#define TICK_UPPER_DOT_ROW 0 // верхня точка
#define TICK_LOWER_DOT_ROW 1 // нижня точка
#define TICK_DOTS_COL      7 // стовпець є для них обох одинаковий

// номер точок
#define TICK_DOT_NUMBER 165

byte gHour;
byte gMinute;
byte gSecond;
byte gDay;
byte gMounth;
byte gDayName;

// LCD 2004c I2C//////////////////////
//////////////////////////////////////
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F

LiquidCrystal_I2C lcd(I2C_ADDR, 20, 4);

// All sensors///////////////////////
/////////////////////////////////////
#define SENSORS_SHOW    3000 // оновлення показу сенсорів 
#define SENSORS_BACKUP  3000 // зчитування з сенсорів
#define TICK_TIME       500   // інтервал мигання точками
#define ONE_MINUTE      60000 // 

bool showTick;

unsigned long gTimerSensorBackup; // 
unsigned long gTimerTick;
unsigned long gTimerClock;

byte gMode;
bool isHomeLoaded = 0;

#define MODE_HOME      0
#define MODE_SETUP     1

////////////////////////////////////
void setup()
{
  setupLCD();
  setupSerial();
  setupBME();
  setupRTC();
      
  gTimerSensorBackup = 0;
  gTimerTick = 0;
  gTimerClock = 0;
  
  showTick = 0;
  gMode = MODE_HOME;

  readBME();
  readRTC();
  loadHomeForm();
  loadSensors();

  lcd.clear();
}

void loop()
{
 long currTime = millis();
   
   switch (gMode)
   {
    case MODE_HOME:
    {
      // завантаження форми
      if (!isHomeLoaded)
      {
        loadHomeForm();
        isHomeLoaded = 1;
      }

      // мигання точками ":"
      if (currTime - gTimerTick  >=  TICK_TIME)
      {
        gTimerTick += TICK_TIME;
        tickClock();    
      }

      // оновлення даних годинника
      if (currTime - gTimerClock >= ONE_MINUTE)
      {
        gTimerClock += ONE_MINUTE;
        backupClock();        
      }

      // оновлення даних з BME280
      if (currTime - gTimerSensorBackup  >= SENSORS_SHOW)
      {           
        gTimerSensorBackup += SENSORS_SHOW;
        readBME();
        loadSensors();
      }
    }      
    break;
    
    case MODE_SETUP:
    {
      //setupMode();
    }
    break;    
   }      
}
