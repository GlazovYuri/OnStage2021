#define NUMPIXELS 144


void to_cmass(int num, int mass[NUMPIXELS][3]) {
  if (num == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      for (int j = 0; j < 3; j++) {
        cmass1[i][j] = mass[i][j];
      }
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      for (int j = 0; j < 3; j++) {
        cmass2[i][j] = mass[i][j];
      }
    }
  }
}
