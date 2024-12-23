#include "Motor_Control.h"

MotorController::MotorController(int motor_pin_1, int motor_pin_2, int enable_pin, bool right_flag) {
  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->enable_pin = enable_pin;

  this->forward_flag = false;
  if (right_flag) {
    this->forward_flag = true;
  }

  pinMode(this->motor_pin_1, OUTPUT);
  pinMode(this->motor_pin_2, OUTPUT);
  pinMode(this->enable_pin, OUTPUT);
  this->break_motors();
}

void MotorController::start_motors() {
  // digitalWrite(this->enable_pin, 1);
}

void MotorController::stop_motors() {
  digitalWrite(this->enable_pin, 0);
}

void MotorController::break_motors() {
  this->stop_motors();
  this->set_motors(true, true);
  this->start_motors();
}

void MotorController::set_motors(bool break_flag, bool direction_flag) {
  // if break flag = false, and direction flag = false, go backwards
  this->stop_motors();
  digitalWrite(this->motor_pin_1, 1);
  digitalWrite(this->motor_pin_2, 1);
  if (!break_flag) {
    digitalWrite(this->motor_pin_1, this->forward_flag);
    digitalWrite(this->motor_pin_2, !this->forward_flag);
    if (direction_flag) {
      digitalWrite(this->motor_pin_1, !this->forward_flag);
      digitalWrite(this->motor_pin_2, this->forward_flag);
    }
  }
}