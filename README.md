# Stove_Reminder
This is the readme file for our project, called Stove Reminder. In here you can read all of the versions of our project as well as the updates to our code.
Changelog:

v0.0.X -
Created GitHub folder and basic documents.

v0.1.X -
Created template code for when we've got the main components working with the Arduino.

v0.2.X -
Added code for IR Sensor and deleted unused folder: "Documents".
Tweaks to the code, in terms of a more fitting threshold for the IR Sensor, as well as Serial.println(); lines, to make sure the code works.
Deleted "else if" part of code, there was no need for an else if function, "else" does the trick.
Optimization of code by creating functions instead of running everything inside of the loop.

Found code for the thermistor.

v0.3.X -
Got some code for the thermistor and combined it with the already existing code. Now the main function of the program works.
1. It checks whether the temperature is higher than the set maximum, using a thermistor.
2. It checks whether there is a pot on the stove, using an IR Sensor.

If there is no pot on the stove and the temperature is higher than the set maximum, it will remind you to turn it off, by making noise using a piezo buzzer and turning on an LED, in all other cases, nothing happens.

v0.4.X -
Re-insulated the sodded wires for the IR-sensor, sodded longer wires onto the legs of the thermistor, to extend its' reach.
Implemented the buzzer to which there was already code. Tweaked some code.

Added new code for a better way of figuring out whether the stove was out of control and a better alarming system:

If the temperature has changed more than X_min in Y minutes, and there is a pot on the stove, do nothing.
If the temperature has changed more than X_min in Y minutes, and there is no pot on the stove, then sound the alarm.
If the temperature has changed more than X_max in Y minutes, then sound the alarm.

Re-organized the wires and added another breadboard to organize like this:

Red wires = 5V
Black wires = GND
Yellow wires = Pins

Breadboard 1: Most of the wires and the important components; IR sensor and Thermistor.
Breadboard 2: LED and the newly coded buzzer.
