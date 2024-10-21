#include "seesaw_neopixel.h"
#include "Adafruit_GFX.h"
#include "Fonts/Picopixel.h"

#define WIDTH 8                   // Wie viele Pixel in der Breite?
#define HEIGHT 8                  // Wie viele Pixel in der Höhe?
#define PIXEL_LAYOUT "linear"     // Wie sind die Pixel angeordnet? "zigzag" oder "progressive"
#define NUM_PIXELS WIDTH * HEIGHT // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15          // An welchem PIN steckt der NeoDriver?

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Zeichnfläche `canvas` auf die man malen kann
GFXcanvas16 canvas = GFXcanvas16(WIDTH, HEIGHT);


// Wird einmal beim Start aufgerufen.
void setup() {
  Serial.begin(115200);          // Startet die Debug-Verbindung  
  while (!pixels.begin(0x60)) {  // Startet die LED-Schnittstelle    
    delay(500);                  // Wartet, bis die LEDs gefunden wurden  
  }

  pixels.setBrightness(50);      // Helligkeit der LEDs anpassen
}


// 'rain-01', 8x8px
const uint16_t epd_bitmap_rain_01 [] PROGMEM = {
	0x0000, 0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0x0000, 0x0000, 0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0x0000, 
	0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f
};
// 'rain-02', 8x8px
const uint16_t epd_bitmap_rain_02 [] PROGMEM = {
	0x0000, 0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0x0000, 0x0000, 0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0x0000, 
	0x0000, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0x0000, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 0xc618, 
	0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x2d7f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 160)
const int epd_bitmap_allArray_LEN = 2;
const uint16_t* epd_bitmap_allArray[2] = {
	epd_bitmap_rain_01,
	epd_bitmap_rain_02
};

int frame = 0;


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  canvas.fillScreen(toCanvasColor(0, 0, 0));

  frame += 1;
  if (frame >= epd_bitmap_allArray_LEN) {
    frame = 0;
  }

  canvas.drawRGBBitmap(0, 0, epd_bitmap_allArray[frame], 8, 8);

  showCanvas();
  delay(200);
}


// Rechnet einzelne RGB-Werte in eine Canvas-Farbe um
uint16_t toCanvasColor(int red, int green, int blue) {
  return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}


// Rechnet eine Canvas-Farbe in eine NeoPixel-Farbe um
int toPixelColor(uint16_t color) {
  return ((color & 0xF800) << 8) | ((color & 0x07E0) << 5) | ((color & 0x001F) << 3);
}


// Rechnet eine X/Y-Koordinate in die Position eines Pixels um
int toPixelIndex(int x, int y) {
  if (PIXEL_LAYOUT == "zigzag" && y % 2 == 0) {
    return (WIDTH - x - 1) + WIDTH * y;
  } else {
    return x + WIDTH * y;
  }
}


// Kopiert den Canvas auf die NeoPixel
void showCanvas() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      int color = toPixelColor(canvas.getPixel(x, y));
      int index = toPixelIndex(x, y);
      pixels.setPixelColor(index, color);
    }
  }

  pixels.show();
}