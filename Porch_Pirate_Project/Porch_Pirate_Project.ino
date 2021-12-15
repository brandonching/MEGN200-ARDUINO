#include <IRremote.h>

// Limit Switch
const int limitSwitchPin = 9;

// IR-Remote
const byte IR_RECEIVE_PIN = 6;
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
int ir_ids[] = {22,12,24,94,8,28,90,66,82,74};

// 7-Segment
byte digitPins[] = {12,A0,A1,13}; //d1,d2,d3,d4
byte segmentPins[] = {7,A2,11,3,4,A3,10}; //abcdefg

// Stepper Motor
const int StepX = 2;
const int DirX = 5;

// 7-Segment Display initilization of displayable characters
String digit_ids = "0123456789SAFEPCODN- ";
int pickNumber[][7] = {
{ 1,1,1,1,1,1,0 }, // 0
{ 0,1,1,0,0,0,0 }, // 1
{ 1,1,0,1,1,0,1 }, // 2
{ 1,1,1,1,0,0,1 }, // 3
{ 0,1,1,0,0,1,1 }, // 4
{ 1,0,1,1,0,1,1 }, // 5
{ 1,0,1,1,1,1,1 }, // 6
{ 1,1,1,0,0,0,0 }, // 7
{ 1,1,1,1,1,1,1 }, // 8
{ 1,1,1,0,0,1,1 }, // 9
{ 1,0,1,1,0,1,1 }, // S
{ 1,1,1,0,1,1,1 }, // A
{ 1,0,0,0,1,1,1 }, // F
{ 1,0,0,1,1,1,1 }, // E
{ 1,1,0,0,1,1,1 }, // P
{ 1,0,0,1,1,1,0 }, // C
{ 1,1,1,1,1,1,0 }, // O
{ 1,1,1,1,1,1,0 }, // D
{ 1,1,1,0,1,1,0 }, // N
{ 0,0,0,0,0,0,1 }, // -
{ 0,0,0,0,0,0,0 } // Blank
};

// others
int ir_command;
String entered_code;
String passcode = "1234";
bool is_armed = false;
bool disarming = false;
String display_msg;

void setup(){
  Serial.begin(9600);  // start serial monitor to visualize data
  Serial.println("Porch Priate Running");   // print initial message
  // initilize stepper
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  
  // inititaze Limit Switch
  pinMode(limitSwitchPin, INPUT_PULLUP);
  
  // initialize IR
  IrReceiver.begin(IR_RECEIVE_PIN); // start IR receiver library
  irrecv.enableIRIn();
  
  // initialize the digital pins as outputs.
  for (int i = 0; i < sizeof(segmentPins); i++){ //sets segment pinMode
      pinMode(segmentPins[i], OUTPUT);
    }
  for (int i = 0; i < sizeof(digitPins); i++) { //sets digit pinModes
    pinMode(digitPins[i], OUTPUT);
  }
}

void loop() {
  armed();
  disarm();
  check_IR();
  display(display_msg);
} 

void check_IR(){
   if (IrReceiver.decode()) {// Perform an action only if a command is recieved from the IR remote
    ir_command = IrReceiver.decodedIRData.command;   // Decode IR remote button press signal data
    //Serial.println(ir_command); // Print decoded IR remote button press signal signal received
    
    switch(ir_command){ // Switch statement that exectures code in each case for desired button press
      
      case 69: Serial.println("Armed"); is_armed = true; display_msg = "    "; break;
      case 71: Serial.println("Disarming"); disarming = true; display_flashing_passcode(); break;  
    } // End Switch case structur
    delay(50);
      // Resume waiting for the next IR remote button press
      IrReceiver.resume();
   }  // End IR receiver decode if statement after button pressed
}

void display(String msg) {
  if (msg != "") {
    for (int digit = 0; digit<=3; digit++) {
        for (int i = 0; i<=3; i++) { //Clear Dispaly    
          digitalWrite(digitPins[i], HIGH);
        }
        int digit_id = digit_ids.indexOf(msg[digit]);
        for (int segment = 0; segment<=6; segment++) {
          digitalWrite(segmentPins[segment], pickNumber[digit_id][segment]);
        }
        digitalWrite(digitPins[digit], LOW);
        delay(1);
    }
  }
}

void armed(){
  int switchState = digitalRead(limitSwitchPin);
  if ((switchState == HIGH) && (is_armed == true)) {
    Serial.println("BOOM!");
    digitalWrite(DirX, HIGH);
    for(int x = 0; x<200; x++) { // loop for 200 steps
      digitalWrite(StepX,HIGH);
      delayMicroseconds(500);
      digitalWrite(StepX,LOW); 
      delayMicroseconds(500);
     }
  is_armed = false;
  display_msg = "OPEN";   
  }
}

void disarm(){
  if ((disarming == true) && (entered_code.length() == 4)) { //Checks if entered passcode is correct
    disarming = false;
    if (entered_code == passcode) {
      is_armed = false;
      display_msg = "SAFE";
    }
    entered_code = "";
  }
  if ((disarming == true) && (IrReceiver.decode())) { // when decoding take button presses as passcode inputs
    ir_command = IrReceiver.decodedIRData.command;
    for (int num = 0; num <=9; num++) {
      if (ir_command == ir_ids[num]) {
        entered_code = entered_code + num;
        break;
      }
    }
    Serial.println(entered_code);
    display_msg = entered_code;
  }
}

void display_flashing_passcode() {
  for (int mil_second = 0; mil_second <=250; mil_second++) { //Display "PASS" for 1 second
        display("PASS");
        delay(1);
      }
      for (int mil_second = 0; mil_second <=250; mil_second++) { //Display "CODE" for 1 second
          display("CODE");
          delay(1);
        }
  display_msg = "----";
}
