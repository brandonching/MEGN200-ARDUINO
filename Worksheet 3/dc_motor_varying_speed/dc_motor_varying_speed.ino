/* ***************************************************************
 *  DC motor using single transistor  
 *  MEGN200 - Arduino activities Week 3
 *  Fall 2020
 *  Code Written by Jordan Sturdy
 * ***************************************************************/

// Define RBG Pins
#define GREEN 6
#define RED 5

/* Global Constants */
const int speed_pin = 3; // Set digital pin connected to base of transistor

/* Global Variables */
int motor_speed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(speed_pin, OUTPUT); // using pin as output to transistor
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  analogWrite(GREEN, 255);
  // write a for loop to increment PWM from 0 to 255 and set the motor speed
  for (motor_speed = 0; motor_speed <= 255; motor_speed = motor_speed+1) { // increase duty cycle every 100th of a second until reach 100%
      analogWrite(speed_pin,motor_speed);// set motor speed (PWM with analogWrite)
      delay(10); // pause for effect (PWM will increment too fast without this)
    }
    
  delay(1000); // run motor at full speed for one second before slowing down
  analogWrite(GREEN, 0);
  
  analogWrite(RED, 255);
  // write a for loop to increment PWM from 0 to 255 and set the motor speed
  for (motor_speed = 255; motor_speed >= 0; motor_speed = motor_speed-1){ // decrease duty cycle every 100th of a second until reach 0%
      analogWrite(speed_pin,motor_speed);// set motor speed (PWM with analogWrite)
      delay(10); // pause for effect
    }
  analogWrite(RED, 0);
  delay(100); // wait breifly before starting again.


}
