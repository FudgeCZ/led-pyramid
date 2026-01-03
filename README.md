# Ročníková práce - Svítící LED pyramida

- Jméno : Novák František

- Třída : MET4

<img width="940" height="529" alt="image" src="https://github.com/user-attachments/assets/f1aac288-7a88-4180-be98-3ab10e3ecfb2" />


## **_Úvod do projektu:_**

Pro svou ročníkovou práci jsem si zvolil **svítící LED pyramidu**. Hlavním důvodem mého výběru byla snaha vytvořit zařízení, které je vizuálně atraktivním projektem a zároveň i zajímavý a naučný.

Tento projekt pro mě představoval ideální výzvu, protože kombinuje několik klíčových disciplín: od návrhu zapojení součástek, přes manuální zručnost při konstrukci pyramidy, až po tvorbu programu pro Arduino. Zvláštní motivací pro mě byla práce s moderními komponenty, jako je Arduino Nano s rozhraním USB-C, a implementace uživatelského rozhraní pomocí LCD displeje.

## **_Co je to a princip:_**

Svítící LED pyramida je elektronický dekorativní prvek, který slouží jako ukázka možností řízení světelných diod pomocí Arduina. Konstrukčně se jedná o 2D objekt ve tvaru jehlanu, který je osazen devatenácti LED diodami. Celé zařízení je řízeno vývojovou deskou Arduino Nano, která tvoří „mozek" celého systému.

Princip funkce je založen na cyklickém provádění hlavní smyčky programu (_loop_), která neustále monitoruje vstupy a řídí výstupy. Zařízení funguje na principu stavového automatu, kde proměnná _režim_ určuje, která animace se má právě vykonávat. Ovládání je zajištěno tlačítkem připojeným na digitální vstup. Aby zařízení reagovalo na stisk tlačítka okamžitě i v průběhu animací, je v kódu implementována speciální funkce _cekejBezpecne_. Ta nahrazuje běžné čekání (_delay_) a v krátkých intervalech kontroluje stav tlačítka, což umožňuje plynulé přepínání režimů bez nutnosti čekat na dokončení světelného efektu.

Vizuální efekty jsou vytvářeny spínáním digitálních pinů, ke kterým jsou diody připojeny. Pro pokročilé efekty, jako je „pulzování" (plynulé rozsvěcení a zhasínání), využívá zařízení metodu softwarové pulsní šířkové modulace (PWM). Protože digitální piny umí standardně jen stavy zapnuto/vypnuto, program velmi rychle střídá tyto stavy v různých poměrech, čímž pro lidské oko vytváří iluzi změny jasu. O aktuálním stavu, názvu animace a číslu režimu je uživatel informován prostřednictvím LCD displeje, který s procesorem komunikuje přes sběrnici I2C.

## **_Hlavní cíl projektu:_**

Hlavním cílem této ročníkové práce bylo navrhnout a sestavit komplexní elektronické zařízení. Cílem nebylo pouze rozblikat diodu, ale vytvořit systém s uživatelským rozhraním. Tento hlavní záměr lze rozdělit do několika konkrétních technických a vzdělávacích cílů:

- **Programování v Arduino IDE:** Osvojit si práci s poli (arrays) pro efektivní správu většího množství pinů a pochopit logiku neblokujícího kódu. Důležitým cílem bylo naprogramovat systém tak, aby animace byly plynulé a ovládání responzivní.
- **Implementace komunikačních protokolů:** Naučit se pracovat s knihovnou LiquidCrystal_I2C a zprovoznit komunikaci mezi arduinem a displejem pouze pomocí dvou datových vodičů (SDA, SCL).
- **Pájení:** Zapájet LED diody do tvaru pyramidy.
- **Tvorba algoritmů:** Naprogramovat sekvence animací, jako je „Zleva doprava", střídání sudých a lichých řad nebo náhodný výběr efektů.
- **Finalizace produktu:** Dotáhnout projekt do podoby, kdy je mechanicky stabilní (využití 3D tisku pro držáky displeje) a spolehlivě funguje při opakovaném použití.

## **_Použité komponenty:_**

Pro realizaci zařízení byly vybrány následující klíčové součástky:

- **Arduino Nano (USB-C):** Kompaktní vývojová. Zvolena pro své malé rozměry vhodné do nepájivého pole a moderní USB-C konektor.
- **LED diody (19 ks):** 5mm diody, které tvoří vizuální část projektu.
- **LCD Displej 1602 s I2C převodníkem:** Zobrazuje textové informace (2 řádky po 16 znacích). Díky I2C modulu vyžaduje pouze 2 datové piny (A5/A6).
- **Rezistory (220 Ω - 9 ks):** Ochranné prvky zapojené v sérii k LED diodám pro omezení proudu.
- **Tlačítko:** Slouží k přepínání režimů.
- **Nepájivé pole a propojovací vodiče:** Pro flexibilní sestavení obvodu.

## **_Mechanická konstrukce a 3D tisk:_**

Mechanická stránka projektu se skládá ze dvou hlavních částí: samotné pyramidy a upevnění displeje.

- **Konstrukce pyramidy:** Pyramida je sestavena pomocí prostorového pájení. Diody drží pohromadě díky spájeným vývodům (katody a anody), které tvoří pevnou mřížku.
- **3D Tisk:** Aby LCD displej pevně držel na nepájivém poli a byl v dobré poloze pro čtení, navrhl jsem a vytiskl speciální plastové nožičky zasouvací do nepájivého pole pro stabilitu. Ty zajišťují lepší čitelnost displeje a hezčí vzhled celého zařízení.

## **_Elektrické zapojení_**
<img width="498" height="440" alt="image" src="https://github.com/user-attachments/assets/86e18aa3-f8b3-4c10-874f-bcb6c8a27469" />

Zapojení je realizováno na nepájivém poli. Projekt byl nejprve zapojen v online nástroji Tinkercad, kde se jednoduše dá navrhnout a naprogramovat Arduino a další různé zařízení. Zapojení elektroniky podle schéma:

- **LED Diody:** Jsou ovládány 9 digitálními výstupy. Piny Arduina **D4** až **D12** jsou připojeny přes rezistory k jednotlivým sekcím pyramidy.
  - Pole v kódu: _int ledPins\[\] = {12, 11, 10, 9, 8, 7, 6, 5, 4};_
- **Ovládací tlačítko:** Jeden pól tlačítka je připojen na pin **D2** a druhý na zem (_GND_). V programu je aktivován interní _INPUT_PULLUP_ rezistor, takže stisk tlačítka spíná logickou nulu (_LOW_).
  - Pole v kódu: _int buttonPin = 2;_
- **LCD Displej:** Napájení (_VCC, GND_) je bráno z 5V větve Arduina. Datová komunikace probíhá přes piny A5 (_SCL_) a A6 (_SDA_) což odpovídá sběrnici I2C.
  - Pole v kódu: _LiquidCrystal_I2C lcd(0x27, 16, 2);_

## **_Ovládání a režimy:_**

Zařízení se ovládá jedním tlačítkem. Systém obsahuje celkem **10 režimů** (0-9). Při každém stisku tlačítka se hodnota proměnné režim zvýší o 1. Po dosažení čísla 9 se cyklus vrátí na 0.

**Seznam naprogramovaných režimů:**

- **Režim 0 (Vypnuto):** Všechny LED zhasnou, zařízení čeká.
- **Režim 1 (Zleva doprava):** Postupné rozsvěcení a zhasínání řad diod z jedné strany na druhou.
- **Režim 2 (Zprava doleva):** Inverzní animace k režimu 1.
- **Režim 3 (Střed -> Ven):** Efekt, kdy se světlo šíří od prostředního sloupce směrem k okrajům.
- **Režim 4 (Ven -> Střed):** Světlo se "stahuje" z okrajů do středu pyramidy.
- **Režim 5 (Pulzování):** Speciální režim využívající softwarové PWM (rychlé spínání signálů). Jas diod se plynule zvyšuje a snižuje (tzv. "dýchání"). Program toho docílí rychlým spínáním diod v cyklech s proměnlivou délkou svitu (_delayMicroseconds_).
- **Režim 6 (Sudé / Liché):** Střídavé blikání sudých a lichých sekcí diod.
- **Režim 7 (Automaticky):** Přehrává pevnou sekvenci animací za sebou.
  - 3x Zleva-doprava - tam a zpátky
  - 3x Pulzování
  - 3x Od středu do stran - tam a zpátky
  - 6x Sudé a liché
  - Zpět na 1…
- **Režim 8 (Náhodně):** Arduino náhodně vybírá animace (1-6) a přehrává je, čímž zajišťuje neopakující se podívanou.
- **Režim 9 (Svítí vše):** Trvalé rozsvícení všech diod.

## **_Pájení:_**

Nejnáročnější částí byla konstrukce samotné pyramidy. Postupoval jsem metodou pájení "ve vzduchu" podle předem připraveného plánu, aby diody tvořily požadovaný tvar. Postup pájení jednotlivých pater a sekcí:

- 2x LED samostatně.
- Spojení 2x zkrácené LED s další LED.
- Spojení 2x LED s další LED.
- Spojení 2x zkrácené LED s dvěma dalšími LED.
- Finální vrchol tvořený 3 LED na sobě.

## **_Testování funkcí:_**

Po dokončení zapojení a sestavení zařízení následuje jedna z nejdůležitějších částí - testování.  
Testování probíhá po jednotlivých krocích:

- **Test napájení:** První zapojení do USB. Kontrola, zda se nerozžhaví žádná součástka a zda svítí kontrolka na Arduinu.
- **Test LED (Hardware):** Nahrání jednoduchého kódu, který postupně rozsvítil všechny piny _ledPins_, aby se ověřilo, že jsou všechny diody připájeny správně a nejsou špatně dané póly.
- **Test I2C Displeje:** Ověření adresy displeje (standardně 0x27) a nastavení kontrastu potenciometrem na zadní straně modulu, aby byl text čitelný.
- **Test Logiky a Tlačítka:** Zde jsem narazil na problém s odezvou tlačítka během dlouhých animací. Vyřešil jsem to implementací funkce _cekejBezpecne()_, která kontroluje tlačítko i během čekání v animaci. Pokud je stisknuto, animace se okamžitě přeruší (return) a přepne se režim.

## **_Výsledné zařízení:_**

Po dokončení všech fázích - od prvotního návrhu a 3D tisku, přes pájení konstrukce, až po finální programování a ladění - vzniklo plně funkční dekorativní zařízení. Výsledný produkt splňuje všechny předem stanovené cíle a funguje spolehlivě.

**Vlastnosti hotové LED pyramidy:**

- **Kompaktní design:** Celé zařízení je sestaveno na malém nepájivém poli, přičemž dominantním prvkem je prostorová konstrukce LED diod ve tvaru pyramidy.
- **Vizuální efekty:** Zařízení nabízí celkem 10 různých provozních režimů. Animace jsou plynulé a zahrnují různé efekty např. pulzování (softwarové stmívání) a náhodné generování efektů.
- **Uživatelské rozhraní:** Díky LCD displeji má uživatel okamžitý přehled o tom, jaký režim je právě aktivní (např. nápis „PULZOVANI" nebo „NAHODNE").
- **Interaktivita:** Ovládání je řešeno jednoduše pomocí tlačítka. Zařízení reaguje okamžitě díky optimalizovanému kódu, který nečeká na dokončení animace, ale umožňuje přepnutí režimu kdykoliv.

V praxi zařízení funguje tak, že po připojení napájení (USB-C) se rozsvítí podsvícení displeje a zařízení je připraveno spustit režimy.

**Možnosti dalšího rozvoje:** Tento projekt je dobrý v tom, že je otevřený dalším úpravám. Do budoucna je možné zařízení rozšířit například o:

- Naprogramování dalších, složitějších světelných sekvencí.
- Vytvoření plošného spoje (PCB) pro přenosnou verzi napájenou např. z baterie.

## **_Závěr :_**

Cílem mé ročníkové práce bylo vytvořit „Svítící LED pyramidu", která bude plně funkční a vizuálně atraktivní. Tento cíl se podařilo splnit. Výsledné zařízení nabízí 10 různých režimů, plynulé animace a informativní displej. Během práce jsem získal cenné zkušenosti s:

- Návrhem vlastní elektronické konstrukce.
- Pokročilým programováním v C++ (práce s časováním a poli).
- Řešením problémů v reálném čase (např. ošetření tlačítka).

## **Zdroje** (_ctrl+kliknutí pro otevření odkazu_):

[wikipedia.org](https://cs.wikipedia.org)

[roboticsbackend.com/arduino-push-button-tutorial/](https://roboticsbackend.com/arduino-push-button-tutorial/)

[projecthub.arduino.cc/led-chaser-using-arduino](https://projecthub.arduino.cc/syedmahamood/led-chaser-using-arduino-uno-fdc5db)

**Kód a 3D model na zkopírování:**

[**github.com/FudgeCZ/led-pyramid**](https://github.com/FudgeCZ/led-pyramid)

Po otevření odkazu se objeví soubor **_LED_pyramida.ino_**, kde je vidět kód

Soubory **_display-holder_** f3d a stl jsou 3D modely (**f3d** - soubor pro Autodesk Fusion pro upravení modelu; **stl** - soubor pro vytištění)
