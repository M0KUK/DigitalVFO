/*
* STEP 2 of 3 - Adding Serial monitor control
* Arduino VFO
* Created by Jakub M0KUK
* Created July 2023
* 
* Example of using Arduino platform for creating digital VFO
* prepared as part of RSGB activity during National Coding Week
* Hardware components:
* Arduino UNO, LCD I2C, Rotary encoder, Si5351
*/

#include <LiquidCrystal_I2C.h>

String inputText = "";

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define your LCD (16 column and 2 rows) using the library, I2C address 0x27

void setup()
{
  lcd.init(); //Initialize screen
  lcd.backlight();

  Serial.begin(9600);  //Initialize serial connection
}

//Main program, running in infinite loop
void loop()
{
  if (Serial.available()){
   inputText = Serial.readString();
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(inputText);
  lcd.setCursor(2, 1);
  lcd.print("Coding Week");
  delay(500);  //wait for half a second before restarting the loop
}