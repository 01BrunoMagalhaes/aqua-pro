int thisChar = 0 ;
Screen actualScreen = HOME;
String lastSelected = "";
// Custom Character Generator http://omerk.github.io/lcdchargen/
byte thermometer[8] = {0b00100,0b01010,0b01010,0b01110,0b01110,0b11111,0b11111,0b01110};
byte customChar[8] = {0b00000,0b00100,0b01010,0b01010,0b00100,0b00000,0b00000,0b00000};
byte upChar[8] = {0b00100,0b01110,0b11111,0b01110,0b01110,0b01110,0b01110,0b01110};
byte downChar[8] = {0b01110,0b01110,0b01110,0b01110,0b01110,0b11111,0b01110,0b00100};

void initializeDisplay() {
  lcd.init();                      // inicializa LCD
  turnDisplayOn();

  lcd.createChar(0, thermometer);
  lcd.createChar(1, customChar);
  lcd.createChar(2, upChar);
  lcd.createChar(3, downChar);

  displayData(0);
}

void displayDataThread() {
  displayData(0);
}

void displayData(boolean next) {
  if (DEBUG) {
    Serial.print(F("actualScreen: ")); Serial.print(actualScreen); Serial.print(F(" next: ")); Serial.println(next);
  }
  switch (actualScreen) {
    case HOME:
      if (next) {
        displayPlugs(next);
        actualScreen = PLUGS;
      } else {
        displayHome();
      }
    break;

    case PLUGS:
      if (next) {
        displayTemp(next);
        actualScreen = TEMP;
      } else {
        displayPlugs(next);
      }

    break;

    case TEMP:
      if (next) {
        displayIlumination(next);
        actualScreen = ILUMINATION;       
      } else {
        displayTemp(next);
      }
    break;

    case ILUMINATION:
      if (next) {
        displayHome();
        actualScreen = HOME;
      } else {
        displayIlumination(next);
      }
    break;   
  }
  
  if (next) {
    lastSelected = "";
  }

}

void displaySwitch(boolean refresh) {

  switch(actualScreen) {
    case PLUGS:
      if (lastSelected.equals("plug1")) {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("1 " + getRelayStatus(relay1) + " ");
        } else {
          lcd.setCursor(0,1);
          lcd.print("2 " + getRelayStatus(relay2) + " ");
          lastSelected = "plug2";      
        }
      } else if (lastSelected.equals("plug2")) {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("2 " + getRelayStatus(relay2) + " ");
        } else {
          lcd.setCursor(0,1);
          lcd.print("3 " + getRelayStatus(relay3) + " ");
          lastSelected = "plug3";     
        }
      } else {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("3 " + getRelayStatus(relay3) + " ");        
        } else {
          lcd.setCursor(0,1);
          lcd.print("1 " + getRelayStatus(relay1) + " ");
          lastSelected = "plug1";
        }
      }
    break;

    case TEMP:
      if (lastSelected.equals("ideal")) {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("IDEAL 26.5      ");
        } else {
          lcd.setCursor(0,1);
          lcd.print("MINIMUM 26.0");
          lastSelected = "min"; 
        }
      } else if (lastSelected.equals("min")) {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("MINIMUM 26.0    ");
        } else {
          lcd.setCursor(0,1);
          lcd.print("MAXIMUM 27.0    ");
          lastSelected = "max"; 
        }
      } else {
        if (refresh) {
          lcd.setCursor(0,1);
          lcd.print("MAXIMUM 27.0    ");
        } else {
          lcd.setCursor(0,1);
          lcd.print("IDEAL 26.5      ");
          lastSelected = "ideal";
        }
      }
    break;

    case ILUMINATION:
      lcd.setCursor(0,0);

      if (lastSelected.equals("channel2")) {
        if (refresh) {
          lcd.print("CHANNEL 2 ON ");
          lcd.setCursor(0,1);
          lcd.write(2);
          lcd.setCursor(2,1);
          lcd.print("08:00");
          lcd.setCursor(8,1);
          lcd.write(3);
          lcd.setCursor(10,1);
          lcd.print("17:00");
        } else {
          lcd.print("CHANNEL 1 OFF ");
          lcd.setCursor(0,1);
          lcd.write(2);
          lcd.setCursor(2,1);
          lcd.print("08:30");
          lcd.setCursor(8,1);
          lcd.write(3);
          lcd.setCursor(10,1);
          lcd.print("16:30");
          lastSelected = "channel1";
        }
      } else {
        if (refresh) {
          lcd.print("CHANNEL 1 OFF ");
          lcd.setCursor(0,1);
          lcd.write(2);
          lcd.setCursor(2,1);
          lcd.print("08:30");
          lcd.setCursor(8,1);
          lcd.write(3);
          lcd.setCursor(10,1);
          lcd.print("16:30");
        } else {
          lcd.print("CHANNEL 2 ON ");
          lcd.setCursor(0,1);
          lcd.write(2);
          lcd.setCursor(2,1);
          lcd.print("08:00");
          lcd.setCursor(8,1);
          lcd.write(3);
          lcd.setCursor(10,1);
          lcd.print("17:00");
          lastSelected = "channel2";
        }
      }
    break;
  }
}

void displaySelect() {

  if (lastSelected.equals("plug1")) {
    toggleRelay(relay1);
  } else if (lastSelected.equals("plug2")) {
    toggleRelay(relay2);
  } else if (lastSelected.equals("plug3")) {
    toggleRelay(relay3);
  }

  displaySwitch(true);
  delay(250);
}

void displayIlumination(boolean next) {
  if (next) {
    clearDisplay();
    lcd.setCursor(0,0);
    lcd.print("ILUMINATION");
}
}

void displayPlugs(boolean next) {
  if (next) clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("PLUGS");
}

void displayTemp(boolean next) {
  if (next) clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("TEMPERATURE");
}

void displayHome() {
//  clearDisplay();
    lcd.setCursor(0,0);
    lcd.print(clockDateTime());
    lcd.setCursor(0,1);
    lcd.write(0);
    lcd.setCursor(1,1);
    lcd.print(temp()); 
    lcd.setCursor(6,1);
    lcd.write(1);
    lcd.setCursor(7,1);
    lcd.print("C"); 
}

void turnDisplayOn() {
  lcd.backlight();
}

void turnDisplayOff() {
  lcd.noBacklight();
}

void clearDisplay() {
  lcd.clear();
}

void Hello ()                     // imprimindo mensagem
{
  lcd.setCursor(0, 0);            // selecionando coluna 0 e linha 0
  lcd.print("Blog ELETROGATE");   // print da mensagem
  lcd.setCursor(2, 1);            // selecionando coluna 2 e linha 1
  lcd.print("Guia do LCD");       // Print da mensagem
  delay(1000);                    // atraso de 1 segundo
}

void Flash ()
{
  lcd.noDisplay();                // desliga display
  delay(1000);                    // atraso de meio segundo
  lcd.display();                  // liga display
  delay(1000);                    // atraso de meio segundo
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

void Blink ()                     // teste do cursor
{
  lcd.noBlink();                  // apaga cursor
  delay(1000);                    // atraso de 1 segundo
  lcd.blink();                    // acende cursor
  delay(1000);                    // atraso de 1 segundo
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

void AutoScroll ()                // teste de rolagem de mensagem
{
  lcd.setCursor(16, 1);           // selecionando coluna 16 e linha 1
  lcd.autoscroll();               // configura rolagem automatica de mensagem
  for (thisChar = 0; thisChar < 10; thisChar++)     // imprime de 0 a 9
  {
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  lcd.noAutoscroll();             // desliga rolagem autoamtica
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

void dirText ()                   // teste de direcao de mensagem
{
  lcd.clear();                    // limpa a tela
  lcd.cursor();                   // liga o cursor
  lcd.setCursor(10, 0);           // selecionando coluna 10 e linha 1
  for (thisChar = 1; thisChar < 10; thisChar++)     // imprime de 1 a 9
  {
    lcd.rightToLeft();            // imprime da direita para a esquerda
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  for (thisChar = 1; thisChar < 10; thisChar++)     // imprime de 1 a 9
  {
    lcd.leftToRight();            // imprime da esquerda para a direita
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  lcd.noCursor();                 // desliga o cursor
}
