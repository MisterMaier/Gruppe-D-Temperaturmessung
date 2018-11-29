//Autor: Gschaider, Hubmann, Maier
//Datum:
//Aufgabe:Wenn der Button gedrückt wird, wird die Temperatur gemessen und auf einem LCD per I2C ausgegeben(2 Sekunden lange, es sei der Button bleibt gedrückt, ann länger).
//Ist der Button nicht gedrückt ist am Display nichts zu sehen.

//----------------Librarys--------------
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//---------------Display zuordnen-----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

//--------------Globale Variablen deklarieren-------------
int sensorPin = A0;
int buttonState;
const int buttonPin = 2;
int counter = 1;

void setup() {
//------------LCD-Display initialisieren und starten-------------
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();

//-------------ButtonPin Pinmoden---------------
  pinMode(buttonPin, INPUT);
}

void loop() {
  //-----------Button einlesen um Starten zu können-----------
  buttonState = digitalRead(buttonPin);

//-----------Wenn Button gedrückt, Einlesen und Ausgabe starten---------------
  if (buttonState == true)
  {
    float celsius = ((5 * (analogRead(sensorPin)) * 100) / 1024);
    
//-----------Die Ausgabe erfolgt mit I2C auf einem LC-Display--------------
    lcd.setCursor(0, 0);    //Position: Reihe 0 Spalte 0
    lcd.print(celsius);     //Der eingelesene Wert wird ausgegeben
    lcd.print(char(223));   //char(223) ist das Gradzeichen °
    lcd.print("C");
    lcd.setCursor(0, 1);    //Position: Reihe 1 Spalte 0
    lcd.print(counter);     //Gibt an, der wie vielte Messwert gezeigt wird
    delay(2000);            //Ein Delay damit das Ergebnis länger sichtbar ist.
    counter = counter + 1;  //Zählt die Messdurchläufe
    lcd.clear();            //Ergebnis wird vom Display gelöscht
  }

//-------------Den Counter wieder auf 1 zurücksetzen---------------
  if (buttonState == false)
  {
    counter = 1;//Der counter wird zurück gesetzt.
  }
}

