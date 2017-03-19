#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int buzzer = 9;
int hour = 1;
double minute = 18.0;
int second = 8;
String timeOfDay = "PM";
bool am = false;
long interval = 977;
bool buzzerState = false;
int switchPin = 7;

void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(switchPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  count();
}

String getTime(){
  return String(hour + ":" + int(minute));
}

void count(){
   second++;
   if(second == 60){
     second = 0;
     minute++;
     if(minute == 60){
       minute = 0;
       hour++;
       if(hour == 13){
         hour = 0;
         am = !am;
         if(timeOfDay == "AM"){
           timeOfDay = "PM";
        }
        else if(timeOfDay == "PM"){
           timeOfDay = "AM";
        }
       }
     }
   }  
}

void buzz(int freq){
  buzzerState = !buzzerState;
  if(buzzerState == true){
    tone(buzzer, freq);
  }

  else{
    noTone(buzzer);
  }
}

void updateDisplay(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 3);
  if(minute/10 >= 1){
    display.print(String(hour) + ":" + String(int(minute)) + " " + timeOfDay);
  }
  else{
    display.print(String(hour) + ":0" + String(int(minute)) + " " + timeOfDay);
  }
  display.setCursor(20, 20);
  display.setTextSize(1);
  display.print("Alarm: OFF");
  display.display();
  display.clearDisplay();
}

void alarm(){
  
}

void loop() {
  count();
  getTime();
  updateDisplay();
  delay(interval);
}
