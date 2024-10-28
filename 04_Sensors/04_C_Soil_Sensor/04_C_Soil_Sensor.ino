#include "Adafruit_seesaw.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers

#define PIN_SOIL_HUMIDITY 0    // Pin an dem der Feuchtigkeitssensor steckt
#define ADDRESS_SOIL 0x36      // Die interne Adresse des Soil Sensors Encoders


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `soil` mit der man den Status des Sensors abfragen kann
Adafruit_seesaw sensor = Adafruit_seesaw();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet die Soil Sensor Schnittstelle
  sensor.begin(ADDRESS_SOIL);
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft den aktuellen Wert des Sensors
  int humidity = sensor.touchRead(PIN_SOIL_HUMIDITY);
  double temperature = sensor.getTemp();


  // Gibt den Wert im Debugger aus
  Serial.println("Feuchtigkeit: " + (String)humidity + ", Temperatur: " + (String)temperature);  
  

  // Zeigt den Wert auf den LEDs an
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (index < ((humidity - 330) * 0.001) * NUM_PIXELS) {
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(10);
}