Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
#define NUMPIXELS 144

void update_led(int num, int mass[NUMPIXELS][3]) {
  if (num == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels1.setPixelColor(i, pixels1.Color(color_mass1[i][0], color_mass1[i][1], color_mass1[i][2]));
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels2.Color(color_mass2[i][0], color_mass2[i][1], color_mass2[i][2]));
    }
  }
  pixels1.show();
  pixels2.show();
}
