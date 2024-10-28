#include "GY521.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers

#define ADDRESS_GYRO 0x68     // Die interne Adresse des Touch-Sensors


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `sensor` mit der man den Status der kapazitiven Eingänge abrufen kann.
GY521 gyro = GY521(ADDRESS_GYRO);


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet den Touch-Sensor
  gyro.begin();
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft die Daten des Sensors ab
  gyro.read();
  float value = gyro.getAngleX();

  // Gibt die Werte im Debugger aus
  float highlight = ((90.0 + value) / 180.0) * NUM_PIXELS;
  Serial.print(value); 
  Serial.print(" > "); 
  Serial.println(highlight); 

  // Zeigt den Wert auf den LEDs an

  for (int index = 0; index < NUM_PIXELS; index++) {
    float value = min(1, max(0, 1 - abs(highlight - index)));
    pixels.setPixelColor(index, pixels.Color(0, value * 255, 0));
  }

  pixels.show();
  delay(10);
}
