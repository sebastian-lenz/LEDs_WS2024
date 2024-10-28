#include "Adafruit_seesaw.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers

#define PIN_ROTARY_PIXEL 6     // An welchem PIN steckt die LED am Rotary Encoder?
#define PIN_ROTARY_BUTTON 24   // An welchem PIN steckt der Button am Rotary Encoder?
#define ADDRESS_ROTARY 0x36    // Die interne Adresse des Rotary Encoders


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `rotary` mit der man den Status des Drehknopfes abfragen kann
Adafruit_seesaw rotary = Adafruit_seesaw();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet die Rotary Schnittstelle
  rotary.begin(ADDRESS_ROTARY);
  rotary.pinMode(PIN_ROTARY_BUTTON, INPUT_PULLUP);
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft den aktuellen Wert des Rotary Encoders ab
  int rotaryPosition = rotary.getEncoderPosition();
  bool isReleased = rotary.digitalRead(PIN_ROTARY_BUTTON);


  // Gibt den Wert im Debugger aus
  if (!isReleased) {
    Serial.println("Button ist gedrückt!");  
  } else {
    Serial.println(rotaryPosition);
  }
  

  // Zeigt den Wert auf den LEDs an
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (!isReleased) {
      // Wenn der Dreher gedrückt ist, werden alle LEDs rot
      pixels.setPixelColor(index, pixels.Color(255, 0, 0));
    } else if (index < rotaryPosition) {
      // Andernfalls werden die LEDs grün, die im Wertebereich liegen
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      // In allen anderen Fällen schalten wir die LEDs aus
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(10);
}