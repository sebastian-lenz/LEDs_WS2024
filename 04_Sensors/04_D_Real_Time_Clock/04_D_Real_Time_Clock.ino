#include "RTClib.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `rtc` (kurz für `Real Time Clock`) mit der man auf die Uhr zugreifen kann.
RTC_PCF8523 rtc = RTC_PCF8523();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet die Uhr
  rtc.begin();
  if (!rtc.initialized() || rtc.lostPower()) {
    Serial.println("Die Uhr ist nicht gestellt");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.start();
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft die aktuelle Uhrzeit ab
  DateTime now = rtc.now();

  // Gibt den Wert im Debugger aus
  Serial.print(now.day());  
  Serial.print(".");  
  Serial.print(now.month());  
  Serial.print(".");  
  Serial.print(now.year());  
  Serial.print(" ");  
  Serial.print(now.hour());
  Serial.print(":");  
  Serial.print(now.minute());
  Serial.print(":");  
  Serial.print(now.second());
  Serial.println();


  // Zeigt den Wert auf den LEDs an
  int seconds = now.second();
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (index < (seconds / 60.0) * NUM_PIXELS) {
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(10);
}