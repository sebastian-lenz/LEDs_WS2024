#include "Adafruit_LTR390.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `sensor` mit der man die UV/Lichtstärke abfragen kann.
Adafruit_LTR390 sensor = Adafruit_LTR390();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet den Lichtsensor
  sensor.begin();
  sensor.setMode(LTR390_MODE_ALS); // Oder LTR390_MODE_UVS
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft die Daten des Sensors ab
  int intensity = sensor.readALS(); // oder readUVS();


  // Gibt die Werte im Debugger aus
  Serial.print("Intensitaet: ");
  Serial.print(intensity);
  Serial.println();


  // Zeigt den Wert auf den LEDs an
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (index * 10 < intensity) {
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(100);
}