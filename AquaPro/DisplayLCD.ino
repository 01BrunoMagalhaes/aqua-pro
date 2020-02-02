LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configura endereço I2C e display com 16 caracteres e 2 linhas 
int thisChar = 0 ;
String lastScreen = "home";
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

  displayData("home");
}

void displayData(String screen) {
  Serial.print(F("Screen: ")); Serial.print(screen); Serial.print(F(" lastScreen: ")); Serial.print(lastScreen);

  if (screen.equals("") || screen.equals("home")) {
    displayHome();
    lastScreen = "home";
  } else if (verifyLastAndNext("home", screen)) {
    displayPlugs();
    lastScreen = "plugs";
  } else if (verifyLastAndNext("plugs", screen)) {
    displayTemp();
    lastScreen = "temp";
  } else if (verifyLastAndNext("temp", screen)) {
    displayIlumination();
    lastScreen = "ilumination";
  } else if (verifyLastAndNext("ilumination", screen)) {
    displayHome();
    lastScreen = "home";
  }

  lastSelected = "";
}

void displayIlumination() {
  clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("ILUMINATION");
}

void displayPlugs() {
  clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("PLUGS");
}

void displayTemp() {
  clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("TEMPERATURE");
}

boolean verifyLastAndNext(String last, String screen) {
  return lastScreen.equals(last) && screen.equals("next");
}

void displaySwitch() {

  if (lastScreen.equals("temp")) {
    displayTemp();
    
    if (lastSelected.equals("ideal")) {
      lcd.setCursor(0,1);
      lcd.print("MINIMUM 26.0");
      lastSelected = "min"; 
    } else if (lastSelected.equals("min")) {
      lcd.setCursor(0,1);
      lcd.print("MAXIMUM 27.0");
      lastSelected = "max"; 
    } else {
      lcd.setCursor(0,1);
      lcd.print("IDEAL 26.5");
      lastSelected = "ideal";
    }
    
  } else if (lastScreen.equals("plugs")) {
    displayPlugs();

    if (lastSelected.equals("plug1")) {
      lcd.setCursor(0,1);
      lcd.print("2 OFF");
      lastSelected = "plug2";
    } else if (lastSelected.equals("plug2")) {
      lcd.setCursor(0,1);
      lcd.print("3 OFF");
      lastSelected = "plug3";
    } else {
      lcd.setCursor(0,1);
      lcd.print("1 OFF");
      lastSelected = "plug1";
    }
  
  } else if (lastScreen.equals("ilumination")) {
    clearDisplay();
    lcd.setCursor(0,0);

    if (lastSelected.equals("channel1")){
      lcd.print("CHANNEL 2 ON");
      lcd.setCursor(0,1);
      lcd.write(2);
      lcd.setCursor(2,1);
      lcd.print("08:00");
      lcd.setCursor(8,1);
      lcd.write(3);
      lcd.setCursor(10,1);
      lcd.print("17:00");
      lastSelected = "channel2";
    } else {
      lcd.print("CHANNEL 1 OFF");
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
    
  }
  
}

void displayHome() {
  clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("02/02/20 13:06");
  lcd.setCursor(0,1);
  lcd.write(0);
  lcd.setCursor(1,1);
  lcd.print("26.30"); 
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
