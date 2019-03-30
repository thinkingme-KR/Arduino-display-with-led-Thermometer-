int redpin = 11;
int greenpin = 10;
int bluepin = 9;
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <DHT_U.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview
DHT dht(DHTPIN, DHTTYPE,11);
char _h[5],_t[5];
void setup() {
  // put your setup code here, to run once:
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  display.setTextSize(1);
  float h = dht.readHumidity(); float t = dht.readTemperature();
  dtostrf(h,4, 1, _h); dtostrf(t, 4, 1, _t);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(15,10); display.println("T:");
  display.setCursor(15,24); display.println("H:");

  display.setCursor(28,10); display.println(_t);
  display.setCursor(28,24); display.println(_h);

  display.setCursor(52,10); display.println("C");
  display.setCursor(85,45); display.println(" %");
  display.display();
  if ( t < 20){
    setColor(0 , 0, 50);
  }
  else if ( t >21){
    setColor(0, 50, 0);
  }
  else if (t > 31){
    setColor(50, 0, 0);
    
  
  }
}
void setColor(int red, int green, int blue)
{
  analogWrite(redpin, red);
  analogWrite(greenpin, green);
  analogWrite(bluepin, blue);
}
