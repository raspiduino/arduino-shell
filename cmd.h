/*Basic commands*/

#include "EEPROMAnything.h"

String version_str = "1.0.2";
String input_str = "";
int end_command = 0;
String directory = "/";
int address_end = 1023; //Default for Arduino UNO
String clipboard_str = ""; //Clipboard string

//list of command :D
void exec(); //This is one not command, sorry :(
void hi();
void ver();
void help();
void ls();
void dir();
void sudo();
String cpu();
int free_ram();
void cd();
String input(); //This is not a command!
void edit_eeprom();
void read_eeprom();
void clipboard();

/*Assembly support*/
//void asm_exec();
//void asm_edit();

void exec(String command) {
  int done_exec = 0;
  //Find the command in the command list
  if(command == "hi"){hi(); done_exec = 1;}
  if(command == "ver"){ver(); done_exec = 1;}
  if(command == "help"){help(); done_exec = 1;}
  if(command == "ls"){ls(); done_exec = 1;}
  if(command == "dir"){ls(); done_exec = 1;}
  if(command == "sudo"){sudo(); done_exec = 1;}
  if(command == "cpu"){Serial.println(F("Your cpu type is: ")); Serial.println(cpu()); Serial.println(F("If there isn't anything, your cpu cannot be read!")); done_exec = 1;}
  if(command == "free_ram"){Serial.println(free_ram()); done_exec = 1;}
  if(command == "cd"){cd(); done_exec = 1;}
  if(command == "edit_eeprom"){edit_eeprom(); done_exec = 1;}
  if(command == "read_eeprom"){read_eeprom(); done_exec = 1;}
  if(command == "clipboard"){clipboard(); done_exec = 1;}
  //if(command == "asm_exec"){asm_exec(); done_exec = 1;}
  //if(command == "asm_edit"){asm_edit(); done_exec = 1;}
  if(done_exec != 1){
    Serial.println(F("Error while execute command! You can try again! Maybe there isn't a command like that! If you retry and the command still error, please press reset!"));
    Serial.println(F("Sorry for the usuage of some command, like cd,..."));
  }
}

void hi() {
  Serial.println(F("Hello, welcome to the shell!"));  
}

void ver() {
  Serial.println(version_str);  
}

void help() {
  Serial.println(F("Welcome to the UNIX-like bash shell for Arduino!"));
  Serial.print(F("Version "));
  Serial.println(version_str);
  Serial.println(F("You can execute the following commands: "));
  Serial.println(F("hi    ver   help    sudo    ls    dir   cpu   free_ram    cd    read_eeprom   edit_eeprom"));
  Serial.println(F("clipboard   asm_exec    asm_edit"));
}

void ls(){
  Serial.println(F("The devices are: "));
  Serial.println(F("/flash"));
  Serial.println(F("/eeprom")); //The eeprom in your Arduino. You can store your file here, modify them and your data won't lost when you unplug your Arduino. Remember: if you erease or rewrite it very often, it will soon be damaged because your eeprom only accepts total 100.000 erease times per one memory cell!
  //Storage devices OUTSIDE your Arduino: we haven't supported this yet. Comming soon in the future version!
  if(directory == "/flash"){
    Serial.println(F("There are command in it, please use help"));  
  }
}

void sudo(){
  Serial.println(F("Comming soon!"));  
}

String cpu(){
  //Thanks to Jim Eli at https://ucexperiment.wordpress.com/2012/02/23/determine-which-arduino-%C2%B5c-your-code-is-on/ or you can also see at https://web.archive.org/web/20200709035756/https://ucexperiment.wordpress.com/2012/02/23/determine-which-arduino-%C2%B5c-your-code-is-on/ if you can not go to the first link
  if(SIGNATURE_0 == 0x1e && SIGNATURE_1 == 0x94 && SIGNATURE_2 == 0x06){return("ATmega168");}
  if(SIGNATURE_0 == 0x1e && SIGNATURE_1 == 0x95 && SIGNATURE_2 == 0x0f){return("ATmega328");}
  if(SIGNATURE_0 == 0x1e && SIGNATURE_1 == 0x97 && SIGNATURE_2 == 0x03){return("ATmega1280");}
  if(SIGNATURE_0 == 0x1e && SIGNATURE_1 == 0x98 && SIGNATURE_2 == 0x01){return("ATmega2560");}
  //If you are using Arduino Yún, why don't you use the real Linux?
}

int free_ram(){//Thanks to ksp http://arduino.vn/bai-viet/355-cach-luu-tru-cac-bien-so-mang-chuoi-trong-arduino
  extern int __heap_start;
  extern int *__brkval;
  int free_ram_amount = (int) SP - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  Serial.print(F("The free RAM amount is "));
  Serial.println(free_ram_amount);
}

void cd(){
  Serial.println(F("Where do you want to go?"));
  String tmp_directory = input();
  if(tmp_directory != "/flash" && tmp_directory != "/eeprom"){
    Serial.println(F("Invaild directory! Please try again!"));  
  } else {
    directory = tmp_directory;
  }
  end_command = 0; //Set the end_command back to 0
  input_str = "";  //Set the command back to "" (empty)
}

String input(){
  Serial.print("> ");
  while (end_command == 0){
    if (Serial.available() > 0) { //If the serial has incomming character, read it
      int incomingByte = Serial.read(); //Read the character ASCII number to the incomingByte varrible
      if (incomingByte == -1 | incomingByte == 10 | incomingByte == 13) { // Don't read the empty character like -1, 10 or 13 (enter)
        if (incomingByte == 13) { //If the user press enter
          end_command = 1; //Said that the input was ended
          if (input_str == "$clipboard"){
            input_str = clipboard_str; //Support for clipboard  
          }
          Serial.println(input_str);
          return(input_str);
        }
      } else {
        char input_tmp = char(incomingByte); //Convert number to ASCII character
        //Serial.println(input_tmp); //For debug 
        input_str = String(input_str + input_tmp); //Add the character to the command string
      }
    }  
  }
}

void edit_eeprom(){
  if(directory != "/flash"){
    Serial.println(F("Which adress do you want to write ?"));
    String edit_addr_eeprom = input();
    //edit_addr_eeprom = edit_addr_eeprom.toInt();
    end_command = 0; //Set the end_command back to 0
    input_str = "";  //Set the string back to "" (empty)
    Serial.println(F("Enter the text:"));
    String edit_eeprom = input();
    end_command = 0; //Set the end_command back to 0
    input_str = "";  //Set the string back to "" (empty)
    delay(5);
    write_String(edit_addr_eeprom.toInt(), edit_eeprom);
  } else {
    Serial.println(F("You cannot use it in /flash and /ram !"));  
  }  
}

void read_eeprom(){
  if(directory != "/flash"){
    Serial.println(F("Which adress do you want to read ?"));
    String read_addr_eeprom = input();
    end_command = 0; //Set the end_command back to 0
    input_str = "";  //Set the string back to "" (empty)
    delay(5);
    Serial.println(read_String(read_addr_eeprom.toInt()));
  } else {
    Serial.println(F("You cannot use it in /flash and /ram !"));  
  }
}

void clipboard(){
  if(directory != "/flash"){
    Serial.println(F("Which adress do you want to read to your clipboard?"));
    String clip_addr_eeprom = input();
    end_command = 0; //Set the end_command back to 0
    input_str = "";  //Set the string back to "" (empty)
    delay(5);
    clipboard_str = read_String(clip_addr_eeprom.toInt());
    Serial.println(F("Done. Now you can paste it to input by using $clipboard"));
  } else {
    Serial.println(F("You cannot use it in /flash!"));  
  }
}

/*void asm_exec(){ //Read asm code in eeprom
  Serial.println(F("Ok, enter your asm start address:"));
  String asm_addr = input();
  Serial.println(F("Now enter the end address:"));
  String asm_end = input();
  while(end_addr < asm_end.toInt()){ //Keep read until end. See end_addr in EEPROMAnything.h
    String asm_code = read_String(asm_addr.toInt());
    delay(5); //Don't delete this!
    asm(asm_code);
  }
  Serial.println(F("Done execute asm code!"));
  Serial.println(F("If there any problem while execute asm code, please reset your Arduino!"));
}

void asm_edit(){ //Write asm code to eeprom
  Serial.println(F("Now enter your asm start address:"));
  String asm_addr = input();
  Serial.println(F("Now start coding, enter to create a new blank line, when done create a new blank line and press enter:"));
  String asm_code = input();
  while(asm_code != ""){ //Not end!
    String asm_code = input();
    write_String(asm_addr.toInt(), asm_code);
    delay(5); //Don't delete this!  
  }
  Serial.print(F("Remember your end address is "));
  Serial.println(end_addr_w); //See in EEPROMAnything.h
}*/
