//UNIX-like bash shell for Arduino
//Version 1.0.0
//@raspiduino 2020
//Date Created 7/7/2020
/****************************************************************************************************************************************************************/

#include "cmd.h"

String command = "";

void setup() { //Run once
  Serial.begin(9600); //Open serial port
  Serial.println("Welcome to the UNIX-like bash shell for Arduino!");
  Serial.print("Version ");
  Serial.println(version_str);
  Serial.println("@raspiduino 2020");
  //Serial.println("Please type to the console and you MUST type enter when you finish, DO NOT press the send button!"); //We don't need that anymore :)))))
  Serial.print("/> ");
}

void loop() { //Run repeatedly
  String command = input();
  Serial.println(command);
  end_command = 0; //Set the end_command back to 0
  input_str = "";  //Set the command back to "" (empty)
  exec(command);
  Serial.print(directory);
  Serial.print("> ");
}
