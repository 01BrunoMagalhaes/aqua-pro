#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Thread.h>

#define relay1 26
#define relay2 27
#define relay3 28

enum Screen { HOME, PLUGS, TEMP, ILUMINATION };

Thread threadTest = Thread();

// LCD display buttons
int btn1 = 22;
int btn2 = 23;
int btn3 = 24;
int btn4 = 25;

void setup() {
  Serial.begin(9600);
  initializeDisplay();
  initializeButtons(btn1, btn2, btn3, btn4);
  initializePlugs();

  threadTest.onRun(displayDataThred); //Atribui função a thread.
  threadTest.setInterval(5000); //Atribui tempo de 30 minutos para execução para a Thread.
}

void loop() {
  if(isButtonPressed(btn1)) {
    Serial.println("Button " + String(btn1) + " pressed!");
    displayData(1);
    delay(250);
  }
  if(isButtonPressed(btn2)) {
    Serial.println("Button " + String(btn2) + " pressed!");
    displaySwitch(0);
    delay(250);
  }
  if(isButtonPressed(btn3)) {
    Serial.println("Button " + String(btn3) + " pressed!");
    displaySelect();
    delay(250);
  }
  if(isButtonPressed(btn4)) {
    Serial.println("Button " + String(btn4) + " pressed!");
  }

  if(threadTest.shouldRun()) {
    threadTest.run();  
  }

}
