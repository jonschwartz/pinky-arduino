#include "Arduino.h"
#include "Command_Controller.h"


CommandController::CommandController () {
}

void CommandController::begin() {
  command_buffer.reserve(40);
  this->clear_input();
  for (int x = 0; x <= 9; x++) {
    // Serial.println("erasing");
    this->erase_command_from_buffer(x);
  }
  this->prog_counter = 0;
  this->load_current_command();
}

void CommandController::log(String message) {
  Serial.println(message);
  delay(200);
}

void CommandController::load_current_command() {
  this->current_command = this->commands[this->prog_counter];
}

void CommandController::read_command() {
  while (Serial.available()) {
    // get the new byte:
    char in_char = (char)Serial.read();
    if (in_char == '\n') {
      this->command_complete = true;
    } else {
      this->command_buffer += in_char;
    }
  }
  if (this->command_complete) {
    this->parse_command();
    this->clear_input();
  }
}

void CommandController::parse_command() {
  if (this->command_buffer.length() < 4) {
    // this->log("Error: command_buffer too short!");
    return;
  }

  long prog_counter = this->command_buffer.substring(0, 1).toInt();
  long command_word = this->command_buffer.substring(1, 4).toInt();
  String args = this->command_buffer.substring(4);

  if ((prog_counter < 0) || (prog_counter > 9)) {
    // this->log((String)"prog counter out of bounds " + prog_counter);
    return;
  }

  this->erase_command_from_buffer(prog_counter);
  this->commands[prog_counter] = PCommand::PCommand(prog_counter, command_word, args);
  this->load_current_command();
}

void CommandController::erase_command_from_buffer(int prog_counter) {
  if ((prog_counter < 0) || (prog_counter > 9)) {
    // this->log("erase - prog counter out of bounds " + String(prog_counter));
    return;
  }
  this->commands[prog_counter] = PCommand::PCommand();
  this->load_current_command();
}
void CommandController::advance_program() {
  this->advance_program(this->prog_counter);
}
void CommandController::advance_program(int prog_counter) {
  prog_counter++;
  if (prog_counter > 9) {
    prog_counter = 0;
  }
  this->prog_counter = prog_counter;
}

PCommand CommandController::get_command_from_buffer() {
  this->advance_program();
  this->load_current_command();
  return this->current_command;
}

bool CommandController::is_complete() {
  return this->command_complete;
}

void CommandController::clear_input() {
  this->command_complete = false;
  this->command_buffer = "";
}

void CommandController::send_result() {
  Serial.println(this->current_command.prog_counter+this->current_command.output);
  delay(200);
}

void CommandController::process_command(int timer_duration, void (*start_function)(), void (*stop_function)()) {
  if (this->current_command.command_word == 999) {
    // this->log("no op process_command");
    return;
  }
  if ((this->current_command.start_timer == 0) && (!this->current_command.complete)) {
    this->current_command.start_timer = millis();
    this->current_command.timer_duration = timer_duration;
    start_function();
    this->current_command.started = true;
    this->commands[this->prog_counter] = this->current_command;
  } else if (this->current_command.start_timer + this->current_command.timer_duration <= millis()) {
    stop_function();
    this->current_command.complete = true;
    this->send_result();
    this->erase_command_from_buffer(this->current_command.prog_counter);
  }
}