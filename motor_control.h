void set_motor_speeds (int speed, double angle, int turn_speed) {

  int  direction0 = 0;
  int  direction1 = 0;
  int  direction2 = 0;
  int  direction3 = 0;

  if (speed < 0) {
    speed *= -1;
    angle += PI;
  }

  int  motor0_speed = speed * sin(angle - PI / 4 * 3) + turn_speed;
  if (motor0_speed < 0) {
    motor0_speed = -1 * motor0_speed;
    direction0 = 1;
  }
  if (motor0_speed > 255) {
    motor0_speed = 255;
  }


  int  motor1_speed = speed * sin(angle - PI / 4) + turn_speed;
  if (motor1_speed < 0) {
    motor1_speed = -1 * motor1_speed;
    direction1 = 1;
  }
  if (motor1_speed > 255) {
    motor1_speed = 255;
  }


  int  motor2_speed = speed * sin(angle + PI / 4) + turn_speed;
  if (motor2_speed < 0) {
    motor2_speed = -1 * motor2_speed;
    direction2 = 1;
  }
  if (motor2_speed > 255) {
    motor2_speed = 255;
  }


  int  motor3_speed = speed * sin(angle + PI / 4 * 3) + turn_speed;
  if (motor3_speed < 0) {
    motor3_speed = -1 * motor3_speed;
    direction3 = 1;
  }
  if (motor3_speed > 255) {
    motor3_speed = 255;
  }



  if (direction0 == 0) {
    digitalWrite(motor0_A_PIN, 0);
    digitalWrite(motor0_B_PIN, 1);
  }
  else {
    digitalWrite(motor0_A_PIN, 1);
    digitalWrite(motor0_B_PIN, 0);
  }
  digitalWrite(motor0_PWM_PIN, motor0_speed);


  if (direction1 == 0) {
    digitalWrite(motor1_A_PIN, 0);
    digitalWrite(motor1_B_PIN, 1);
  }
  else {
    digitalWrite(motor1_A_PIN, 1);
    digitalWrite(motor1_B_PIN, 0);
  }
  digitalWrite(motor1_PWM_PIN, motor1_speed);


  if (direction2 == 0) {
    digitalWrite(motor2_A_PIN, 0);
    digitalWrite(motor2_B_PIN, 1);
  }
  else {
    digitalWrite(motor2_A_PIN, 1);
    digitalWrite(motor2_B_PIN, 0);
  }
  digitalWrite(motor2_PWM_PIN, motor2_speed);


  if (direction3 == 0) {
    digitalWrite(motor3_A_PIN, 0);
    digitalWrite(motor3_B_PIN, 1);
  }
  else {
    digitalWrite(motor3_A_PIN, 1);
    digitalWrite(motor3_B_PIN, 0);
  }
  digitalWrite(motor3_PWM_PIN, motor3_speed);
}




long motor0_enc = 0;
void Enc0()
{
  if ( digitalRead(motor0_SIG_PIN) )
  {
    motor0_enc++;
  } else {
    motor0_enc--;
  }
}

long enc0_zero = 0;

int get_motor_encoder(int enc_number) {
  if (enc_number == 0) {
    return motor0_enc - enc0_zero;
  }
  //need more encoders (4 && 5)
}

void set_motor_encoder_zero() {
  enc0_zero = 0;
  enc0_zero = get_motor_encoder(0);
}
