#include <Servo.h>

const int servo1 = 3;       // first servo
const int servo2 = 10;       // second servo
const int joyH = 3;        // L/R Thumbstick at A3 port
const int joyV = 4;        // U/D Thumbstick at A4 port
const int laser = 5;      // Laser Pointer Digital Pin 5, connected to relay
const int btnlaser = 6;    // Button for laser to turn on or off
const int led = 13;       //status light.

float x;        // x value input from bluetooth will be float value
float y;        // y value input from bluetooth will be float value
float xMIN = -10.0; // setting x input minimum value
float xMAX = 10.0;  // setting x input maximum value
float yMIN = -10.0; // setting y input minimum value
float yMAX = 10.0;  // setting y input maximum value

int servoVal;           // variable to read the value from the analog pin

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo



void setup() {
  pinMode(laser, OUTPUT);
  pinMode(btnlaser, INPUT_PULLUP);
  // Servo
  myservo1.attach(servo1);  // attaches the servo
  myservo2.attach(servo2);  // attaches the servo

/*
I think this is where the bluetooth code goes i think
*/

  // Inizialize Serial
  Serial.begin(9600);
}


void loop(){

    int laserstate = digitalRead(btnlaser); //this sets the laser button state each cycle
    digitalWrite(laser, laserstate);        //this turns laser on or off depending on laserstate

    // Display Joystick values using the serial monitor
    outputJoystick();

    // Read the horizontal joystick value  (value between 0 and 1023)
    servoVal = analogRead(joyH);
    servoVal = map(servoVal, 0, 1023, 0, 180);     // scale it to use it with the servo (result  between 0 and 180)

    myservo2.write(servoVal);                         // sets the servo position according to the scaled value

    // Read the horizontal joystick value  (value between 0 and 1023)
    servoVal = analogRead(joyV);
    servoVal = map(servoVal, 0, 1023, 70, 180);     // scale it to use it with the servo (result between 70 and 180)

    myservo1.write(servoVal);                           // sets the servo position according to the scaled value

    delay(15);                                       // waits for the servo to get there
    int x1 = round((x+10)*9);  // x1 is the converted x value from phone data
    int y2 = round((y+10)*9);  // y1 is the converted y value from phone data.

}


/**
* Display joystick values
*/
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.print ("---");
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
}
