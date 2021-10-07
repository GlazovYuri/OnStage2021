#define PIN1    8
#define PIN2    9

#define NUMPIXELS 144

Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

pixels1.begin();
pixels2.begin();

int color_mass1[NUMPIXELS][3];
int color_mass2[NUMPIXELS][3];


void static_gradient1(int r1, int g1, int b1, int r2, int g2, int b2) {
  for (int i = 0; i < NUMPIXELS; i++) {

    color_mass1[i][0] = r1 + (r2 - r1) * i / NUMPIXELS;
    color_mass1[i][1] = g1 + (g2 - g1) * i / NUMPIXELS;
    color_mass1[i][2] = b1 + (b2 - b1) * i / NUMPIXELS;
  }
}

void static_gradient2(int r1, int g1, int b1, int r2, int g2, int b2) {
  for (int i = 0; i < NUMPIXELS; i++) {

    color_mass2[i][0] = r1 + (r2 - r1) * i / NUMPIXELS;
    color_mass2[i][1] = g1 + (g2 - g1) * i / NUMPIXELS;
    color_mass2[i][2] = b1 + (b2 - b1) * i / NUMPIXELS;
  }
}

float pos1;
void dynamic_gradient1(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {
  pos1 += speed;
  if (pos1 > NUMPIXELS)   pos1 -= NUMPIXELS;


  for (int i = 0; i < NUMPIXELS; i++) {

    color_mass1[i][0] = r1 + (r2 - r1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    color_mass1[i][1] = g1 + (g2 - g1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    color_mass1[i][2] = b1 + (b2 - b1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));

  }
  pixels.show();
}

float pos2;
void dynamic_gradient2(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {
  pos2 += speed;
  if (pos2 > NUMPIXELS)   pos2 -= NUMPIXELS;


  for (int i = 0; i < NUMPIXELS; i++) {

    color_mass2[i][0] = r1 + (r2 - r1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    color_mass2[i][1] = g1 + (g2 - g1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    color_mass2[i][2] = b1 + (b2 - b1) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));

  }
  pixels.show();
}


float delta2;
int place = rand() % 140 + 2;
int size = rand() % 23 * 2 + 2;

/*void pulse_rand(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {

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

}*/

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
