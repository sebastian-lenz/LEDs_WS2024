#include "Adafruit_MPR121.h"
#include "seesaw_neopixel.h"

#define NUM_PIXELS 32          // Wie viele Pixel insgesamt?
#define PIN_NEODRIVER 15       // An welchem PIN steckt der NeoDriver?
#define ADDRESS_NEODRIVER 0x60 // Die interne Adresse des NeoDrivers

#define ADDRESS_TOUCH 0x5A     // Die interne Adresse des Touch-Sensors


// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
seesaw_NeoPixel pixels = seesaw_NeoPixel(NUM_PIXELS, PIN_NEODRIVER, NEO_GRB + NEO_KHZ800);

// Erzeugt die Schnittstelle `sensor` mit der man den Status der kapazitiven Eingänge abrufen kann.
Adafruit_MPR121 sensor = Adafruit_MPR121();


// Wird einmal beim Start aufgerufen.
void setup() {
  // Startet die Debug-Verbindung  
  Serial.begin(115200);

  // Startet die Pixel-Schnittstelle & setzt Helligkeit
  pixels.begin(0x60);
  pixels.setBrightness(25);

  // Startet den Touch-Sensor
  sensor.begin(ADDRESS_TOUCH);
}


int currentState = 0;
int lastState = 0;


// Gibt an, ob ein Eingang gerade gedrückt wird
bool isTouched(int touchIndex, int state = currentState) {
  if (touchIndex < 0 || touchIndex >= 12) {
    return false;
  } else {
    return state & (1 << touchIndex);
  }
}


// Gibt an, ob ein Eingang zuvor gedrückt wurde
bool wasTouched(int touchIndex) {
  return isTouched(touchIndex, lastState);
}


// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft die Daten des Sensors ab
  lastState = currentState;
  currentState = sensor.touched();


  // Gibt die Werte im Debugger aus
  for (int index = 0; index < 12; index++) {
    if (isTouched(index) && !wasTouched(index)) {
      Serial.print(index); 
      Serial.println(" gedrückt");
    }

    if (!isTouched(index) && wasTouched(index)) {
      Serial.print(index); 
      Serial.println(" losgelassen");
    }
  }


  // Zeigt den Wert auf den LEDs an
  for (int index = 0; index < NUM_PIXELS; index++) {
    if (isTouched(index)) {
      pixels.setPixelColor(index, pixels.Color(0, 255, 0));
    } else {
      pixels.setPixelColor(index, pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
  delay(100);
}
