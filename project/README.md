Project 3: Graphical LCD Toy
====================================
# What the program does:
  This program will implement certain features to the MSP430
  Microcontroller. These features include making sounds, the LEDs flashin, the
  use of the buttons and the LCD dinamically changing. When you connect the
  MSP430 to the computer, it will go into the idle state which nothing will
  happen. Once you click a button, it will start sounds and the LEDs will
  start turning on and off. The following buttons will perfon the assigned
  tasks:

  S1. Will immitate a cop siren.
  
  S2. Will play the song Twinkle Little Star.

  S3. Will dim the RED LED.

  S4. Will play the song Happy Birthday.

  Apart from making sounds and turning on lights, the screen will also show a
  cop car driving around with the string "COPS" at top.

# How to compile:
  I have create a Makefile that will be easy to compile and clean the
  project. The instructions are as follows:

  make - Compile the entire project

  make load - Compile and run the project on the MSP430

  make clean - Remove all .o and .elf files
