#include <Adafruit_NeoPixel.h>

// Erzeugt die Schnittstelle `pixels` um die LEDs anzusteuern 
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


// Wird einmal beim Start aufgerufen.
void setup() {  
  Serial.begin(115200);              // Startet die Debug-Verbindung
  pixels.begin();                    // Startet die LED-Schnittstelle
  pinMode(PIN_SWITCH, INPUT_PULLUP); // Startet den Button
}

// Wird immer wieder in Endlosschleife aufgerufen.
void loop() {
  // Ruft den Status des Buttons ab
  if (digitalRead(PIN_SWITCH)) {
    pixels.fill(pixels.Color(255, 0, 0));
  } else {
    pixels.fill(pixels.Color(0, 255, 0));
  }

  // Aktualisiert die LED
  pixels.show();

  // Hält das Programm 200 Millisekunden an
  delay(200);
}