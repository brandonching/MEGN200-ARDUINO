/* ***************************************************************
 *  DC motor using single transistor  
 *  MEGN200 - Arduino activities Week 3
 *  Fall 2020
 *  Code Written by Jordan Sturdy
 * ***************************************************************/


/* Global Constants */
const int speed_pin = 3; // Set digital pin connected to base of transistor

/* Global Variables */
int motor_speed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(speed_pin, OUTPUT); // using pin as output to transistor
}

void loop() {

  analogWrite(speed_pin,255);



}
