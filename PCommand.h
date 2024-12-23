#ifndef PCOMMAND_CLASS
#define PCOMMAND_CLASS

#include <Arduino.h>

class PCommand{
  private:

  public:
    int prog_counter = 10;
    int command_word = 999;
    String args = "";
    unsigned long start_timer = 0;
    int timer_duration = 0;
    String output = "";
    bool complete = false;
    bool started = false;

    PCommand(int prog_counter, int command_word, String args);
    PCommand();
};

#endif