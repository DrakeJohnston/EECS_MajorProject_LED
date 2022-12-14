#include <arduino-timer.h>
#include <LCD_I2C.h>

auto timer = timer_create_default();

int pot = A0;
int buttonSwitch = 2;
int buzzer = 4;

int timerVal = 10;
bool timerActive = false;

LCD_I2C LCD(0x27, 16, 2);

void runTimer(bool isStarting){
//do timer stuff here please  
}

void setup() {
  Serial.begin(9600);
  LCD.begin();
  LCD.backlight();
  LCD.setCursor(0, 1);
  LCD.print("00:00");

  pinMode(buttonSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  LCD.setCursor(0,0);
  int currentPot = 0;
  
  int buttonState = digitalRead(buttonSwitch);
  int potState = (analogRead(pot)/60);
  int currentPot = potState;
  Serial.println(potState);

  if(buttonState == HIGH){
    tone(buzzer, 1000);
    //plz check for elapsed time using time class
    //Note the origin has not been fetch since last so make sure to do that
    //first before moving this script to the git repos 
    int timeElapsed = 1;
    if(timeElapsed >= 3){
      timer = 0;
      timerActive = false;
      runTimer(false);  
    }
    
   }else{
     //Re go through the logic here
    noTone(buzzer);
    if(!timerActive){
      runTimer(true);
      timerActive = true;
    }else{
      runTimer(false);
      timerActive = false;
    }
   }
  
}
