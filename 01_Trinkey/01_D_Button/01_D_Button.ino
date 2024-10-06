#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL  6  // Definiert wo die Bauteile angesteckt sind.
#define PIN_SWITCH   12  // Braucht man nur im Simulator!

#define NUMPIXELS     1  // Definiert wieviele LEDs wir haben

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


// Wird einmal beim Start aufgerufen.
void setup() {  
  Serial.begin(115200);              // Startet die Debug-Verbindung
  pixels.begin();                    // Startet die LED-Schnittstelle
  pinMode(PIN_SWITCH, INPUT_PULLUP); // Startet den Button
}

// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft den Status des Buttons ab
  if (digitalRead(PIN_SWITCH)) {
    // Button ist nicht gedrückt: Nichts tun
  } else {
    // Button ist gedrückt: Setze die Farbe der LED auf einen zufälligen Wert
    pixels.fill(pixels.Color(
      random(0, 255),
      random(0, 255),
      random(0, 255)
    ));
  }

  // Aktualisiert die LED
  pixels.show();

  // Hält das Programm 200 Millisekunden an
  delay(200);
}