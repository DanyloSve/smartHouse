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

#define ONE_SECOND 990

unsigned long gTotalSec;
unsigned long gTimerSensorBackup; 
unsigned long gTimerLoadSensors;
unsigned long gTimerTick;
unsigned long gTimerClock;

//OneButton//////////////////////////
/////////////////////////////////////
#include "OneButton.h"

#define BUTTON_OK_PIN   A0
#define BUTTON_INC_PIN  5
#define BUTTON_DEC_PIN  6

OneButton buttOk (BUTTON_OK_PIN , false);  // confirm button 
OneButton buttInc(5, false);  // increment button (+)
OneButton buttDec(6, false);  // decrement button (-)

bool isPressedButtOk     = 0;
bool isDoublePressOk     = 0;
bool isLongPressStartOk  = 0;
bool isLongPressStopOk   = 0;

bool isPressedButtInc    = 0;
bool isDoublePressInc    = 0;
bool isLongPressStartInc = 0;
bool isLongPressStopInc  = 0;

bool isPressedButtDec    = 0;
bool isDoublePressDec    = 0;
bool isLongPressStartDec = 0;
bool isLongPressStopDec  = 0;

// All sensors///////////////////////
/////////////////////////////////////
// у секундах
#define SENSORS_SHOW    3    // (у секундах) оновлення показу сенсорів 
#define SENSORS_BACKUP  3    // (у секундах) зчитування з сенсорів
#define TICK_TIME       1    // (у секундах) інтервал мигання точками

bool showTick = 0;

bool isHomeLoaded     = 0;
bool isSettingsLoaded = 0;

#define MODE_HOME      0
#define MODE_SETTINGS  1

byte gMode = MODE_HOME;

////////////////////////////////////
void setup()
{
  setupLCD();
  setupSerial();
  setupBME();
  setupRTC();
  //setupOneButton();

  readBME();
  readRTC();
  
  setupMsTimer();
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

      // виведення даних з сенсорів
      if (gTotalSec - gTimerLoadSensors >= SENSORS_SHOW)
      {
        gTimerLoadSensors += SENSORS_SHOW;  
        loadSensors();  
      }

    }      
    break;
    
    case MODE_SETTINGS:
    {
      // заватнтаження форми
      if (!isSettingsLoaded)
      {
        loadSettingsForm();
        isHomeLoaded = 0;
        isSettingsLoaded = 1;
      }

      // виставлення курсору ">"
      setPointer();

      // зчитання сигналу з кнопок
      buttInc.tick();
      buttDec.tick();
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
  if (gTotalSec - gTimerClock >= 1) // 1 sec
  {
    gTimerClock += 1;
    backupClock();        
  }

  // зчитання сигналу з OK кнопки
  /////////////////////////////////
 /* buttOk.tick();
  
  if (isPressedButtOk)
  {
    if (gMode == MODE_HOME)
    {
      gMode = MODE_SETTINGS;
    }
    else if (gMode == MODE_SETTINGS)
    {
      gMode = MODE_HOME;
    }

    isPressedButtOk = 0;
  }
  */
}
