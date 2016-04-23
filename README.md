# Laser-Pointer

These are some notes and thoughts.

The ino file has been modified from the instructables project:
http://www.instructables.com/id/Arduino-2-Servos-Thumbstick-joystick/?ALLSTEPS

180 degrees
Resting position is in middle (90 degrees)

Resting position
x:0
y:0
z: 10

pointing left (phone rotates left)
x:10
y:0
z:0

pointing right (phone rotates right)
x:-10
y:0
z:0

Pointing up
x:0
y:10
z:0

Pointing down
x:0
y:-10
z:0

From resting poisition, servos have movement ability of +/-90 degrees.
Left/Right movement is on X axis.
Up/Down movement is on Y axis.

input values for servo range from 0 to 180.
Output values for accelerometer are -10 to 10
Output values should not exceed +/-10
Data from android has values with two interger placements and 6 decimal, example 12.123456.
Note:

/* this needs work.  Because of rounding to nearest integer, the values currently have a resolution of 9 degrees.

I think output values need to be multiplied by 10, rounded, and then brought back to a valid degree.

Output values need to be processed with following formula:
x1 = round((x+10)*9)  // x1 is the converted x value from phone data
y2 = round((y+10)*9)  // y1 is the converted y value from phone data.

This formula translates values of -10 to 10 into a value between 0 and 180

Also, these x1 and y1 values need to be rounded to the nearest integer as floating point does not work with the
arduino servo library.

*/


Note: Z axis can be ignored as it performs no function.
