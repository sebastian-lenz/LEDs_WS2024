#include "Adafruit_LPS2X.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `sensor` mit der man den Luftdruck abfragen kann.
Adafruit_LPS22 sensor = Adafruit_LPS22();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet den Luftdruck-Sensor
  sensor.begin_I2C();
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft die Daten des Sensors ab
  sensors_event_t pressureEvent;
  sensors_event_t temperatureEvent;
  sensor.getEvent(&pressureEvent, &temperatureEvent);

  float pressure = pressureEvent.pressure;
  float temperature = temperatureEvent.temperature;


  // Gibt die Werte im Debugger aus
  Serial.print("Temperatur: ");
  Serial.print(temperature);
  Serial.print(" Grad, Luftdruck: ");
  Serial.print(pressure);
  Serial.print("hPa");
  Serial.println();


  // Zeigt den Wert auf den LEDs an
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (index < (temperature / 40.0) * NUM_PIXELS) {
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(100);
}