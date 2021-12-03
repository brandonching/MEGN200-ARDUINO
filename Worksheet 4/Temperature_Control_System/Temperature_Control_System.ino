// Temperature Control System v1.0
// By Jeff Ackerman
// Serial.println(); statements are included for Serial Monitor measurement and debugging purposes

// Define Thermistor Variables
int tempPin = A0; // initialize the Analog Pin to read the Thermistor
int tempReading = 0;  // initialize temp reading variable
double tempK = 0.0; // initialize temp in Kelvin variable
float tempC = 0.0; // initialize temp in Celcius variable
float tempF = 0.0; // initialize temp in Fahrenheight variable
long curtime = 0; // initialize sampling time tracking variable
int threshold = 26; // initialize temp temperature threshold trigger variable, may need to adjust this for your hand temperature

// Define pins for DC motor with fan using the L293D h-bridge motor controller
int motorpin=5;     // initialize motor speed pin
int direction1 = 3; // initialize motor direction pin
int direction2 = 4; // initialize motor direction pin

// Define pin for the Servo Code and include the built-in Servo library
#include <Servo.h>  // include built-in servo library
Servo myservo;      // create servo object to control a servo
int servopin=9;     // initialize servo pin

void setup() {    // setup outputs, runs once when powered on
   Serial.begin(9600);  //start the Serial Monitor for debugging
   myservo.attach(servopin);  // attaches the servo on pin 9 to the servo object
   myservo.write(0);          // sets the servo position to 0 degrees initially
   pinMode(motorpin,OUTPUT);  //the motor speed pin should be set to an output
   pinMode(direction1,OUTPUT);  //the motor direction pin should be set to an output
   pinMode(direction2,OUTPUT);  //the motor direction pin should be set to an output
   delay(1000);   // wait a second before loops starts
}

void loop() { // runs continuously as long as the Arduino has power
  
  // Thermistor code here, use temperature in C (tempC) variable
  tempReading = analogRead(tempPin);
  tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  tempC = tempK - 273.15;             // conversion from Kelvin to Celcius
  tempF = (tempC * 9.0)/ 5.0 + 32.0;  // conversion from Kelvin to Fahrenheit
  Serial.println(tempC);
  
  if (tempC >= threshold) {// if statement which turns the motor on (set motor speed and a direction) and the servo angle to 90 degrees
    myservo.write(90);
    digitalWrite(direction1, HIGH);
    analogWrite(motorpin, 255);
  } else {// else statement which turns the motor off and the servo angle to 0 degrees
    myservo.write(0);
    digitalWrite(direction1, LOW);
    digitalWrite(direction2, LOW);
    analogWrite(motorpin, 0);
  }
   delay(200);  //short 200 ms delay to slow program down so the data collects slower and is more readable
   
} // end void loop, repeat as long as Arduino has power
