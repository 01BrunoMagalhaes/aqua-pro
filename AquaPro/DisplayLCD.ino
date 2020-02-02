LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configura endereço I2C e display com 16 caracteres e 2 linhas 
int thisChar = 0 ;

// Custom Character Generator http://omerk.github.io/lcdchargen/
byte thermometer[8] = {0b00100,0b01010,0b01010,0b01110,0b01110,0b11111,0b11111,0b01110};

byte customChar[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b01010,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};

void initializeDisplay() {
  lcd.init();                      // inicializa LCD
  turnDisplayOn();

  lcd.createChar(0, thermometer);         // criando o caracter especial 1
  lcd.createChar(1, customChar);
}

void displayHome() {
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
