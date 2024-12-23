#include "Command_Controller.h"
#include "Motor_Control.h"
#include "PCommand.h"

#define LN298_ENA_PIN 6
#define LN298_IN4_PIN 11
#define LN298_IN3_PIN 9
#define LN298_IN2_PIN 8
#define LN298_IN1_PIN 7
#define LN298_ENB_PIN 5

#define SERVO_PIN 3

#define ULTRASONIC_TRIGGER_PIN A5
#define ULTRASONIC_ECHO_PIN A4
#define DEFAULT_MOTOR_TIMEOUT_MILLISECONDS 250

MotorController left_motors(LN298_IN1_PIN, LN298_IN2_PIN, LN298_ENB_PIN, false);
MotorController right_motors(LN298_IN3_PIN, LN298_IN4_PIN, LN298_ENA_PIN, true);
CommandController command_controller;

void choose_actions() {
  if (command_controller.current_command.command_word != 999) {
    switch ((int)command_controller.current_command.command_word) {
      case 1:
        command_controller.log("hit 1 command");
        // turn hard right for default motor timeout
        command_controller.current_command.output = "move motors - hard right";
        command_controller.process_command(DEFAULT_MOTOR_TIMEOUT_MILLISECONDS, start_func_1, break_motors);
        break;
      case 2:
        command_controller.log("hit 2 command");
        // turn hard left for default motor timeout
        command_controller.current_command.output = "Pretending to move motors - hard left";
        command_controller.process_command(DEFAULT_MOTOR_TIMEOUT_MILLISECONDS, start_func_2, break_motors);
        break;
      case 3:
        command_controller.log("hit 3 command");
        // all ahead for default motor timeout
        command_controller.current_command.output = "Pretending to move motors - forward";
        command_controller.process_command(DEFAULT_MOTOR_TIMEOUT_MILLISECONDS, start_func_3, break_motors);
        break;
      case 4:
        command_controller.log("hit 4 command");
        // all back for default motor timeout
        command_controller.current_command.output = "Pretending to move motors - backward";
        command_controller.process_command(DEFAULT_MOTOR_TIMEOUT_MILLISECONDS, start_func_4, break_motors);
        break;
      case 5:
        command_controller.log("hit 5 command");
        // read ultrasonic
        command_controller.process_command(DEFAULT_MOTOR_TIMEOUT_MILLISECONDS, start_func_5, break_motors);
        break;
      case 997:
        // ping
        command_controller.current_command.output = "pong";
        command_controller.process_command(0, noop, break_motors);
        break;
      case 998:
      default:
        // break
        command_controller.log("hit default");
        command_controller.current_command.output = "Pretending to stop";
        command_controller.process_command(1, break_motors, break_motors);
        break;
    }
  }
}


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait for Serial Monitor to connect
  }
  command_controller.begin();

  left_motors.break_motors();
  right_motors.break_motors();
}

void loop() {
  command_controller.get_command_from_buffer();
  choose_actions();
}

void break_motors() {
  left_motors.break_motors();
  right_motors.break_motors();
}

void start_motors(bool left_direction, bool right_direction) {
  left_motors.set_motors(false, left_direction);
  right_motors.set_motors(false, right_direction);
  left_motors.start_motors();
  right_motors.start_motors();
}

void move_servo(int position) {
}

float read_ultrasonic() {
  // motors need to be stopped for this to go because otherwise, the data doesn't make sense
  break_motors();
  return 0;
}

void serialEvent() {
  command_controller.read_command();
}

// Command Start Functions

void noop() {

}

void start_func_1() {
  start_motors(true, false);
}

void start_func_2() {
  start_motors(false, true);
};

void start_func_3() {
  start_motors(true, true);
}

void start_func_4() {
  start_motors(false, false);
}

void start_func_5() {
  float reading = read_ultrasonic();
  command_controller.current_command.output = (String)reading;
}