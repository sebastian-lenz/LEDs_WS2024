#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL  6  // Definiert wo die Bauteile angesteckt sind.
#define PIN_SWITCH   12  // Braucht man nur im Simulator!

#define NUMPIXELS     1  // Definiert wieviele LEDs wir haben

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


// Wird einmal beim Start aufgerufen.
void setup() {  
  Serial.begin(115200); // Startet die Debug-Verbindung
  pixels.begin();       // Startet die LED-Schnittstelle
}

// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  pixels.setPixelColor(0, pixels.Color(255, 0, 100));
  pixels.show();
}