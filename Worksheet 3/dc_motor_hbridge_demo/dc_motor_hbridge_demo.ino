// MEGN 200


/* **********************
 *  Global Constants    *
 * **********************/
// L293D H-bridge pins
const int ena1 = 5; // Arduino pin connected to Enable1 of H-Bridge
const int drive1A = 4; // Arduino pin connected to In1 of H-Bridge
const int drive2A = 3; // Arduino pin connected to In2 of H-Bridge

/* **********************
 *  Global Variables    *
 * **********************/
// motor control vars
bool is_running = false; // motor is off to start
int spin_speed = 0; // start at 0% duty cycle
bool In1State = LOW; // Direction pin 1 is LOW (off) to start
bool In2State = LOW; // Direction pin 2 is LOW (off) to start



void setup() {
  Serial.begin(9600); // open serial port

  pinMode(ena1,OUTPUT); // set digital pin modes to output
  pinMode(drive1A,OUTPUT);
  pinMode(drive2A,OUTPUT);
}

  
void loop() {
 
      // run motor forward at 50% duty cycle
      In1State = HIGH; In2State = LOW; spin_speed = 128;
      digitalWrite(drive1A, In1State);  
      digitalWrite(drive2A,In2State); 
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second
        
      // run motor forward (no direction change) at 100% duty cycle
      spin_speed = 255; // don't need to update direction pins
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second

      // turn motor off 
      In1State = LOW; In2State = LOW; spin_speed = 0;
      digitalWrite(drive1A, In1State);  
      digitalWrite(drive2A,In2State); 
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second

      // run motor reverse at 50% duty cycle
      In1State = LOW; In2State = HIGH; spin_speed = 128;
      digitalWrite(drive1A, In1State);  
      digitalWrite(drive2A,In2State); 
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second
        
      // run motor reverse (no direction change) at 100% duty cycle
      spin_speed = 255; // don't need to update direction pins
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second

      // turn motor off 
      In1State = LOW; In2State = LOW; spin_speed = 0;
      digitalWrite(drive1A, In1State);  
      digitalWrite(drive2A,In2State); 
      analogWrite(ena1, spin_speed); 
      delay(1000); // let run for 1 second
}
