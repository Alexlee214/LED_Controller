# Description
This project is used to create a simple yet easy to use LED controller for controlling single colored LED light strips. The required components are as listed:
 * ATTiny85 microcontroller x 1
 * DIP-8 socket 
 * Perfboard x 2
 * Push button x 2
 * Photoresistor x 1
 * 4.7 ohm resistor x 1
 * 10k ohm resistor x 2
 * 12V voltage regulator with at least 5A rating
 * 12V to 5V step down converter (recommend buck converter like LM2596)
 * 5V triggered relay
 * 3mm LED light (Optional) 
 * 220 ohm resistor x 1 (Optional) 
 
 The controller box houses two buttons, one is used for switching on the LED strip on and off manually, the other one is used to switch it into auto mode:
 ### Manual Mode
 In manual mode, pressing the button turns on the LED strip gradually and preesing again turns it off
 ### Auto Mode
In auto mode, the LED light by the button lights up to indicate it is in auto mode (* Note to use auto mode, it is required to follow the initialization steps when the LED strip is first plugged in, see appendix for more information). In this mode, the LED strip turns on when the main light is turned on and turns off when the light is off. (Note that this mode may not work as well in a room with natural sunlight)



## Current functionalities
* May 24, 2018, Version 1.0.0
* Photoresistor used to detected light level so that the LED strip is synchronized with the main light source
* Push button to turn on light manually
* Single LED light to indicate that the controller is in auto mode
* LED strip uses PWN signal to turn on and off gradually


## Future improvements
* Use INT0 external interrupt for the push button
* Setup pin change interrupt for the other button
* Replace the photocell with a PIR sensor
* Instead of using a photoresistor to detect light level on the main controller, use an infared reciever, and have another device (possibly with ATTiny13 ) placed beside the main light source to send signals when the light is on (eliminates sunlight disturbance)
* Have the LED strip stay on for 5 seconds after the main light source is turned off, then detect again, if the light is still off, turn off LED strip. This is to eliminate potential incorrect photoresistor readings or obstructions such as shadows


## Appendix
* Set up:
 - Switch off all the light sources in the room
 - Plug in the LED strip
 - Wait for 1 second and the LED strip should turn on for 1 second
 - After the LED strip turns off once again, the setup process is complete
 
* Pinouts on ATTiny85
 - Pin #1 (RESET)
 - Pin #2 (pin 3 or pin A1) : LED light to indicate in auto mode
 - Pin #3 (pin 4 or pin A2) : Photoresistor 
 - Pin #4 (GROUND) : all grounds must be connected together
 - Pin #5 (pin 0 PWM) : output signal to the 5v relay
 - Pin #6 (pin 1 PWM) : push button 1 for manual mode
 - Pin #7 (pin 2 or pin A1) : push button 2 for auto mode
 - Pin #4 (VCC) : 5V coming out from the step down converter
