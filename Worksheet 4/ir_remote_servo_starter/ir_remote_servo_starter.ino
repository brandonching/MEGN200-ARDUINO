#include <IRremote.h>

// Set up IR reciever pin
const byte IR_RECEIVE_PIN = 3;
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
// Create variable to store value recieved from the ir remote
int ir_command;
int correct_code;
int passcode[] = {12, 24, 94, 8};

void setup()
{
   Serial.begin(9600);  // start serial monitor to visualize data
   Serial.println("IR Receive test");   // print initial message
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // start IR receiver library
   irrecv.enableIRIn();
}

void loop() {
   if (IrReceiver.decode()) // Perform an action only if a command is recieved from the IR remote
   {
      ir_command = IrReceiver.decodedIRData.command;   // Decode IR remote button press signal data
      //Serial.println(ir_command); // Print decoded IR remote button press signal signal received


      
      switch(ir_command){ // Switch statement that exectures code in each case for desired button press
        
        case 69: Serial.println("Armed"); break;
        case 71:
        Serial.println("Please Enter Password to Disarm");
        for (int digit = 0; digit<=3; digit++) {
          delay(500);
          IrReceiver.resume();
          while (!irrecv.decode()) {
            // DO NOTHING AND WAIT FOR BUTTON PRESS
          } 
          if (IrReceiver.decode()) {
            ir_command = IrReceiver.decodedIRData.command;
          }
          
          if (ir_command == passcode[digit]){
            Serial.println("Correct Digit");
            correct_code++;
            Serial.println(correct_code);
          } else {
            Serial.println("Wrong Digit");
          }
        }

        if (correct_code == 4) {
            Serial.println("Correct Passcode");
            Serial.println("System Dis-Armed");
          } else {
            Serial.println("Wrong Passcode");
          }
        correct_code = 0;  
        break;
        
      } // End Switch case structure
      delay(50);
      
      
  
      // Resume waiting for the next IR remote button press
      IrReceiver.resume();
   }  // End IR receiver decode if statement after button pressed
} // End void loop, head back to the top of the void loop again
