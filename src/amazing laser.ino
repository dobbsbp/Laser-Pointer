/* This has borrowed code from both the video and comments from
https://www.youtube.com/watch?v=uJgeMjLmII8

This program recieves values from an android phone in strings
(A10) =
(B20)
(C2)

A10 mean that x axis servo position should be 10.
B20 would mean y axis servo position should be at 20.
C2 Would mean that laser is off. C1 would be laser is on.
*/

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BT1(13,12); // RX, TX

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

char unChar; // assigning unChar as a char
String readString; // assigning readString as a String

int laser = 3;

void setup() {
  myservo1.attach(9);  //X axis at pin 9
  myservo2.attach(10);  //Y axis at pin 10
  BT1.begin(115200);   // establishes bluetooth connection at 115200bps
  Serial.begin(115200); // establishes serial connection at 115200bps
}

void loop() {
  if (BT1.available()) {  //verify first character in serial port
    unChar = BT1.read();
    Serial.print(unChar); //for viewing data via serial monitor

    if(unChar=='A'){ //if A go to motor1 function
      motor1();
    }
    if(unChar=='B'){ //if B go to motor2 function
      motor2();
    }
    if(unChar=='C'){ //if A go to motor1 function
      laserSwitch();
    }
  }
}

void motor1(){
        delayMicroseconds(300);
        while (BT1.available()) { //Now the numerical data of the angle of the servomotor is received
          //delayMicroseconds(100);
          char c = BT1.read();  // Se leen los caracteres que ingresan por el puerto
          readString += c;         //each character builds in a string
        }
        if (readString.length() >0) {   //the length of the string is verified
          Serial.println(readString.toInt());  //Now we send data to serial and servos
          myservo1.write(readString.toInt());
          readString=""; // Clear string
        }
}

void motor2(){
        delayMicroseconds(300);
        while (BT1.available()) {
          //delayMicroseconds(100);
          char c = BT1.read();
          readString += c;
        }
        if (readString.length() >0) {
          Serial.println(readString.toInt());
          myservo2.write(readString.toInt());
          readString="";
        }
}

void laserSwitch(){
        delayMicroseconds(300);
        while (BT1.available()) { //Now the numerical data of the angle of the servomotor is received
          //delayMicroseconds(100);
          char c = BT1.read();  // Se leen los caracteres que ingresan por el puerto
          readString += c;         //each character builds in a string
        }
        if (readString.length() >0) {   //the length of the string is verified
          Serial.println(readString.toInt());  //Now we send data to serial and servos
          myservo1.write(readString.toInt());
          if (readString.toIn == 1) digitalWrite(laser, high);
          if (readString.toIn ==  2) digitalWrite(laser, low);
          }

          readString=""; // Clear string
        }
}
