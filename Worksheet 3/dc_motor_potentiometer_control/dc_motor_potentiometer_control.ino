/*
 Using an H Bridge and joystick to turn on a motor with variable speed and direction.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduinos, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.
 */

int enable = 5; // the PWM-capable digital pin the transistor is attached to
int dir1 = 4;   // direction 1 pin
int dir2 = 3;   // direction 2 pin
int intensity = 0;    // how fast the motor should spin from 0 to 255
int joystick_y = A1;  // read one joystick axis
int joystick_button = 2;  // read built-in joystick button
int button_pressed = 0;
bool activate = true; // boolean value to toggle motor on/off

// the setup routine runs once when powered on or you press reset:
void setup() {
  // declare output pin to be an output:
  pinMode(enable, OUTPUT);  // enable pin is an output
  pinMode(dir1, OUTPUT);    // direction 1 pin is an output
  pinMode(dir2, OUTPUT);    // direction 2 pin is an output
  // declare analog input pin to be a normal input:
  pinMode(joystick_y, INPUT);
  // declare digital input pin to be an input with a big resistor that pulls the signal to high by default
  pinMode(joystick_button, INPUT_PULLUP);
  // start serial communication so we can view the data using the Serial Plotter or Monitor
  Serial.begin(9600);
}

// the loop routine runs over and over again as long as the Arduino has power:
void loop() {
  // activate and deactivate the system using the joystick push button like a toggle switch
  button_pressed = digitalRead(joystick_button);
    if(button_pressed == 0){ // if joystick button is pressed, should be LOW when pressed due to INPUT_PULLUP
    activate = !activate;// toggle activate variable, consider using not operator (!) or if/else here
    // this is very similar to the toggle button code - here we're toggling the motor to be on and off
    delay(500);   // toggle button debounce
    }
  
  if(activate==true){  // if the system is activated
  // read horizontal joystick axis potentiometer value
  intensity = analogRead(joystick_y);
  // serial.print the raw analogRead data which will show values from 0 to 1023
  Serial.print(intensity);Serial.print(",");
  // the analogRead function outputs a 10 bit signal, or a maximum of 2^10 = 1024 data points
  // the analogWrite function outputs an 8 bit signal, or a maximum of 2^8 = 256 data points
  // we need to map the 10 bit analogRead range from 0-1023 or the 8 bit analogWrite range from 0-255
  if (intensity >= 600){ // if joystick pushed to the right, intensity is above 600
    Serial.print("Forward,");
    intensity = map(intensity,600,1023,0, 255);
    analogWrite(enable, intensity);// use analogWrite to write intensity to the enable pin
    // use two digitalWrites to make the motor spin in one direction (clockwise)
    digitalWrite(dir1, HIGH);  
    digitalWrite(dir2, LOW); 
    
  }
  else if ( intensity <= 400 ){ // if joystick pushed to the left, intensity is below 400
    Serial.print("Backward,");
    intensity = map(intensity,400,0,0, 255);  // map 
    analogWrite(enable, intensity);// use analogWrite to write intensity to the enable pin
    // use two digitalWrites to make the motor spin in the other direction (counter-clockwise)
    digitalWrite(dir1, LOW);  
    digitalWrite(dir2, HIGH); 
    
  }
  else if ( intensity > 400 && intensity < 600) { // if joystick is idle in the center, intensity is between 400 to 600
    Serial.print("Off,");
    analogWrite(enable, 0);// use analogWrite to output 0 to the enable pin
    // use two digitalWrites to make the motor not spin in either direction (i.e. set both LOW)
    digitalWrite(dir1, LOW);  
    digitalWrite(dir2, LOW); 
    
  }
  // serial.print the mapped intensity values which will show values from 0 to 255 for forward and backward
  Serial.print(intensity);Serial.println("");
  }

  // if the system is deactivated, turn off the motor
  else{
    Serial.println("Deactivated");
    // analogWrite 0 to the enable pin so it doesn't spin
    // use two digitalWrites to make the motor not spin in either direction (i.e. set both LOW)
    
  }
  
  delay(100); // overall system delay to slow things down
}
