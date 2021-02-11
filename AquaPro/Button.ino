void initializeButtons() {
  //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btnManualFeed, INPUT_PULLUP);
  pinMode(btnDisplayLight, INPUT_PULLUP);
  
  pinMode(waterSensor, INPUT);
}

boolean isButtonPressed(int pin){
  return digitalRead(pin) == LOW;
}
