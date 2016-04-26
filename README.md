# Laser-Pointer

## The Goal:
Create a laser pointer that is moved by two servo motors by using an arduino
uno, bluetooth HC-05 module, and android phone.

The values that the phone's sensors put out are X, Y, and Z values.  The
sensors read a value of 10m/s^2 while resting in their most extreme positions.  
Their values can exceed 10m/s^2 when the device is moved so my assumption is that
10m/s^2 is equal to 1g which is interesting...but not needed for this project.

Numerical values from the accelerometer sensors are floating point.  They use
6 number placements to the right of the decimal; for example 10.123456 could
be a number.

My servo motors have a limit of 180 degrees and can only handle 1 degree
increments.  This mean that there's some math that needs to happen.  I need to
limit the minimum and maximum values to +/-10.  If I were to round up or round
down the accelerometer values directly, then my increments would be limited to
9 degrees.

In other words, we need to do some math. I'll try my best to explain my math
here, hopefully you can understand what I'm doing.

## Conditions:

x = value from sensor
x1 = value to be used with arduino for servo motor.
x value ranges from -10.xxxxxx to 10.xxxxxx
Servo motor can only handle positive values.
The minimum value of the servo motors is 0.
The maximum value of the servo motors is 180.

## The Math explained:

I came up with the following.

>float x = sensorx;  //not sure what to call this just yet

>float xcon = constrain(sensorx,-10.0, 10.0);  //this constrains values between -10 to 10

>float x1 = round((xcon + 10.0) * 8.0) * (180.0 / 160.0);  //converts x to degrees.`

### So in steps it's like this:
1. Assign the value from the sensor to x.
2. Take the sensor value and constrain it to values between -10 and 10.
3. Convert the constrained value of x (xcon) and convert it to a degree range of 0-180. (The math here can vary.  I created a different formula but this one looks tidy. Thanks Dan!)

## Some thoughts and Ponderings:

Prior to a conversation with a friend, I was going to use a thumbstick to control
the movements of the servos. I might still be able to use this, but will need
to figure out bluetooth communication as it's not something I have ever worked
with before.

The ino file has been modified from the instructables project:
http://www.instructables.com/id/Arduino-2-Servos-Thumbstick-joystick/?ALLSTEPS

## And here's some phone data:

This block is the data output from the VirtualShield app.

`
[LOG] Shield = 2

[Accelerometer] x = -0.575

[Accelerometer] y = 1.887

[Accelerometer] z = 10.017

`

Z axis can be ignored for this project.

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
