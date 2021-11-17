#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define PIN1        7 // On Trinket or Gemma, suggest changing this to 1
#define PIN2        8

#define NUMPIXELS 144 // Popular NeoPixel ring size

int scene = 1;
int changing_state1 = 0;
int changing_state2 = 0;

Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

#include "effects.h"

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

void changeScene(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  scene = x;
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(changeScene);

  delay(123);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels1.begin();
  pixels2.begin();

  Serial.begin(9600);
}

void loop() {
  int t1 = millis();
  //pixels.clear(); // Set all pixel colors to 'off'
  //dynamic_gradient1 (0.8, 255, 0, 0, 0, 0, 255);
  //dynamic_gradient2 (0.8, 255 , 0, 0, 0, 255, 0);
  //pixels.setPixelColor(59, 255, 255, 255);
  //pulse_rand1 (0.8, 0, 0, 0, 0, 0, 75);
  /*changing_state1 = 1;
    switch (changing_state1) {
    case (1):
      //change_dynamic_gradient1(100, 0.8,  50, 0, 0,   0, 50, 0,   0, 0, 0,   0, 0, 50);
      break;
      case (0):
        while (true) {
          dynamic_gradient1(0.8,  0, 125, 0,   0, 0, 0);
        }
        break;
    }*/
  static_gradient1(128,  0, 128, 128, 0, 128);
  //dynamic_gradient2(0.8,  25, 0, 255, 255, 0, 25);
  pixels1.show();
  //pixels2.show();
}
