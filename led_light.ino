#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//#include "effects.h"
#define NUMPIXELS 144


#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels


int static_gradient(int r1, int g1, int b1, int r2, int g2, int b2) {
  int color_mass[NUMPIXELS - 1][3];
  for (int i = 0; i < NUMPIXELS; i++) {

    color_mass[i][0] = r1 + (r2 - r1) / NUMPIXELS * i;
    color_mass[i][1] = g1 + (g2 - g1) / NUMPIXELS * i;
    color_mass[i][2] = b1 + (b2 - b1) / NUMPIXELS * i;

    return color_mass;
    //delay(DELAYVAL);
  }
}


int scene = 1;
void changeScene(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read();
    Serial.print(c);
  }
  int x = Wire.read();
  Serial.println(x);
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

  Serial.begin(9600);
}
int cmass1[144][3];
void loop() {
  int t1 = millis();

  // = static_gradient(50, 25, 0, 0, 50, 25);
  //pixels.clear(); // Set all pixel colors to 'off'
  //dynamic_gradient (0.8, 25, 0, 0, 0, 0, 128);
  /*pixels.setPixelColor(59, 255, 255, 255);
      pixels.show();*/

  /*switch (scene) {
    case (1):
      pulse_rand (0.8, 0, 0, 0, 0, 0, 75);
      break;
    case (2):
      pulse_rand (0.8, 0, 0, 0, 0, 75, 0);
      break;
    case (3):
      pulse_rand (0.8, 0, 0, 0, 75, 0, 0);
      break;
    }*/

  //  Serial.println(delta);

}