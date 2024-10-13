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
  pixels.setBrightness(10);  // Reduziert die Helligkeit
  
  // Die Farbe aller Pixel setzen
  pixels.setPixelColor(0,  pixels.Color(255, 0, 0));
  pixels.setPixelColor(1,  pixels.Color(0, 255, 0));
  pixels.setPixelColor(2,  pixels.Color(0, 0, 255));
  pixels.setPixelColor(3,  pixels.Color(255, 0, 0));
  pixels.setPixelColor(4,  pixels.Color(0, 255, 0));
  pixels.setPixelColor(5,  pixels.Color(0, 0, 255));
  pixels.setPixelColor(6,  pixels.Color(255, 0, 0));
  pixels.setPixelColor(7,  pixels.Color(0, 255, 0));
  pixels.setPixelColor(8,  pixels.Color(0, 0, 255));
  pixels.setPixelColor(9,  pixels.Color(255, 0, 0));
  pixels.setPixelColor(10, pixels.Color(0, 255, 0));
  pixels.setPixelColor(11, pixels.Color(0, 0, 255));
  pixels.setPixelColor(12, pixels.Color(255, 0, 0));
  pixels.setPixelColor(13, pixels.Color(0, 255, 0));
  pixels.setPixelColor(14, pixels.Color(0, 0, 255));
  pixels.setPixelColor(15, pixels.Color(255, 0, 0));
  
  pixels.show();             // Aktualisiert die LEDs
  delay(200);                // 200ms warten
}