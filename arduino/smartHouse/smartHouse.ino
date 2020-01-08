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

// DS3231 RTC/////////////////////////
///////////////////////////////////////
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define RESET_CLOCK 1

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

// MsTimer ///////////////////////////
#include <MsTimer2.h>

#define ONE_SECOND 1000

unsigned long gTotalSec;
unsigned long gTimerSensorBackup; 
unsigned long gTimerTick;
unsigned long gTimerClock;

//OneButton//////////////////////////
/////////////////////////////////////
#include "OneButton.h"

OneButton buttOk (4, false);  // confirm button 
OneButton buttInc(5, false); // increment button (+)
OneButton buttDec(6, false); // decrement button (-)

// All sensors///////////////////////
/////////////////////////////////////
// у секундах
#define SENSORS_SHOW    3    // (у секундах) оновлення показу сенсорів 
#define SENSORS_BACKUP  3    // (у секундах) зчитування з сенсорів
#define TICK_TIME       1    // (у секундах) інтервал мигання точками

bool showTick;

byte gMode;
bool isHomeLoaded = 0;
bool isSettingsLoaded = 0;

#define MODE_HOME      0
#define MODE_SETTINGS  1

////////////////////////////////////
void setup()
{
  setupLCD();
  setupSerial();
  setupBME();
  setupRTC();

  setupMsTimer();
  
  showTick = 0;
  gMode = MODE_HOME;
  //gMode = MODE_SETTINGS;

  readBME();
  readRTC();
  loadHomeForm();
  loadSensors();
}

void loop()
{   
   switch (gMode)
   {
    case MODE_HOME:
    {
      // завантаження форми
      if (!isHomeLoaded)
      {
        loadHomeForm();
        isHomeLoaded = 1;
        isSettingsLoaded = 0;
      }

      if (gTotalSec - gTimerClock >= ONE_SECOND / ONE_SECOND)
      {
        gTimerClock += ONE_SECOND / ONE_SECOND;  
        loadSensors();  
      }

    }      
    break;
    
    case MODE_SETTINGS:
    {
      if (!isSettingsLoaded)
      {
        loadSettingsForm();
        isHomeLoaded = 0;
        isSettingsLoaded = 1;
      }

      setPointer();
    }
    break;    
   }    
  
  // оновлення даних з BME280
  if (gTotalSec - gTimerSensorBackup  >= SENSORS_SHOW)
  {           
    gTimerSensorBackup += SENSORS_SHOW;
    readBME();
   } 

  // мигання точками ":"
  if (gTotalSec - gTimerTick  >=  TICK_TIME)
  {
    gTimerTick += TICK_TIME;
    tickClock();    
  }

  // оновлення даних годинника
  if (gTotalSec - gTimerClock >= ONE_SECOND / ONE_SECOND)
  {
    gTimerClock += ONE_SECOND / ONE_SECOND;
    backupClock();        
  }
}
