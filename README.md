# PaddleWar
TVOut PaddleWar game with added artwork

 Demo/Game sketch for TinyRFModulator and DisplayFoundation library project.
 
 ------
 This game was originally created by Maarten Janssen in 2015 and is converted to be able to use with TDisplayFoundation
 and TVOut. This is a demo project for TDisplayFoundation and TinyRFModulator.

 Serveral things are changed:
 - Reading controller values in percents
 - Added defines and macros, makes it easier to convert the code
 - Rebuild or remove graphics (monochrome)
 - Created some Keen artwork (monochrome)

  REQUIREMENTS
  - MCU with 32Kb program space
  - TVOut library
  - TV with RF input and TinyRFModulator
                OR
    TV with composite input
  - 10K Potentiometer as paddle input

```
  HOW TO CONNECT
  _____________
  ARDUINO      |
  NANO/    GND o-------------------------------\
  ATMEGA328    |                               _|_/|
           D11 o ------- SOUND OUT ------------[__ | SPEAKER
               |                                  \|                         RCA CONNECTOR
               |                                                             ____
           D9  o ------- VIDEO SYNC ----|__1K RESITOR ]--------- |              |______
               |                                                 |----TV--------|______)
           D7  o ------- VIDEO SIGNAL --|__470 OHM RESISTOR ] ---|          ____|
               |                                                              |
           GND o ---------------------------------------------------- TV-----/
               |                  _|_      |        _
                                  ___  1uF |_______| |_____
               |                   | +           --| |_____| 10K POTENTIOMETER LINEAIR
           AO  o ------------------|---------------|_|       (not a taper pot!)
               |
 ______________|
```

 TODO:
 - Auto alignment to any screensize


HOW TO PLAY:

This demo lets you play the PaddleWar! game from the Commander Keen series.

- Connect a 10K potentiometer to A0, +5v and GND to control your paddle. 
- Simple sounds are provided if you connect a small speaker between pin 11 and GND. 
- The game will start automatically and end when either you or the MCU reach 21 points. 
- The game restarts automatically.

SCREENSHOTS:


