#ifndef COMMAND_CONTROLLER_CLASS
#define COMMAND_CONTROLLER_CLASS

#include <Arduino.h>
#include "PCommand.h"

class CommandController {
  private:
    // format:
    // {command # (0-9)}:{int command verb}:{csv of params up to 144 bytes}|
    String command_buffer = "";
    bool command_complete = false;
    PCommand commands[10];

  public:
    byte prog_counter = 0;
    PCommand current_command;
    
    CommandController();
    void begin();
    void log(String message);
    void load_current_command();
    void read_command();
    void parse_command();
    void erase_command_from_buffer(int prog_counter);
    void advance_program();
    void advance_program(int prog_counter);
    PCommand get_command_from_buffer();
    bool is_complete();
    void clear_input();
    void send_result();
    void process_command(int timer_duration, void (*start_function)(), void (*stop_function)());
};

#endif