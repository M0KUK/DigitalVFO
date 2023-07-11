/*
* STEP 3 of 3 - Final step
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
#include "si5351.h"
#include "Wire.h"

String inputText = "";
uint64_t frequency = 701000000ULL; // 7.030 MHz, in hundredths of hertz

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define your LCD (16 column and 2 rows) using the library, I2C address 0x27
Si5351 si5351;

void setup()
{
  lcd.init(); //Initialize screen
  lcd.backlight();

  Serial.begin(9600);  //Initialize serial connection

  // The crystal load value needs to match in order to have an accurate calibration
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);

  //Start on target frequency
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
  si5351.set_freq(frequency, SI5351_CLK2);
}

//Main program, running in infinite loop
void loop()
{
  //We expect frequency in kHz, e.g. 7030 to be given on input
  if (Serial.available()){
   inputText = Serial.readString();
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(inputText);
  lcd.setCursor(2, 1);
  lcd.print("Coding Week");
  //Calculate new frequency based on the input
  frequency = inputText.toInt() * 100000ULL;
  //Change the frequency on Si5351 module
  si5351.set_freq(frequency, SI5351_CLK2);
  delay(500);  //wait for half a second before restarting the loop
}