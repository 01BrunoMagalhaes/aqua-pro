#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD display buttons
int btn1 = 22;
int btn2 = 23;
int btn3 = 24;
int btn4 = 25;

void setup() {
  initializeDisplay();
  initializeButtons(btn1, btn2, btn3, btn4);
  Serial.begin(9600);
  displayHome();
}


void loop() {
  if(isButtonPressed(btn1)) {
    Serial.println("Button " + String(btn1) + " pressed!");
    displayHome();
  }
  if(isButtonPressed(btn2)) {
    Serial.println("Button " + String(btn2) + " pressed!");
    clearDisplay();
  }
  if(isButtonPressed(btn3)) {
    Serial.println("Button " + String(btn3) + " pressed!");
  }
  if(isButtonPressed(btn4)) {
    Serial.println("Button " + String(btn4) + " pressed!");
  }

//  Hello (); // imprimindo mensagem
//  Flash ();         // piscando a mensagem
//  Blink ();         // teste do cursor
//  AutoScroll ();    // teste de rolagem de mensagem
//  dirText ();       // teste de direcao de mensagem
//  delay(1000);      // atraso de 1 segundo
}
