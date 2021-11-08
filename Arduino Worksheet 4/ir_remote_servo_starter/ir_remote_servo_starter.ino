#include <IRremote.h>
#include <Servo.h>

// Set up IR reciever pin
const byte IR_RECEIVE_PIN = 3;
// Create variable to store value recieved from the ir remote
int ir_command;
// Create Servo object
Servo myservo;
// Create servo position variable, start at 90 degrees
int servopos=90;
// Set an initial increment that the up/down arrows will move the servo (in degrees)
int increment=10;

void setup()
{
   Serial.begin(9600);  // start serial monitor to visualize data
   Serial.println("IR Receive test");   // print initial message
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // start IR receiver library
   myservo.attach(9); // Servo signal wire on pin 9
   myservo.write(servopos); // Start servo at initial value of servopos variable
}

void loop()
{
   if (IrReceiver.decode()) // Perform an action only if a command is recieved from the IR remote
   {
      ir_command = IrReceiver.decodedIRData.command;   // Decode IR remote button press signal data
      //Serial.println(ir_command); // Print decoded IR remote button press signal signal received

      /*   No changes needed above */
      
      /*  Use the serial monitor to figure out what code each remote button 
       *  gives when pressed.  Use in a switch-case structure below to move the servo
       *  depending on which is button pressed. Make sure to press the buttons and set
       *  the case numbers to the appropriate button press. Two example case structures
       *  are shown below for reference, but need to be customized for your remote. 
       *  Remember to include a break statement after each case, and use Serial.println();
       *  statements for debugging to make sure the buttons are registering correctly.
       */
       
      switch(ir_command){ // Switch statement that exectures code in each case for desired button press
        case 69: servopos=90; Serial.println("Power, 90 deg"); break;   //Go to 90 degrees if power button is pushed
        case 70: increment = increment + 1; Serial.print("Increment + 1:"); Serial.println(increment); break;    // Go to 0 degrees if rewind is pushed
        case 21: increment = increment - 1; Serial.print("Increment - 1:"); Serial.println(increment); break;   // If fast forward (>>|) is pushed, go to 180 degrees, include Serial.println(); statement
        case 67: servopos=180; Serial.println("Fast forward, 180 deg"); break;   // If UP arrow is pushed, increase servopos variable by positive increment, include Serial.println(); statement
        case 68: servopos=0; Serial.println("Rewind, 0 deg"); break;   // If DOWN arrow is pushed, decrease servopos variable by positive increment, include Serial.println(); statement
        case 9: servopos=servopos + increment; Serial.print("Move: +"); Serial.println(increment); break;   // if VOL+ is pressed, adjust increment up by 1, Serial.println(); print the increment
        case 7: servopos=servopos - increment; Serial.print("Move: -"); Serial.println(increment); break;   // if VOL- is pressed, adjust increment down by 1, Serial.println(); print the  increment
      } // End Switch case structure
      
      
      if (servopos > 180) { // Use an if statement here to make sure servopos isn't greater than 180 (highest servo angle)
        servopos = 180; Serial.println("Position can't be set above 180. Angle set to 180");
      } else if (servopos < 0 ) { // Use an if statement here to make sure servopos isn't less than 0 (lowest servo angle)
        servopos = 0; Serial.println("Position can't be set below 0. Angle set to 0");
      }
      if (increment < 1) { // Use an if statement here to make sure increment isn't less than 1 (lowest increment)
        increment = 1; Serial.println("Increment can't be less than 1. Increment set to 1");
      }
      
      
      /*   No changes needed below */
      
      // Move servo to new position, just need to update servopos variable above
      myservo.write(servopos);
      // Need at least a 20 ms delay in between myservo.write(); function calls to allow servo to catch up, 50 ms delay chosen here
      delay(50);
      // Resume waiting for the next IR remote button press
      IrReceiver.resume();
   }  // End IR receiver decode if statement after button pressed
} // End void loop, head back to the top of the void loop again
