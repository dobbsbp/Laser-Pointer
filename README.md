# Laser-Pointer

The Goal:
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

Conditions:

x = value from sensor
x1 = value to be used with arduino for servo motor.
x value ranges from -10.xxxxxx to 10.xxxxxx
Servo motor can only handle positive values.
The minimum value of the servo motors is 0.
The maximum value of the servo motors is 180.

The Math explained:
x1 needs to be positive (or zero) so we add the opposite value of the lowest x
value.

x1=x+10

We need to work with whole numbers so we need to round.

x1=round(x+10)

But, we also need more resolution to get 1 degree increments!

x1=round((x+10)*100)

The maximum value of x is 10.  The maximum value for servos is 180. Therefore
as the current formula stands, the maximum value is (10+10)*100 or 2000.  This
number has to be broken down into 1 degree increments out of 180 degrees.
2000/180=11.11

And here we have a formula.

x1=round(((x+10)*100)/11.11)

We can plug some values in to test this.  Let's start with the minimum value
first.
x=0

x1=round(((0+10)*100)/11.11)

x1=round((0*100)/11.11)

x1=round(0/11.11)

x1=round(0)

x1=0

x=10

x1=round(((10+10)*100)/11.11)

x1=round((20*100)/11.11)

x1=round(2000/11.11)

x1=round(180.01800180018)

x1=180

And for fun...
x=7.123456

x1=round(((7.123456+10)*100)/11.11)

x1=round((17.123456*100)11.11)

x1=round(1712.3456/11.11)

x1=round(154.1265166516652)

x1=154

Prior to a conersation with a friend, I was going to use a thumbstick to control
the movements of the servos. I might still be able to use this, but will need
to figure out bluetooth communication as it's not something I have ever worked
with before.

The ino file has been modified from the instructables project:
http://www.instructables.com/id/Arduino-2-Servos-Thumbstick-joystick/?ALLSTEPS

And here's some phone data.

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
