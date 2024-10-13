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

int highlightIndex = 0;

// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  pixels.setBrightness(10);  // Reduziert die Helligkeit

  // Position des Highlights erhöhen
  highlightIndex += 1;
  if (highlightIndex >= NUMPIXELS) {
    highlightIndex = 0;
  }

  // Schleife, die alle Pixel abläuft
  for (int index = 0; index < NUMPIXELS; index = index + 1) {
    int difference = abs(highlightIndex - index);
    if (difference > NUMPIXELS * 0.5) {
      difference = abs(difference - NUMPIXELS);
    }
    
    int colorValue = 255 - difference * 50;
    if (colorValue < 0) {
      colorValue = 0;
    }

    pixels.setPixelColor(index, pixels.Color(colorValue, colorValue, colorValue));
  }
  
  pixels.show();             // Aktualisiert die LEDs
  delay(200);                // 200ms warten
}