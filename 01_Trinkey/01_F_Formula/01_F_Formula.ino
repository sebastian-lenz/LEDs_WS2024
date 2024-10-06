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

int colorValue = 0;
bool isRaising = true;

// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  if (isRaising) {
    if (colorValue < 245) {
      colorValue = colorValue + 10;
    } else {
      isRaising = false;
    }
  } else {
    if (colorValue > 0) {
      colorValue = colorValue - 10;
    } else {
      isRaising = true;
    }
  }

  // Setze die Farbe auf den pulsierenden Wert
  pixels.fill(pixels.Color(colorValue, 0, 0));

  // Aktualisiert die LED
  pixels.show();

  // Hält das Programm 200 Millisekunden an
  delay(200);
}