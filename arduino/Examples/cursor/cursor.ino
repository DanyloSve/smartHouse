#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F

LiquidCrystal_I2C lcd(I2C_ADDR, 20, 4);

uint8_t L[8] = {
                            0b00000,
                            0b00000,  
                            0b00000,  
                            0b00000,  
                            0b00000,  
                            0b00000,  
                            0b00000,  
                            0b11111
                           };

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
void setup()
{
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

    
  lcd.createChar(0, L);
  lcd.createChar(1, LEFT_POINTER);
  
}


                           
void loop() 
{
  lcd.setCursor(12, 1);
  lcd.print("A");
  
  lcd.setCursor(11, 1);
  lcd.print("");
  lcd.write(0);
  
  lcd.write(1);

  delay(5000);
}
