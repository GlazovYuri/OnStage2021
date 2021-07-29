#define motor0_A_PIN   29
#define motor0_B_PIN   30
#define motor0_PWM_PIN  4
#define motor1_A_PIN   31
#define motor1_B_PIN   32
#define motor1_PWM_PIN  5
#define motor2_A_PIN   33
#define motor2_B_PIN   34
#define motor2_PWM_PIN  6
#define motor3_A_PIN   35
#define motor3_B_PIN   36
#define motor3_PWM_PIN  7
#define motor4_A_PIN   37
#define motor4_B_PIN   38
#define motor4_PWM_PIN  8
#define motor5_A_PIN   39
#define motor5_B_PIN   40
#define motor5_PWM_PIN  9

#define motor0_INT_PIN 19
#define motor0_SIG_PIN 25
#define motor4_INT_PIN  2
#define motor4_SIG_PIN 26
#define motor5_INT_PIN  3
#define motor5_SIG_PIN 27

#include "SparkFunLSM6DS3.h"
#include "pins_arduino.h"
#include "SPI.h"
#include "nc2_toolkit.h"
#include "interpolation.h"

#include "buttonUpd.h"
#include "motor_control.h"

#include <Wire.h>

using namespace nc;

timer_ms global_time(0);
timer_ms my_time(0);

/*gyro handling*/
LSM6DS3 raw_gyro(I2C_MODE, 0x6A);
crude_integrator<micros> gyro_integrator(
  0.000001 * D2R,
  1.8856
);

/*motor_suite motors{{.value={
  {26, 28, 9},
  {30, 32, 8},
  {42, 43, 7},
  {47, 48, 6}
  }}};*/

template<typename T>
struct ni_point {
  T payload;
  long timestamp;
};

template<typename T>
class ni_sequence {
  public:
    ni_sequence(ni_point<T>* sequence_ptr, size_t size);
    T get(long timestamp);

  private:
    unsigned find_left_point_index(long timestamp);
    ni_point<T>* sequence_ptr;
    size_t size;
};

template<typename T>
ni_sequence<T>::ni_sequence(ni_point<T>* sequence_ptr, size_t size) :
  sequence_ptr(sequence_ptr), size(size)
{}

template<typename T>
unsigned ni_sequence<T>::find_left_point_index(long timestamp) {
  unsigned current_index = size - 1;
  while (sequence_ptr[current_index].timestamp > timestamp) {
    current_index--;
  }
  return current_index;
}

template<typename T>
T ni_sequence<T>::get(long timestamp) {
  unsigned left_point_index = find_left_point_index(timestamp);
  return sequence_ptr[left_point_index].payload;
}
struct my_payload {
  short v1;
  short v2;
  short p1;
  short p2;
};

#define masive_size 18

#define delta_pos   -100
#define delta_speed 0.7
#define delta_time  200

ni_point<my_payload> masive[masive_size] = {                  //1-rats   2-soldiers
  //v1                 v2                 p1                p2                   time
  {{100 * delta_speed,   100 * delta_speed,   540 + delta_pos,  -540 - delta_pos},   0},
  {{100 * delta_speed,   100 * delta_speed,   340 + delta_pos,  -350 - delta_pos},   2800 + delta_time},
  {{100 * delta_speed,   100 * delta_speed,   540 + delta_pos,  -540 - delta_pos},   3700 + 2 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   340 + delta_pos,  -350 - delta_pos},   4600 + 3 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   540 + delta_pos,  -540 - delta_pos},   5500 + 4 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   780 + delta_pos,  -750 - delta_pos},   6600 + 5 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   540 + delta_pos,  -540 - delta_pos},   7700 + 6 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   780 + delta_pos,  -750 - delta_pos},   8800 + 7 * delta_time},
  {{100 * delta_speed,   100 * delta_speed,   540 + delta_pos,  -540 - delta_pos},   9900 + 8 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -540 - delta_pos},   11000 + 9 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -470 - delta_pos},   11250 + 10 * delta_time},
  {{100 * delta_speed,    60 * delta_speed,   540 + delta_pos,  -470 - delta_pos},   12300 + 11 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -470 - delta_pos},   13200 + 12 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -400 - delta_pos},   14050 + 13 * delta_time},
  {{100 * delta_speed,    60 * delta_speed,   540 + delta_pos,  -400 - delta_pos},   14700 + 14 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -400 - delta_pos},   15800 + 15 * delta_time},
  {{120 * delta_speed,    60 * delta_speed,   850 + delta_pos,  -200 - delta_pos},   16450 + 16 * delta_time},
  {{100 * delta_speed,    60 * delta_speed,   630 + delta_pos,  -200 - delta_pos},   17150 + 17 * delta_time},
};

ni_sequence<my_payload> sequence(masive, masive_size);
//sequence.get(global_time).v1

void setup() {
  pinMode(motor0_A_PIN,   OUTPUT);
  pinMode(motor0_B_PIN,   OUTPUT);
  pinMode(motor0_PWM_PIN, OUTPUT);
  pinMode(motor1_A_PIN,   OUTPUT);
  pinMode(motor1_B_PIN,   OUTPUT);
  pinMode(motor1_PWM_PIN, OUTPUT);
  pinMode(motor2_A_PIN,   OUTPUT);
  pinMode(motor2_B_PIN,   OUTPUT);
  pinMode(motor2_PWM_PIN, OUTPUT);
  pinMode(motor3_A_PIN,   OUTPUT);
  pinMode(motor3_B_PIN,   OUTPUT);
  pinMode(motor3_PWM_PIN, OUTPUT);

  pinMode(motor0_INT_PIN, INPUT);
  pinMode(motor0_SIG_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(motor0_INT_PIN), Enc0, RISING);
  pinMode(motor4_INT_PIN, INPUT);
  pinMode(motor4_SIG_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(motor4_INT_PIN), Enc4, RISING);
  pinMode(motor5_INT_PIN, INPUT);
  pinMode(motor5_SIG_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(motor5_INT_PIN), Enc5, RISING);

  Serial.begin(9600);
  raw_gyro.begin();
  gyro_integrator.reset();

  global_time = timer_ms(0);
  my_time = timer_ms(0);
}

constexpr long iteration_duration{15};
long iterations_passed{0};

void end_iteration() {
  while(global_time<iteration_duration*(iterations_passed+1)) {};
  iterations_passed++;
}

double gyro_zero = 0;
int scene = 2;           // !!! don't change if you work with customs libraries for decoration  (without waiting button)

void loop() {
  gyro_integrator.update(raw_gyro.readFloatGyroZ());

  buttonUpd();
  Serial.println(scene);
  Serial.println(get_motor_encoder(0));

  

  //set_motor_speeds(0, 0, 25);

  switch (scene) {

    case (1):
      if (button3)  {             //wait start
        scene = 2;
        gyro_zero = gyro_integrator;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
        delay(200);                                          //for activate by start_button
      }
      break;


    case (2):
      set_motor_speeds(-25, 0, 0);                 //drive
      if (get_motor_encoder(0) > 800)   {
        scene = 3;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
      }
      break;


    case (3):
      set_motor_speeds(0, 0, 15);                 //180 turn
      if (gyro_integrator > PI / 32 * 31 + gyro_zero)   {
        scene = 4;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
        set_motor_speeds(0, 0, 0);
      }
      break;


    case (4):
      //set_motor_target(sequence.get(my_time).v1, sequence.get(my_time).p1, sequence.get(my_time).v2, sequence.get(my_time).p2);
      if (my_time > 18300 + 18 * delta_time)   {
        scene = 5;
        gyro_zero = gyro_integrator;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
      }
      break;


    case (5):
      set_motor_speeds(0, 0, -15);                 //180 turn
      if (gyro_integrator < -PI / 32 * 31  + gyro_zero)   {
        scene = 6;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
      }
      break;


    case (6):
      set_motor_speeds(25, 0, 0);                 //drive
      if (get_motor_encoder(0) > 2000)   {
        scene = 7;
        my_time = timer_ms(0);
        set_motor_encoder_zero();
      }
      break;


    case (7):
      //set_motor_target(100 * delta_speed, 0, 100 * delta_speed, 0);
      if (get_motor_encoder(0) < 5 and get_motor_encoder(0) > -5)
        //p.end(); end
      set_motor_speeds(0, 0, 0);
      break;

    }
  end_iteration();
}
