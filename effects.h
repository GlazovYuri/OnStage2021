float delta2_1;
int place1 = rand() % 140 + 2;
int size1 = rand() % 23 * 2 + 2;

void pulse_rand1(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {

  for (int i = 0; i < (place1 - size1 / 2); i++) {
    pixels1.setPixelColor(i, pixels1.Color(r1, g1, b1));
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r1, g1, b1));
  }

  delta2_1 = delta2_1 + speed;
  if (delta2_1 >= 200) {
    delta2_1 = 0;
    place1 = rand() % 140 + 2;
    size1  = rand() % 20 * 2 + 6;
  }
  int delta1_1 =  100 - abs(100 - delta2_1);

  for (int i = 0; i < (size1 / 2); i++) {

    pixels1.setPixelColor(place1 + i, pixels1.Color(r1 + ((r2 - r1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100), g1 + ((g2 - g1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100), b1 + ((b2 - b1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100)));
    pixels1.setPixelColor(place1 - i, pixels1.Color(r1 + ((r2 - r1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100), g1 + ((g2 - g1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100), b1 + ((b2 - b1) / (size1 / 2) * (size1 / 2 - i) * delta1_1 / 100)));

  }
  //delay(20);
  //Serial.println(delta);

}





float delta2_2;
int place2 = rand() % 140 + 2;
int size2 = rand() % 23 * 2 + 2;

void pulse_rand2(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {

  for (int i = 0; i < (place2 - size2 / 2); i++) {
    pixels2.setPixelColor(i, pixels2.Color(r1, g1, b1));
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r1, g1, b1));
  }

  delta2_2 = delta2_2 + speed;
  if (delta2_2 >= 200) {
    delta2_2 = 0;
    place2 = rand() % 140 + 2;
    size2  = rand() % 20 * 2 + 6;
  }
  int delta1_2 =  100 - abs(100 - delta2_2);

  for (int i = 0; i < (size2 / 2); i++) {

    pixels2.setPixelColor(place2 + i, pixels2.Color(r1 + ((r2 - r1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100), g1 + ((g2 - g1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100), b1 + ((b2 - b1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100)));
    pixels2.setPixelColor(place2 - i, pixels2.Color(r1 + ((r2 - r1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100), g1 + ((g2 - g1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100), b1 + ((b2 - b1) / (size2 / 2) * (size2 / 2 - i) * delta1_2 / 100)));

  }
  //delay(20);
  //Serial.println(delta);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

float pos1;
void dynamic_gradient1(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {
  pos1 += speed;
  if (pos1 > NUMPIXELS)   pos1 -= NUMPIXELS;


  for (int i = 0; i < NUMPIXELS; i++) {
    float k1 = ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2))) / (NUMPIXELS / 2);
    float  r_1 = r1 + (r2 - r1) * k1;
    float  g_1 = g1 + (g2 - g1) * k1;
    float  b_1 = b1 + (b2 - b1) * k1;
    //Serial.println(kr_1);
    pixels1.setPixelColor(i, pixels1.Color(round(r_1), round(g_1), round(b_1)));
  }
}


float pos2;
void dynamic_gradient2(float speed, int r1, int g1, int b1, int r2, int g2, int b2) {
  pos2 += speed;
  if (pos2 > NUMPIXELS)   pos2 -= NUMPIXELS;


  for (int i = 0; i < NUMPIXELS; i++) {
    float k2 = ((NUMPIXELS / 2) - abs(abs(pos2 - i) - (NUMPIXELS / 2))) / (NUMPIXELS / 2);
    float  r_2 = r1 + (r2 - r1) * k2;
    float  g_2 = g1 + (g2 - g1) * k2;
    float  b_2 = b1 + (b2 - b1) * k2;
    pixels2.setPixelColor(i, pixels2.Color(round(r_2), round(g_2), round(b_2)));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

int inter1;
void change_dynamic_gradient1(int interr, float speed, int r11, int g11, int b11, int r12, int g12, int b12, int r21, int g21, int b21, int r22, int g22, int b22) {
  pos1 += speed;
  inter1++;
  if (inter1 < interr) {
    changing_state1 = 1;
  }
  else {
    changing_state1 = 0;
    inter1 = 0;                       //////need to move this line to global code
  }

  Serial.println("point1");
  if (pos1 > NUMPIXELS)  pos1 -= NUMPIXELS;

  for (int i = 0; i < NUMPIXELS; i++) {
    float  r1 = r11 + (r12 - r11) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    float r_1 = r21 + (r22 - r21) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    int  r__1 = round(r1  + (r_1 - r1)  * inter1 / interr);

    float  g1 = g11 + (g12 - g11) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    float g_1 = g21 + (g22 - g21) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    int  g__1 = round(g1  + (g_1 - g1)  * inter1 / interr);

    float  b1 = b11 + (b12 - b11) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    float b_1 = b21 + (b22 - b21) / (NUMPIXELS / 2) * ((NUMPIXELS / 2) - abs(abs(pos1 - i) - (NUMPIXELS / 2)));
    int  b__1 = round(b1  + (b_1 - b1)  * inter1 / interr);

    pixels1.setPixelColor(i, pixels1.Color(r__1, g__1, b__1));

  }
  Serial.println("point2");

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


int static_gradient1(int r1, int g1, int b1, int r2, int g2, int b2) {
  for (int i = 0; i < NUMPIXELS; i++) {
    float  r_1 = r1 + (r2 - r1) * i / NUMPIXELS;
    float  g_1 = g1 + (g2 - g1) * i / NUMPIXELS;
    float  b_1 = b1 + (b2 - b1) * i / NUMPIXELS;
    pixels1.setPixelColor(i, pixels1.Color(round(r_1), round(g_1), round(b_1)));
  }
}
