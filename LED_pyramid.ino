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
// 1-6 = Animace
// 7 = Automaticky (Pevná sekvence)
// 8 = Náhodně (Bez opakování)
// 9 = Svítí vše
int rezim = 0; // Výchozí režim při zapnutí
int maxRezim = 9; 

int rychlost = 100; // Čím vyšší tím pomalejší
int pauzaKonec = 150; 

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
    case 2: animaceZpravaDoleva(); break;
    case 3: animaceStredDoStran(); break;
    case 4: animaceStranyDoStredu(); break;
    case 5: animacePulzovani(); break;
    case 6: animaceSudeLiche(); break;
    case 7: animaceAutomatickyPevna(); break; 
    case 8: animaceNahodne(); break;          
    case 9: rozsvititVse(); delay(10); break; 
  }
}

// --- FUNKCE PRO LCD DISPLEJ ---
void aktualizujDisplej() {
  lcd.clear(); 
  
  lcd.setCursor(0, 0); 
  lcd.print("REZIM: ");
  lcd.print(rezim);
  
  lcd.setCursor(0, 1); 
  
  switch(rezim) {
    case 0: lcd.print("VYPNUTO"); break;
    case 1: lcd.print("ZLEVA DO PRAVA"); break;
    case 2: lcd.print("ZPRAVA DO LEVA"); break;
    case 3: lcd.print("STRED -> VEN"); break;
    case 4: lcd.print("VEN -> STRED"); break;
    case 5: lcd.print("PULZOVANI"); break;
    case 6: lcd.print("SUDE / LICHE"); break;
    case 7: lcd.print("AUTOMATICKY"); break; 
    case 8: lcd.print("NAHODNE"); break;     
    case 9: lcd.print("SVITI VSE"); break;
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

// ----- ANIMACE -----

// --- REŽIM 1: Zleva doprava ---
void animaceZlevaDoprava() {
  for (int i = pocetLed - 1; i >= 0; i--) { digitalWrite(ledPins[i], HIGH); if (cekejBezpecne(rychlost)) return; }
  for (int i = pocetLed - 1; i >= 0; i--) { digitalWrite(ledPins[i], LOW); if (cekejBezpecne(rychlost)) return; }
}

// --- REŽIM 2: Zprava doleva ---
void animaceZpravaDoleva() {
  for (int i = 0; i < pocetLed; i++) { digitalWrite(ledPins[i], HIGH); if (cekejBezpecne(rychlost)) return; }
  for (int i = 0; i < pocetLed; i++) { digitalWrite(ledPins[i], LOW); if (cekejBezpecne(rychlost)) return; }
}

// --- REŽIM 3: Od středu do stran ---
void animaceStredDoStran() {
  int stred = 4; 
  for (int i = 0; i <= 4; i++) {
    digitalWrite(ledPins[stred - i], HIGH); digitalWrite(ledPins[stred + i], HIGH);
    if (cekejBezpecne(rychlost)) return;
  }
  for (int i = 0; i <= 4; i++) {
    digitalWrite(ledPins[stred - i], LOW); digitalWrite(ledPins[stred + i], LOW);
    if (cekejBezpecne(rychlost)) return;
  }
  if (cekejBezpecne(pauzaKonec)) return;
}

// --- REŽIM 4: Od stran do středu ---
void animaceStranyDoStredu() {
  for (int i = 0; i <= 4; i++) {
    digitalWrite(ledPins[i], HIGH); digitalWrite(ledPins[8 - i], HIGH);     
    if (cekejBezpecne(rychlost)) return;
  }
  for (int i = 0; i <= 4; i++) {
    digitalWrite(ledPins[i], LOW); digitalWrite(ledPins[8 - i], LOW);
    if (cekejBezpecne(rychlost)) return;
  }
  if (cekejBezpecne(pauzaKonec)) return;
}

// --- REŽIM 5: Pulzování ---
void animacePulzovani() {
  int krokStmivani = 1; 
  for (int jas = 0; jas <= 50; jas += krokStmivani) {
    for (int t = 0; t < 15; t++) { 
       rozsvititVse(); 
       delayMicroseconds(jas * 30);        
       vypnoutVse();
       delayMicroseconds((50 - jas) * 50); 
       if (kontrolaTlacitka()) return; 
    }
  }
  for (int jas = 50; jas >= 0; jas -= krokStmivani) {
    for (int t = 0; t < 15; t++) { 
       rozsvititVse();
       delayMicroseconds(jas * 30);        
       vypnoutVse();
       delayMicroseconds((50 - jas) * 50); 
       if (kontrolaTlacitka()) return; 
    }
  }
  if (cekejBezpecne(100)) return;
}

// --- REŽIM 6: Sudé/liché ---
void animaceSudeLiche() {
  for (int i = 0; i < pocetLed; i++) {
    if (i % 2 == 0) digitalWrite(ledPins[i], HIGH);
    else digitalWrite(ledPins[i], LOW);
  }
  if (cekejBezpecne(rychlost * 4)) return;

  for (int i = 0; i < pocetLed; i++) {
    if (i % 2 == 0) digitalWrite(ledPins[i], LOW);
    else digitalWrite(ledPins[i], HIGH);
  }
  if (cekejBezpecne(rychlost * 4)) return;
}

// --- REŽIM 7: PEVNÁ SEKVENCE ---
void animaceAutomatickyPevna() {
  
  // 1. ČÁST: LEVÁ/PRAVÁ (3x tam a zpět)
  for(int i=0; i<3; i++) {
    animaceZlevaDoprava(); 
    if (rezim != 7) return; 
    
    animaceZpravaDoleva(); 
    if (rezim != 7) return;
  }

  // 2. ČÁST: 3x PULZ
  for(int i=0; i<3; i++) {
    animacePulzovani();
    if (rezim != 7) return;
  }

  // 3. ČÁST: STŘED/STRANY (3x ven a dovnitř)
  for(int i=0; i<3; i++) {
    animaceStredDoStran();   
    if (rezim != 7) return;

    animaceStranyDoStredu(); 
    if (rezim != 7) return;
  }

  // 4. ČÁST: 6x SUDÉ/LICHÉ
  for(int i=0; i<6; i++) {
    animaceSudeLiche();
    if (rezim != 7) return;
  }

  // KONEC CYKLU - Vše zhasnout
  vypnoutVse();
  if (cekejBezpecne(500)) return; 
}

// --- REŽIM 8: NÁHODNĚ ---
void animaceNahodne() {
  static int vybranyEfekt = 0;
  static int pocetOpakovani = 0;
  static int minulyEfekt = 0; 

  if (pocetOpakovani == 0) {
    do {
      vybranyEfekt = random(1, 7); 
    } while (vybranyEfekt == minulyEfekt);
    
    minulyEfekt = vybranyEfekt;
  }

  switch(vybranyEfekt) {
    case 1: animaceZlevaDoprava(); break;
    case 2: animaceZpravaDoleva(); break;
    case 3: animaceStredDoStran(); break;
    case 4: animaceStranyDoStredu(); break;
    case 5: animacePulzovani(); break;
    case 6: animaceSudeLiche(); break;
  }
  
  vypnoutVse(); 

  pocetOpakovani++;
  if (pocetOpakovani >= 3) { 
    pocetOpakovani = 0;
  }
}

// --- POMOCNÉ FUNKCE ---
void vypnoutVse() { for (int i = 0; i < pocetLed; i++) digitalWrite(ledPins[i], LOW); }
void rozsvititVse() { for (int i = 0; i < pocetLed; i++) digitalWrite(ledPins[i], HIGH); }
