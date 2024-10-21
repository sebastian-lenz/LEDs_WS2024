#include "seesaw_neopixel.h"

#define WIDTH 8                   // Wie viele Pixel in der Breite?
#define HEIGHT 8                  // Wie viele Pixel in der Höhe?
#define PIXEL_LAYOUT "linear"     // Wie sind die Pixel angeordnet? "zigzag" oder "linear"
#define NUM_PIXELS WIDTH * HEIGHT // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15          // An welchem PIN steckt der NeoDriver?

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);


// Wird einmal beim Start aufgerufen.
void setup() {
  Serial.begin(115200);          // Startet die Debug-Verbindung  
  while (!pixels.begin(0x60)) {  // Startet die LED-Schnittstelle    
    delay(500);                  // Wartet, bis die LEDs gefunden wurden  
  }

  pixels.setBrightness(50);      // Helligkeit der LEDs anpassen
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      int color = pixels.Color(10 + x * 5, 10 + y * 5, 0);
      int index = toPixelIndex(x, y);
      pixels.setPixelColor(index, color);
    }
  }

  pixels.show();
  delay(100);
}


// Rechnet eine X/Y-Koordinate in die Position eines Pixels um
int toPixelIndex(int x, int y) {
  if (PIXEL_LAYOUT == "zigzag" && y % 2 == 0) {
    return (WIDTH - x - 1) + WIDTH * y;
  } else {
    return x + WIDTH * y;
  }
}