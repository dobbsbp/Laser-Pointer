#include <Servo.h>
#include <SoftwareSerial.h>
#include <VirtualShield.h>


//const int btnlaser = 6;    // Button for laser to turn on or off
//const int led = 13;       //status light.


float x;        // x value input from bluetooth will be float value
float y;        // y value input from bluetooth will be float value
float x1; //= round((x + 10) * 8) * (180 / 160);
float y1; //= round((y + 10) * 8) * (180 / 160);
float xcon; //constrained var for x
float ycon; //constrained var for y

int xpos = 90;
int ypos = 90;

Servo servoX;  // create servo object to control a servo
Servo servoY;  // create servo object to control a servo

VirtualShield shield(true);  //Are you using the virtual shield?

//The function below will receive incoming sensor values.
void onReceive(byte * buffer, byte length) {

	Accelerometer accelerometer = shield.getAccelerometer(buffer); //accelerometer data is what we want

//	Log.w("Accelerometer", "x", accelerometer.x);  // not sure how this works but it does.
//	Log.w("Accelerometer", "y", accelerometer.y);
//	Log.w("Accelerometer", "z", accelerometer.z);

  float x = accelerometer.x; //setting x to sensor x value
  float y = accelerometer.y; //setting y to sensor y value

  float xcon = constrain(x, -10.0,10.0); //constraining x and y values
  float ycon = constrain(y, -10.0,10.0);
  //taking sensor values and constraining
  //float xcon = constrain(x,-10.0,10.0);
  //loat ycon = constrain(y,-10.0,10.0);

  // processing constrained values to degrees
  float x1 = round((xcon + 10.0) * 8.0) * (180.0 / 160.0);
  float y1 = round((ycon + 10.0) * 8.0) * (180.0 / 160.0);

  int xpos = (int) x1;
  int ypos = (int) y1;
  //sending degrees to servos
  servoX.write(xpos);
  servoY.write(ypos);

    //checking button on or off state
  //  int laserstate = digitalRead(btnlaser); //this sets the laser button state each cycle
  //  digitalWrite(laser, laserstate);        //this turns laser on or off depending on laserstate

}

void setup() {
//  pinMode(laser, OUTPUT);
//  pinMode(btnlaser, INPUT_PULLUP); // Saving wire, resistor, and headaches.
  // Servo
  servoX.attach(9);  // attaches the servo
  servoY.attach(10);  // attaches the servo

  servoX.write(90);   //setting servos to 90 degrees so they are centered.
  servoY.write(90);

  shield.begin(115200); //starting up the Virtual Shield

  // adding accelerometer sensor here
	shield.addSensor(ACCELEROMETER, onReceive);
}

void loop(){

  //listening for accelerometer inputs
	shield.listen();
}
