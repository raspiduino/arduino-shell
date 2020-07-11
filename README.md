# Arduino-shell
## A simple Unix-like shell for your Arduino! 
This is a very simple shell I have wrote for my Arduino, and I want to share it for you. If you like, you can give it a try! Thanks a lot for that :D If you want to add something new or report a bug, feel free to tell me at raspiduinogit@gmail.com
### Support Arduino Uno (ATmega328) or some of the other AVR cpus!
In the future, it will supports internet with esp8266 and it can be portable with lcd support! Hope you like it!
## Usuage
Just download the source, open shell.ino with your Arduino IDE and flash it into your Arduino! Or you can also download the pre-compiled .hex file in the releases!
## Commands list (currently version 1.0.1 - update 11/7/2020):
- hi --------------------------------- A simple command to say hello (unnecessary, you can remove it if you want)
- ver -------------------------------- Display the current version
- help ------------------------------- Display help
- ls --------------------------------- List the current storage device
- dir -------------------------------- The same with "ls"
- cpu -------------------------------- Display the current AVR cpu info. If it doesn't show anything, that's mean we cannot detect it!
- free_ram --------------------------- Display the current free amount of RAM (in bytes)
- cd --------------------------------- Change the current directory. REMEMBER: enter cd first, and then the command will ask you about the directory!
- read_eeprom ------------------------ Read the value in eeprom. It can be a string!
- edit_eeprom ------------------------ Edit the value in eeprom. It can be a string!
- clipboard -------------------------- Copy text from eeprom and paste it again in input prompt using $clipboard
### A new version which is support assembly code will be release in 20 minutes
