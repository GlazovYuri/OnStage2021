void saber_fight_lights() {
switch (fight_state) {
        case (0):
          if (st > 0) {
            Wire.beginTransmission(8);
            Wire.write(0);
            Wire.endTransmission();
          }
          //Serial.println(fire_int);
          st = 0;
          break;
        case (1):
          if (st == 0) {
            Wire.beginTransmission(8);
            Wire.write(1);
            Wire.endTransmission();
          }
          Serial.println(st);
          st++;
          break;
        case (2):
          if (st == 0) {
            Wire.beginTransmission(8);
            Wire.write(2);
            Wire.endTransmission();
          }
          st++;
          break;
      }
      break;
}
