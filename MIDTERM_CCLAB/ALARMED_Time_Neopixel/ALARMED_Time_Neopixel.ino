
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <TimeLib.h>
#include <TimeAlarms.h>

AlarmId id;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A5

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

#define SENSOR_LOW  0         //these numbers will change the sensitivity of the sensor.  Lower numbers = harder step to trigger
#define SENSOR_HIGH  10 

const int WEIGHT_PIN = A0;  // Analog input pin that the force sensitive resistor is attached to
int sensorValue = 0;    

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

  // create the alarms, to trigger at specific times
  Alarm.alarmRepeat(9,00,00, MorningAlarm);  
  Alarm.alarmRepeat(12,00,0,NoonAlarm);  
  Alarm.alarmRepeat(18,00,0,EveningAlarm);  
  Alarm.alarmRepeat(22,00,0,BeforeBedAlarm);  
  pinMode(WEIGHT_PIN, INPUT);
  pinMode(PIN, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  digitalClockDisplay();
  sensorValue = analogRead(WEIGHT_PIN); 
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);
   
  Alarm.delay(1000); // wait one second between clock display
}

void MorningAlarm() {
    pixels.setPixelColor(0, pixels.Color(255,0,0)); 
    pixels.setPixelColor(1, pixels.Color(255,0,0));
    pixels.setPixelColor(2, pixels.Color(255,0,0));
    pixels.setPixelColor(3, pixels.Color(255,0,0));
    pixels.setPixelColor(4, pixels.Color(255,0,0));
    pixels.setPixelColor(5, pixels.Color(255,0,0));
    pixels.setPixelColor(6, pixels.Color(255,0,0));
    pixels.setPixelColor(7, pixels.Color(255,0,0));
    pixels.show();
    delay(8000); 
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.setPixelColor(4, pixels.Color(0,0,0));
    pixels.setPixelColor(5, pixels.Color(0,0,0));
    pixels.setPixelColor(6, pixels.Color(0,0,0));
    pixels.setPixelColor(7, pixels.Color(0,0,0));
    pixels.show();
}

void NoonAlarm() {
    pixels.setPixelColor(0, pixels.Color(255,0,0)); 
    pixels.setPixelColor(1, pixels.Color(255,0,0));
    pixels.setPixelColor(2, pixels.Color(255,0,0));
    pixels.setPixelColor(3, pixels.Color(255,0,0));
    pixels.setPixelColor(4, pixels.Color(255,0,0));
    pixels.setPixelColor(5, pixels.Color(255,0,0));
    pixels.show();
    delay(8000); 
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.setPixelColor(4, pixels.Color(0,0,0));
    pixels.setPixelColor(5, pixels.Color(0,0,0));
    pixels.show();
}

void EveningAlarm() {
    pixels.setPixelColor(0, pixels.Color(255,0,0)); 
    pixels.setPixelColor(1, pixels.Color(255,0,0));
    pixels.setPixelColor(2, pixels.Color(255,0,0));
    pixels.setPixelColor(3, pixels.Color(255,0,0));
    pixels.show();
    delay(8000); 
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.show();
}

void BeforeBedAlarm() {
    pixels.setPixelColor(0, pixels.Color(255,0,0)); 
    pixels.setPixelColor(1, pixels.Color(255,0,0));
    pixels.show();
    delay(8000); 
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.show();
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


