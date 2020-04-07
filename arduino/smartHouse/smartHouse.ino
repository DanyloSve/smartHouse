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

int gSensorReadTimeDomainSec = 3; // часовий проміжок зчитування з сенсорів
int gSensorShowSec           = 3; // часовий період виведення даних з сенсорів MODE_HOME
int gNumberOfTimeDomains     = 20; // кількість проміжків для зчитування з сенсорів для знятття усередненого значення

int gSettingsAdjustingSensorReadTimeDomainSec; // тимчасова знінна для приймання значень gSensorReadTimeDomainSec під час налаштування
int gSettingsAdjustingNumberOfTimeDomains; //  тимчасова знінна для приймання значень gNumberOfTimeDomains  під час налаштування

// DS3231 RTC/////////////////////////
///////////////////////////////////////
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define RESET_CLOCK 0

byte gHour;
byte gMinute;
byte gSecond;
byte gDay;
byte gMonth;
byte gDayName;
int  gYear;

// LCD 2004c I2C//////////////////////
//////////////////////////////////////
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F

LiquidCrystal_I2C lcd(I2C_ADDR, 20, 4);

// MsTimer ///////////////////////////
//////////////////////////////////////
#include <MsTimer2.h>

#define ONE_SECOND_MILLI_SEC  996
#define CALIBRATE_CLOCK_MIN 1

// відраховує кількість пройдених секунд після запуску або оновлення таймерів
unsigned long gTotalSec;

// таймери
unsigned long gTimerSensorBackup;
unsigned long gTimerLoadSensors;
unsigned long gTimerTick;
unsigned long gTimerClock;

//OneButton//////////////////////////
/////////////////////////////////////
#include "OneButton.h"

//#define BUTTON_OK_PIN   (A0)
//#define BUTTON_INC_PIN  (A2)
//#define BUTTON_DEC_PIN  (A1)

OneButton buttOk (A0, false);  // confirm button
OneButton buttInc(A2, false);  // increment button (+)
OneButton buttDec(A1, false);  // decrement button (-)

#define MODE_SETTINGS_ADJUST_DATE_ROW   1
#define MODE_SETTINGS_ADJUST_SENS_ROW   2
#define EXIT_SETTING_MODE_ROW           3

#define SETTINGS_CHOISE_COL             0
#define SETTINGS_ADJUSTMENT_COL         7

// координати вказівника вибору у меню налаштувань
byte gSettingsPointerRow;
byte gSettingsPointerCol;
byte gSettingsConfirmAdjustment = 0;

int *gpSettingsAdjustValue;

// тимчасові знінні для приймання значень gHour, gMinute ...  і тд під час налаштування
int gAdjustingHour;    // тимчасова знінна для приймання значень gHour   під час налаштування
int gAdjustingMinute;  // тимчасова знінна для приймання значень gMinute під час налаштування
int gAdjustingDay;     // тимчасова знінна для приймання значень gDay    під час налаштування
int gAdjustingMonth;   // тимчасова знінна для приймання значень gMonth  під час налаштування
int gAdjustingYear;    // тимчасова знінна для приймання значень gYear   під час налаштування
byte gSettingsRank = 1; // розряд для редагування чисел під час налаштування 
                        // 0 =  1(e0), 1 =  10(e1) , 2 = 100 (e2), 3 = 1000 (e3)

//wifi//////////////////////////////
////////////////////////////////////
#define wifiName "Moto"
#define wifiPass "ursaursa"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 
 
// All sensors///////////////////////
/////////////////////////////////////
// у секундах
//#define SENSORS_SHOW_SEC    3    // (у секундах) оновлення показу сенсорів 
//#define SENSORS_BACKUP_SEC  3    // (у секундах) зчитування з сенсорів
#define TICK_TIME_SEC       1    // (у секундах) інтервал мигання точками

bool isHomeLoaded     = 0;
bool isSettingsLoaded = 0;
bool isSettingsExit   = 0;

#define MODE_HOME                 0
#define MODE_SETTINGS_ADJUST_DATE 1
#define MODE_SETTINGS_ADJUST_SENS 2
#define MODE_SETTINGS             4

byte gMode = MODE_HOME;

#define PLACE_ID 1 // id місця зняття даних
                            // 0 - тестові дані

////////////////////////////////////
void setup()
{
  setupLCD();
  setupSerial();
  setupBME();
  setupRTC();
  setupOneButton();

  readBME();
  readRTC();

  setupMsTimer();
  loadHomeForm();
  loadSensors();
}

void loop()
{   
    if(gMode ==  MODE_HOME)
    {
     // виведення даних з сенсорів
     if (gTotalSec - gTimerLoadSensors >= gSensorShowSec )
     {
       gTimerLoadSensors += gSensorShowSec ;
       loadSensors();
     }
    }      
    else
    { 
     // зчитання сигналу з кнопок
     loadSegments();
     buttInc.tick();
     buttDec.tick();
    }
  
  // оновлення даних з BME280
  if (gTotalSec - gTimerSensorBackup  >= gSensorReadTimeDomainSec)
  {
    gTimerSensorBackup += gSensorReadTimeDomainSec;
    readBME();
    
    static double tempForSql{0};
    static double humForSql{0};
    static double presForSql{0};
    static double altForSql{0}; // altitude
    
    tempForSql += gTemp;
    humForSql  += gHum;
    presForSql += gPres;
    altForSql  += gAlt; 
    
    static int passedTimeDomains{0};
    
    if (gNumberOfTimeDomains <= passedTimeDomains)
    {            
       insertDataToMySql(
       (unsigned int)(tempForSql * 100 /(gNumberOfTimeDomains+1)),
       (unsigned int)(humForSql  * 100 /(gNumberOfTimeDomains+1)),
       (unsigned long)(presForSql* 100 /(gNumberOfTimeDomains+1)),
       (unsigned long)(altForSql * 100 /(gNumberOfTimeDomains+1)));
       
       passedTimeDomains = 0;

       tempForSql  = 0;
       humForSql   = 0;
       presForSql  = 0;
       altForSql   = 0; 
    }
    else
    {
      passedTimeDomains++;
    }   
  }

  // мигання точками ":"
  if (gTotalSec - gTimerTick  >=  TICK_TIME_SEC)
  {
    gTimerTick += TICK_TIME_SEC;
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
  buttOk.tick();
}
