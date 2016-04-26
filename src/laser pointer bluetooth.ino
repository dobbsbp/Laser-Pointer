#include <Servo.h>
#include <SoftwareSerial.h>
#include <VirtualShield.h>


const int servo1 = 3;       // first servo
const int servo2 = 10;       // second servo
//const int joyH = 3;        // L/R Thumbstick at A3 port
//const int joyV = 4;        // U/D Thumbstick at A4 port
const int laser = 5;      // Laser Pointer Digital Pin 5, connected to relay
const int btnlaser = 6;    // Button for laser to turn on or off
const int led = 13;       //status light.

// int incomingString = 0,0;  //need to figure out input string(s)

float x;        // x value input from bluetooth will be float value
float y;        // y value input from bluetooth will be float value
// float xMIN = -10.0; // setting x input minimum value
// float xMAX = 10.0;  // setting x input maximum value
// float yMIN = -10.0; // setting y input minimum value
// float yMAX = 10.0;  // setting y input maximum value
float x1; //= round((x + 10) * 8) * (180 / 160);
float y1; //= round((y + 10) * 8) * (180 / 160);
float xcon;
float ycon;

Servo servoX;  // create servo object to control a servo
Servo servoY;  // create servo object to control a servo

VirtualShield shield(true);  //Are you using the virtual shield?

//The function below will receive incoming sensor values.
void onReceive(byte * buffer, byte length) {

	Accelerometer accelerometer = shield.getAccelerometer(buffer); //accelerometer data is what we want

	Log.w("Accelerometer", "x", accelerometer.x);  // not sure how this works but it does.
	Log.w("Accelerometer", "y", accelerometer.y);
	Log.w("Accelerometer", "z", accelerometer.z);

  float x = accelerometer.x; //setting x to sensor x value
  float y = accelerometer.y; //setting y to sensor y value
}

void setup() {
  pinMode(laser, OUTPUT);
  pinMode(btnlaser, INPUT_PULLUP); // Saving wire, resistor, and headaches.
  // Servo
  servoX.attach(9);  // attaches the servo
  servoY.attach(10);  // attaches the servo

  servoX.write(90);   //setting servos to 90 degrees so they are centered.
  servoY.write(90);

  shield.begin(115200); //starting up the Virtual Shield

  // adding accelerometer sensor here
	shield.addSensor(ACCELEROMETER, onReceive);
}

  // Inizialize Serial
//  Serial.begin(9600); // default
//  Serial.begin(115200); // for virtual shield


void loop(){

  //listening for accelerometer inputs
	shield.listen();


  //taking sensor values and constraining
  float xcon = constrain(x,-10.0,10.0);
  float ycon = constrain(y,-10.0,10.0);

  // processing constrained values to degrees
  float x1 = round((xcon + 10.0) * 8.0) * (180.0 / 160.0);
  float y1 = round((ycon + 10.0) * 8.0) * (180.0 / 160.0);

  //sending degrees to servos
  servoX.write(x1);
  servoY.write(y1);
  delay (15); //wait for sensors to move

  //checking button on or off state
  int laserstate = digitalRead(btnlaser); //this sets the laser button state each cycle
  digitalWrite(laser, laserstate);        //this turns laser on or off depending on laserstate

}
