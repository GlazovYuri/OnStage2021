#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        8 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 144 // Popular NeoPixel ring size

int scene = 1;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

void static_gradient(int r1, int g1, int b1, int r2, int g2, int b2) {
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(r1 + (r2 - r1) / NUMPIXELS * i, g1 + (g2 - g1) / NUMPIXELS * i, b1 + (b2 - b1) / NUMPIXELS * i));

    pixels.show();

    //delay(DELAYVAL);
  }
}

float pos1;

void dynamic_gradient(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {
  pos1 += speed;
  if (pos1 > NUMPIXELS)   pos1 -= NUMPIXELS;


  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(round(r1 + (r2 - r1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)))), round(g1 + (g2 - g1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)))), round(b1 + (b2 - b1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2))))));

  }
  pixels.show();
}

float delta2;
int place = rand() % 140 + 2;
int size = rand() % 23 * 2 + 2;

void pulse_rand(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {

  for (int i = 0; i < (place - size / 2); i++) {
    pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r1, g1, b1));
  }

  delta2 = delta2 + speed;
  if (delta2 >= 200) {
    delta2 = 0;
    place = rand() % 140 + 2;
    size  = rand() % 20 * 2 + 6;
  }
  int delta =  100 - abs(100 - delta2);

  for (int i = 0; i < (size / 2); i++) {

    pixels.setPixelColor(place + i, pixels.Color(r1 + ((r2 - r1) / (size / 2) * (size / 2 - i) * delta / 100), g1 + ((g2 - g1) / (size / 2) * (size / 2 - i) * delta / 100), b1 + ((b2 - b1) / (size / 2) * (size / 2 - i) * delta / 100)));
    pixels.setPixelColor(place - i, pixels.Color(r1 + ((r2 - r1) / (size / 2) * (size / 2 - i) * delta / 100), g1 + ((g2 - g1) / (size / 2) * (size / 2 - i) * delta / 100), b1 + ((b2 - b1) / (size / 2) * (size / 2 - i) * delta / 100)));

  }
  //delay(20);
  pixels.show();
  //Serial.println(delta);

}

/*
  int change_flag;
  int first_color;
  int color_mass[NUMPIXELS];
  int mass[3];

  void change_to_gradient(int speed, int r1, int g1, int b1, int r2, int g2, int b2) { //setings for gradient
  if (change_flag == 0) {
    change_flag = 1;
    for (int i = 0; i < NUMPIXELS; i++) {
      int mass [0] = pixels.getPixelColor(mass{i]);
    }
  }
  }*/

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
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.begin(9600);
}

void loop() {
  int t1 = millis();
  //pixels.clear(); // Set all pixel colors to 'off'
  switch (scene) {
    //dynamic_gradient (0.8, 25, 0, 0, 0, 0, 128);
    /*pixels.setPixelColor(59, 255, 255, 255);
        pixels.show();*/
    case (1):
      pulse_rand (0.8, 0, 0, 0, 0, 0, 75);
      break;
    case (2):
      pulse_rand (0.8, 0, 0, 0, 0, 75, 0);
      break;
    case (3):
      pulse_rand (0.8, 0, 0, 0, 75, 0, 0);
      break;
  }

  //  Serial.println(delta);

}
