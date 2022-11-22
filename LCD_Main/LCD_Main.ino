#include <DHT.h>
#include <DHT_U.h>

#include <arduino-timer.h>

/*
    LCD_I2C - Arduino library to control a 16x2 LCD via an I2C adapter based on PCF8574
    Copyright(C) 2020 Blackhack <davidaristi.0504@gmail.com>
    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#include <LCD_I2C.h>



LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

int sensorPin = 2;
DHT dht(sensorPin, DHT11);

int buttonPin = 6;
int curButtonState = 0;
int lastButtonState = 0;

int screenPos = 0;

float sensorVal = 0;
float voltz = 0;
float temp = 0;

auto timerTemp = timer_create_default();

void check_temp(){
  //sensorVal = analogRead(sensorPin);
  sensorVal = dht.readTemperature();
  Serial.println(sensorVal);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  curButtonState = digitalRead(buttonPin);
  timerTemp.every(2000, check_temp);
  
  dht.begin();
}

void loop()
{
  //temp = sensorVal * 0.48828125;
  String s = "Temp: ";
  s.concat(sensorVal);
  
  lastButtonState    = curButtonState;      // save the last state
  curButtonState = digitalRead(buttonPin); // read new state

  //lcd.print("     Hello"); // You can make spaces using well... spaces
  if(screenPos == 0){
    lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
    lcd.print("Health: 10");
    lcd.setCursor(0, 1);
    lcd.print("Hydration: 10");
  }else{
    lcd.setCursor(0,0);
    Serial.println(sensorVal);
    lcd.print(s);
  }
  if(lastButtonState == HIGH && curButtonState == LOW) {
  Serial.println("The button is pressed");
  
  if(screenPos == 0){
    screenPos = 1;  
  }
  else{
    screenPos = 0;
  }

    lcd.clear();
  }
}
