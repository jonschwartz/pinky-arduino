#include "PCommand.h"

PCommand::PCommand(int prog_counter, int command_word, String args) {
  this->prog_counter = prog_counter;
  this->command_word = command_word;
  this->args = args;
}

PCommand::PCommand() {
  this->command_word = 999;
  this->args = "";
  this->prog_counter = 10;
  this->start_timer = 0;
}