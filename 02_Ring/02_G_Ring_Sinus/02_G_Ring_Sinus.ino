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
  pixels.setBrightness(50);  // Reduziert die Helligkeit
  
  int time = millis();

  // Schleife, die alle Pixel abläuft
  for (int index = 0; index < NUMPIXELS; index = index + 1) {
    double red   = sin(time * 0.0002 + index * 0.50) * 100.0;
    double green = sin(time * 0.0010 + index * 0.25) * 100.0;
    double blue  = sin(time * 0.0001 + index * 0.10) * 100.0;

    pixels.setPixelColor(index, pixels.Color(
      map(red,   -100, 100, 10, 100), 
      map(green, -100, 100, 10,  50), 
      map(blue,  -100, 100, 10, 150)  
    ));
  }
  
  pixels.show();             // Aktualisiert die LEDs
  delay(10);                // 200ms warten
}