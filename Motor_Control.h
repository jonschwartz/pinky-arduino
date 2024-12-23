#ifndef MOTOR_CONTROLLER_CLASS
#define MOTOR_CONTROLLER_CLASS

#include <Arduino.h>

class MotorController {
  private:
    int motor_pin_1;
    int motor_pin_2;
    int enable_pin;
    bool forward_flag;

  public:  
    MotorController(int motor_pin_1, int motor_pin_2, int enable_pin, bool right_flag);

    void start_motors();
    void stop_motors();
    void break_motors();
    void set_motors(bool break_flag, bool direction_flag);
};

#endif