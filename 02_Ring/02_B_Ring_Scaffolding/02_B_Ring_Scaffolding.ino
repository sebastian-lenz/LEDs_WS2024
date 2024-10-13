#include <seesaw_neopixel.h>

#define NUMPIXELS     16  // Wieviele LEDs sind angeschlossen?
#define PIN_NEODRIVER 15  // An welchem PIN steckt der NeoDriver?

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUMPIXELS, PIN_NEODRIVER, NEO_GRBW + NEO_KHZ800);


// Wird einmal beim Start aufgerufen.
void setup() {  
  Serial.begin(115200);          // Startet die Debug-Verbindung
  
  while (!pixels.begin(0x60)) {  // Startet die LED-Schnittstelle
    delay(500);                  // Wartet, bis die LEDs gefunden wurden
  }
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {

}