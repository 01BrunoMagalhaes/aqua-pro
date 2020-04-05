#include <Wire.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <Thread.h>
#include <ThreadController.h>
#include <RtcDS3231.h>

#define DEBUG false

enum Screen { HOME, PLUGS, TEMP, ILUMINATION };

#define t 22 //temp sensor
#define waterSensor 23
#define btn1 24
#define btn2 25
#define btn3 26
#define btn4 27
#define relayHeater 28 //heater
#define relayCooler 29 //cooler
#define relay1 30
#define relay2 31
#define relay3 32
#define relayBoia 33

OneWire  sensorTemp(t);
DallasTemperature sensors(&sensorTemp);
DeviceAddress sensor1;
RtcDS3231<TwoWire> Rtc(Wire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Thread displayThread = Thread();
Thread waterLevelThread = Thread();
Thread tempControlThread = Thread();
ThreadController threadCtr = ThreadController();

  float tMin = 26;
  float tMax = 27;
  float tIdeal = 26.5;

void setup() {
  Serial.begin(9600);

  initializeClock();
  initializeTemp();
  initializeDisplay();
  initializeButtons();
  initializePlugs();
  initializeThreads();
}

void loop() {

  if (DEBUG) {
    Serial.print(F("DateTime: ")); Serial.println(clockDateTime());
    Serial.print(F("Temperature: ")); Serial.println(temp()); 
    Serial.println();
  }
  
  if (isButtonPressed(btn1)) {
    if (DEBUG) Serial.println("Button " + String(btn1) + " pressed!");
    displayData(1);
    delay(250);
  }
  if (isButtonPressed(btn2)) {
    if (DEBUG) Serial.println("Button " + String(btn2) + " pressed!");
    displaySwitch(0);
    delay(250);
  }
  if (isButtonPressed(btn3)) {
    if (DEBUG) Serial.println("Button " + String(btn3) + " pressed!");
    displaySelect();
    delay(250);
  }
  if (isButtonPressed(btn4)) {
    if (DEBUG) Serial.println("Button " + String(btn4) + " pressed!");
    delay(250);
  }

  threadsControl();
}
