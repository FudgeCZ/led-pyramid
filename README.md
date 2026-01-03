### [**LED_pyramid.ino**](https://github.com/FudgeCZ/led-pyramid/blob/main/LED_pyramid.ino) **= Hlavní program**
### [**LED_pyramid_test.ino**](https://github.com/FudgeCZ/led-pyramid/blob/main/LED_pyramid_test.ino) **= Program pro testování funkčnosti**
### [**display-holder.f3d**](https://github.com/FudgeCZ/led-pyramid/blob/main/display-holder.f3d) **= 3D model pro úpravy v Autodesk Fusion**
### [**display-holder.stl**](https://github.com/FudgeCZ/led-pyramid/blob/main/display-holder.stl) **= 3D model pro výtisk**

# Ročníková práce MET - Svítící LED pyramida

- Jméno : Novák František

- Třída : MET4

<img width="900" height="548" alt="image" src="https://github.com/user-attachments/assets/e040081d-c241-40d7-a369-b35a0420dec0" />


## Obsah

[Úvod do projektu](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#úvod-do-projektu)

[Co je to a princip](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#co-je-to-a-princip)

[Hlavní cíl projektu](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#hlavní-cíl-projektu)

[Použité komponenty](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#použité-komponenty)

[Mechanická konstrukce a 3D tisk](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#mechanická-konstrukce-a-3d-tisk)

[Elektrické zapojení](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#elektrické-zapojení)

[Ovládání a režimy](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#ovládání-a-režimy)

[Pájení](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#pájení)

[Testování funkcí](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#testování-funkcí)

[Výsledné zařízení](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#výsledné-zařízení)

[Závěr](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#závěr)

[Zdroje](https://github.com/FudgeCZ/led-pyramid/tree/main?tab=readme-ov-file#zdroje)

## **_Úvod do projektu:_**

Pro svou ročníkovou práci jsem si zvolil **svítící LED pyramidu**. Hlavním důvodem mého výběru byla snaha vytvořit zařízení, které je vizuálně atraktivním projektem a zároveň i zajímavý a naučný.

Tento projekt pro mě představoval ideální výzvu, protože kombinuje: návrh zapojení součástek, manuální zručnost při konstrukci pyramidy, a tvorbu programu pro Arduino. Zvláštní motivací pro mě byla práce s moderními komponenty, jako je Arduino Nano s rozhraním USB-C, a implementace uživatelského rozhraní pomocí LCD displeje.


## **_Co je to a princip:_**

Svítící LED pyramida je elektronický dekorativní prvek, který slouží jako ukázka možností řízení světelných diod pomocí Arduina. Konstrukčně se jedná o 2D objekt ve tvaru jehlanu, který je osazen devatenácti LED diodami. Celé zařízení je řízeno vývojovou deskou Arduino Nano, která tvoří „mozek" celého systému.

Princip funkce je založen na cyklickém provádění hlavní smyčky programu (_loop_), která neustále monitoruje vstupy a řídí výstupy. Zařízení funguje na principu stavového automatu, kde proměnná _režim_ určuje, která animace se má právě vykonávat. Ovládání je zajištěno tlačítkem připojeným na digitální vstup. Aby zařízení reagovalo na stisk tlačítka okamžitě i v průběhu animací, je v kódu implementována speciální funkce _cekejBezpecne_. Ta nahrazuje běžné čekání (_delay_) a v krátkých intervalech kontroluje stav tlačítka, což umožňuje plynulé přepínání režimů bez nutnosti čekat na dokončení světelného efektu.

Vizuální efekty jsou vytvářeny spínáním digitálních pinů, ke kterým jsou diody připojeny. Pro pokročilé efekty, jako je „pulzování" (plynulé rozsvěcení a zhasínání), využívá zařízení metodu softwarové pulsní šířkové modulace (PWM). Protože digitální piny umí standardně jen stavy zapnuto/vypnuto, program velmi rychle střídá tyto stavy v různých poměrech, čímž pro lidské oko vytváří iluzi změny jasu. O aktuálním stavu, názvu animace a číslu režimu je uživatel informován prostřednictvím LCD displeje, který s procesorem komunikuje přes sběrnici I2C.

## **_Hlavní cíl projektu:_**

Hlavním cílem této ročníkové práce bylo navrhnout a sestavit komplexní elektronické zařízení. Cílem nebylo pouze rozblikat diodu, ale vytvořit systém s uživatelským rozhraním. Tento hlavní záměr lze rozdělit do několika konkrétních technických a vzdělávacích cílů:

- **Programování v Arduino IDE:** Osvojit si práci s poli (arrays) pro efektivní správu většího množství pinů a pochopit logiku neblokujícího kódu. Důležitým cílem bylo naprogramovat systém tak, aby animace byly plynulé a ovládání responzivní.
- **Implementace komunikačních protokolů:** Naučit se pracovat s knihovnou LiquidCrystal_I2C a zprovoznit komunikaci mezi arduinem a displejem pouze pomocí dvou datových vodičů (SDA, SCL).
- **Tvorba algoritmů:** Naprogramovat sekvence animací, jako je „Zleva doprava", střídání sudých a lichých řad nebo náhodný výběr efektů.
- **Finalizace produktu:** Dotáhnout projekt do podoby, kdy je mechanicky stabilní (využití 3D tisku pro držáky displeje) a spolehlivě funguje při opakovaném použití.


## **_Použité komponenty:_**

Pro realizaci zařízení byly vybrány následující klíčové součástky:

- **Arduino Nano (USB-C):** Kompaktní vývojová. Zvolena pro své malé rozměry vhodné do nepájivého pole a moderní USB-C konektor.

  <img width="353" height="214" alt="image" src="https://github.com/user-attachments/assets/f9706c00-d4c8-4ef6-8200-14ad2e74c874" />

- **LED diody (19 ks):** 5mm diody, které tvoří vizuální část projektu.

  <img width="352" height="198" alt="image" src="https://github.com/user-attachments/assets/03625dfa-ecf0-4a26-a5f3-3bdc73a94962" />

- **LCD Displej 1602 s I2C převodníkem:** Zobrazuje textové informace (2 řádky po 16 znacích). Díky I2C modulu vyžaduje pouze 2 datové piny (A5/A6).

  <img width="391" height="220" alt="image" src="https://github.com/user-attachments/assets/70f2d0dc-bc25-4c35-94cf-b51aaff9c7cb" /> <img width="387" height="218" alt="image" src="https://github.com/user-attachments/assets/b1c476d4-4d1b-4c03-8ab7-55e01e6f7d67" />

- **Rezistory (220 Ω - 9 ks):** Ochranné prvky zapojené v sérii k LED diodám pro omezení proudu.

  <img width="357" height="201" alt="image" src="https://github.com/user-attachments/assets/f8d84537-7f3c-4765-b744-9b4fc7a624c3" />

- **Tlačítko:** Slouží k přepínání režimů.

  <img width="238" height="200" alt="image" src="https://github.com/user-attachments/assets/fc57c152-f210-4e84-b9b7-62c38e1ea352" />

- **Nepájivé pole a propojovací vodiče:** Pro flexibilní sestavení obvodu.

## **_Mechanická konstrukce a 3D tisk:_**

Mechanická stránka projektu se skládá ze dvou hlavních částí: samotné pyramidy a upevnění displeje.

- **Konstrukce pyramidy:** Pyramida je sestavena pomocí prostorového pájení. Diody drží pohromadě díky spájeným vývodům (katody a anody), které tvoří pevnou mřížku.
- **3D Tisk:** Aby LCD displej pevně držel na nepájivém poli a byl v dobré poloze pro čtení, navrhl jsem a vytiskl speciální plastové nožičky zasouvací do nepájivého pole pro stabilitu. Ty zajišťují lepší čitelnost displeje a hezčí vzhled celého zařízení.
<img width="289" height="272" alt="image" src="https://github.com/user-attachments/assets/008942f8-f305-41c3-bfdd-1a9ea6424820" />

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

Režimy se dají jednoduše přidat a upravit, stačí přidat funkce a text pro displej.

**Seznam naprogramovaných režimů:**

- **Režim 0 (Vypnuto):** Všechny LED zhasnou, zařízení čeká.

  <img width="475" height="259" alt="image" src="https://github.com/user-attachments/assets/81b2bd9d-f86a-4779-bac5-7fd434642880" />
  
- **Režim 1 (Zleva doprava):** Postupné rozsvěcení a zhasínání řad diod z jedné strany na druhou.

  <img width="482" height="267" alt="image" src="https://github.com/user-attachments/assets/12887646-4b59-48ff-a5c9-b0788e17c4a5" />

- **Režim 2 (Zprava doleva):** Inverzní animace k režimu 1.

  <img width="486" height="272" alt="image" src="https://github.com/user-attachments/assets/17f0594d-17a0-4466-b293-70f59127f01b" />

- **Režim 3 (Střed -> Ven):** Efekt, kdy se světlo šíří od prostředního sloupce směrem k okrajům.

  <img width="483" height="261" alt="image" src="https://github.com/user-attachments/assets/7403a35b-9409-4600-8ddc-5919372c7fc7" />

- **Režim 4 (Ven -> Střed):** Světlo se "stahuje" z okrajů do středu pyramidy.

  <img width="484" height="287" alt="image" src="https://github.com/user-attachments/assets/3b4f9506-37a3-4ac3-ba85-bf52c22120eb" />

- **Režim 5 (Pulzování):** Speciální režim využívající softwarové PWM (rychlé spínání signálů). Jas diod se plynule zvyšuje a snižuje (tzv. "dýchání"). Program toho docílí rychlým spínáním diod v cyklech s proměnlivou délkou svitu (_delayMicroseconds_).

  <img width="418" height="241" alt="image" src="https://github.com/user-attachments/assets/37e2527d-66b1-42c8-9f27-2d76c1a96c86" /> <img width="417" height="242" alt="image" src="https://github.com/user-attachments/assets/08a275ac-24a1-458b-9b1a-24aedb8b0f9e" />


- **Režim 6 (Sudé / Liché):** Střídavé blikání sudých a lichých sekcí diod.

  <img width="422" height="243" alt="image" src="https://github.com/user-attachments/assets/244360a9-67e1-46cd-8d42-33668f686b23" /> <img width="420" height="243" alt="image" src="https://github.com/user-attachments/assets/aa5eb5c5-9906-476f-a179-14d2ccd093eb" />


- **Režim 7 (Automaticky):** Přehrává pevnou sekvenci animací za sebou.
  - 3x Zleva-doprava - tam a zpátky
  - 3x Pulzování
  - 3x Od středu do stran - tam a zpátky
  - 6x Sudé a liché
  - Zpět na 1…

  <img width="478" height="270" alt="image" src="https://github.com/user-attachments/assets/4783da42-a84a-4330-bc80-bf73f95f3c48" />

- **Režim 8 (Náhodně):** Arduino náhodně vybírá animace (1-6) a přehrává je, čímž zajišťuje neopakující se podívanou.

  <img width="477" height="279" alt="image" src="https://github.com/user-attachments/assets/95b2431f-4fb1-47fa-915d-c7433aba83ab" />

- **Režim 9 (Svítí vše):** Trvalé rozsvícení všech diod.
  
  <img width="478" height="288" alt="image" src="https://github.com/user-attachments/assets/e8f0e1c9-9b36-4cea-a60f-e11db1d19c47" />

## **_Pájení:_**

Náročnější částí byla konstrukce samotné pyramidy. Postupoval jsem metodou pájení "ve vzduchu" podle předem připraveného plánu, aby diody tvořily požadovaný tvar. Postup pájení jednotlivých pater a sekcí:

- 2x LED samostatně.

  <img width="269" height="151" alt="image" src="https://github.com/user-attachments/assets/8264da8d-25fb-470b-83f6-41b392b2d5ed" />

- Spojení 2x zkrácené LED s další LED.

  <img width="270" height="152" alt="image" src="https://github.com/user-attachments/assets/ffb501e3-8343-4add-9837-fe60acb9d94e" />

- Spojení 2x LED s další LED.

  <img width="273" height="154" alt="image" src="https://github.com/user-attachments/assets/2071e229-959b-4045-ac6d-45565c3c55b0" />

- Spojení 2x zkrácené LED s dvěma dalšími LED.

  <img width="291" height="164" alt="image" src="https://github.com/user-attachments/assets/9a8d5023-16c8-4b8b-903b-3f6f5f52a9b7" />

- Finální vrchol tvořený 3 LED na sobě.

  <img width="311" height="175" alt="image" src="https://github.com/user-attachments/assets/59f93947-4b48-4cc4-9b7d-58edfce9a322" />

## **_Testování funkcí:_**

Po dokončení zapojení a sestavení zařízení následuje testování. K dispozici je i testovací program _LED_pyramid_test.ino (viz. Zdroje)_

- **Test napájení:** První zapojení do USB. Kontrola, zda se nerozžhaví žádná součástka a zda svítí kontrolka na Arduinu.
- **Test LED diod:** Nahrání jednoduchého kódu, který rozsvítí všechny piny _ledPins_, aby se ověřilo, zda jsou všechny diody připájeny správně a nejsou špatně dané póly.
- **Test I2C Displeje:** Ověření adresy displeje (standardně 0x27) a nastavení kontrastu potenciometrem na zadní straně modulu, aby byl text čitelný.
- **Test Logiky a Tlačítka:** Zde jsem narazil na problém s odezvou tlačítka během dlouhých animací. Vyřešil jsem to implementací funkce _cekejBezpecne()_, která kontroluje tlačítko i během čekání v animaci. Pokud je stisknuto, animace se okamžitě přeruší (return) a přepne se režim.


## **_Výsledné zařízení:_**

Po dokončení všech fázích - od prvotního návrhu a 3D tisku, přes pájení konstrukce, až po finální programování a ladění - vzniklo plně funkční dekorativní zařízení. Výsledný produkt splňuje všechny předem stanovené cíle a funguje spolehlivě.

<img width="497" height="279" alt="image" src="https://github.com/user-attachments/assets/d193355c-bd7d-4e75-8dd5-9334a10f8526" />

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

[github.com/johnrickman/LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

**Kód a 3D model na zkopírování:**

[**github.com/FudgeCZ/led-pyramid**](https://github.com/FudgeCZ/led-pyramid)

Po otevření odkazu se objeví soubor **_LED_pyramida.ino_**, kde je vidět kód

Soubory **_display-holder_** f3d a stl jsou 3D modely (**f3d** - soubor pro Autodesk Fusion pro upravení modelu; **stl** - soubor pro vytištění)
