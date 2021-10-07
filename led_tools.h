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
  pixels.show();
}
