#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- NASTAVENÍ DISPLEJE ---
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// --- NASTAVENÍ PINŮ ---
int ledPins[] = {12, 11, 10, 9, 8, 7, 6, 5, 4}; 
int pocetLed = 9;
int buttonPin = 2; 

// Režimy
// 0 = Vypnuto
// 1 = Zleva doprava
// 2 = Všechny
int rezim = 0; 
int maxRezim = 2; 

int rychlost = 100;   
int pauzaKonec = 200; 

void setup() {
  // LED
  for (int i = 0; i < pocetLed; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Tlačítko
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializace náhodných čísel
  randomSeed(analogRead(A0));

  // START DISPLEJE
  lcd.init();      
  lcd.backlight(); 
  
  aktualizujDisplej();
}

void loop() {
  kontrolaTlacitka(); 

  switch (rezim) {
    case 0: vypnoutVse(); delay(10); break;
    case 1: animaceZlevaDoprava(); break;         
    case 2: rozsvititVse(); delay(10); break; 
  }
}

// --- FUNKCE PRO LCD DISPLEJ ---
void aktualizujDisplej() {
  lcd.clear(); 
  
  lcd.setCursor(0, 0); 
  lcd.print("REZIM: ");
  lcd.print(rezim);
  lcd.print("  Test mód");
  
  lcd.setCursor(0, 1); 
  
  switch(rezim) {
    case 0: lcd.print("VYPNUTO"); break;
    case 1: lcd.print("ZLEVA DO PRAVA"); break;    
    case 2: lcd.print("SVITI VSE"); break;
  }
}


// --- OVLÁDÁNÍ ---
bool kontrolaTlacitka() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50); 
    if (digitalRead(buttonPin) == LOW) {
      rezim++;
      if (rezim > maxRezim) rezim = 0; 
      
      vypnoutVse(); 
      aktualizujDisplej(); 
      
      while (digitalRead(buttonPin) == LOW) delay(10);
      return true; 
    }
  }
  return false; 
}

bool cekejBezpecne(int casMs) {
  int kroky = casMs / 10; 
  for (int k = 0; k < kroky; k++) {
    delay(10);
    if (kontrolaTlacitka()) return true; 
  }
  return false;
}

void animaceZlevaDoprava() {
  for (int i = pocetLed - 1; i >= 0; i--) { digitalWrite(ledPins[i], HIGH); if (cekejBezpecne(rychlost)) return; }
  for (int i = pocetLed - 1; i >= 0; i--) { digitalWrite(ledPins[i], LOW); if (cekejBezpecne(rychlost)) return; }
}

// --- POMOCNÉ FUNKCE ---
void vypnoutVse() { for (int i = 0; i < pocetLed; i++) digitalWrite(ledPins[i], LOW); }
void rozsvititVse() { for (int i = 0; i < pocetLed; i++) digitalWrite(ledPins[i], HIGH); }