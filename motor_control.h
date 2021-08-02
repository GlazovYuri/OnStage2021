int max_speed = 127;  //max_speed < 255   (else pwm_pin will be on fire)

void set_motor_speeds (int speed, double angle, int turn_speed) {

  int  direction0 = 0;
  int  direction1 = 0;
  int  direction2 = 0;
  int  direction3 = 0;

  if (speed < 0) {
    speed *= -1;
    angle += PI;
  }

  int  motor0_speed = speed * cos(angle - PI / 4 * 3) + turn_speed;
  if (motor0_speed < 0) {
    motor0_speed = -1 * motor0_speed;
    direction0 = 1;
  }
  if (motor0_speed > max_speed) {
    motor0_speed = max_speed;
  }


  int  motor1_speed = speed * cos(angle - PI / 4) + turn_speed;
  if (motor1_speed < 0) {
    motor1_speed = -1 * motor1_speed;
    direction1 = 1;
  }
  if (motor1_speed > max_speed) {
    motor1_speed = max_speed;
  }


  int  motor2_speed = speed * cos(angle + PI / 4) + turn_speed;
  if (motor2_speed < 0) {
    motor2_speed = -1 * motor2_speed;
    direction2 = 1;
  }
  if (motor2_speed > max_speed) {
    motor2_speed = max_speed;
  }


  int  motor3_speed = speed * cos(angle + PI / 4 * 3) + turn_speed;
  if (motor3_speed < 0) {
    motor3_speed = -1 * motor3_speed;
    direction3 = 1;
  }
  if (motor3_speed > max_speed) {
    motor3_speed = max_speed;
  }



  if (direction0 == 0) {
    digitalWrite(motor0_A_PIN, 0);
    digitalWrite(motor0_B_PIN, 1);
  }
  else {
    digitalWrite(motor0_A_PIN, 1);
    digitalWrite(motor0_B_PIN, 0);
  }
  analogWrite(motor0_PWM_PIN, motor0_speed);


  if (direction1 == 0) {
    digitalWrite(motor1_A_PIN, 0);
    digitalWrite(motor1_B_PIN, 1);
  }
  else {
    digitalWrite(motor1_A_PIN, 1);
    digitalWrite(motor1_B_PIN, 0);
  }
  analogWrite(motor1_PWM_PIN, motor1_speed);


  if (direction2 == 0) {
    digitalWrite(motor2_A_PIN, 0);
    digitalWrite(motor2_B_PIN, 1);
  }
  else {
    digitalWrite(motor2_A_PIN, 1);
    digitalWrite(motor2_B_PIN, 0);
  }
  analogWrite(motor2_PWM_PIN, motor2_speed);


  if (direction3 == 0) {
    digitalWrite(motor3_A_PIN, 0);
    digitalWrite(motor3_B_PIN, 1);
  }
  else {
    digitalWrite(motor3_A_PIN, 1);
    digitalWrite(motor3_B_PIN, 0);
  }
  analogWrite(motor3_PWM_PIN, motor3_speed);
}




long motor0_enc = 0;
long motor4_enc = 0;
long motor5_enc = 0;
void Enc0() {
  if ( digitalRead(motor0_SIG_PIN) )
  {
    motor0_enc--;
  } else {
    motor0_enc++;
  }
}
void Enc4() {
  if ( digitalRead(motor4_SIG_PIN) )
  {
    motor4_enc--;
  } else {
    motor4_enc++;
  }
}
void Enc5() {
  if ( digitalRead(motor5_SIG_PIN) )
  {
    motor5_enc++;
  } else {
    motor5_enc--;
  }
}


float k1 = 1.5;

void set_motor_target(int v5, int pos5, int v4, int pos4) {

  long err4 = motor4_enc - pos4;
  long err5 = motor5_enc - pos5;

  long motor4_speed = abs(err4 * k1);
  long motor5_speed = abs(err5 * k1);

  if (motor4_speed > v4) {
    motor4_speed = v4;
  }
  if (motor5_speed > v5) {
    motor5_speed = v5;
  }

  Serial.print("enc4  ");
  Serial.print(motor4_enc);
  Serial.print("  err4  ");
  Serial.print(err4);
  Serial.print("  speed4  ");
  Serial.println(motor4_speed);

  if (err4 < 0) {
    digitalWrite(motor4_A_PIN, 0);
    digitalWrite(motor4_B_PIN, 1);
  }
  else {
    digitalWrite(motor4_A_PIN, 1);
    digitalWrite(motor4_B_PIN, 0);
  }
  analogWrite(motor4_PWM_PIN, motor4_speed);

  if (err5 < 0) {
    digitalWrite(motor5_A_PIN, 0);
    digitalWrite(motor5_B_PIN, 1);
  }
  else {
    digitalWrite(motor5_A_PIN, 1);
    digitalWrite(motor5_B_PIN, 0);
  }
  analogWrite(motor5_PWM_PIN, motor5_speed);

}



long enc0_zero = 0;

int get_motor_encoder() {
  return motor0_enc - enc0_zero;
}

void set_motor_encoder_zero() {
  enc0_zero = 0;
  enc0_zero = get_motor_encoder();
}

void stop_up_motors() {
  digitalWrite(motor4_A_PIN, 0);
  digitalWrite(motor4_B_PIN, 0);
  digitalWrite(motor5_A_PIN, 0);
  digitalWrite(motor5_B_PIN, 0);
  analogWrite(motor4_PWM_PIN, 0);
  analogWrite(motor5_PWM_PIN, 0);
}
