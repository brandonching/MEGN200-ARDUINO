
/*
This program waits for the "Start Scan" push button to be pressed.
It begins a 180 degree step sweep while monitoring the analog input with a photo resistor voltage divider.
When is "sees" the brightest reading it will record it and the location.
After completing the 180 degree sweep it waits 1 second and then rotates 
to "point" at the location of the brightest location.
It then waits for the "Start Scan" push button and repeats the process when it is pressed.
 */

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // For the 28BYJ-48 w/ULN2003 driver
// 2048 steps in 360 degrees = 0.176 degrees/step

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);  // these stepper driver pins match the wiring diagram

const int Start_PB_Pin = 2;   // the number of the  Start pushbutton pin
#define Photo_Resist_Pin A0   // Arduino A0 Pin connected to the photo resistor voltage divider
int stepCount = 0;            // Stores the number of steps the motor has taken, and initializes it to zero
int Photo_Resist_Value = 0;   // Stores the value of the photo resistor voltage divider
int Bright_Light_Reading = 0; // Stores the value of the highest reading of the photo resistor voltage divider
int Bright_stepCount = 0;     // Stores the # of steps corresponding to the highest reading of the photo resistor voltage divider
int buttonState = 0;          // Variable for reading the pushbutton status
float angle = 0;              // Variable for reading the angle
float Bright_angle = 0;       // Variable for reading the highest angle

void setup()
{
  Serial.begin(9600);         // initialize the serial port to view data
  pinMode(Start_PB_Pin, INPUT); // initialize the pushbutton pin as an INPUT (INPUT requires a physical resistor with the pushbutton)
}

void loop()
{
  Bright_Light_Reading = 0; //resets Bright_Light_Reading back to 0 after each loop
  Bright_stepCount = 0;     //resets Bright_stepCount back to 0 after each loop
  Bright_angle = 0;         //resets Bright_angle back to 0 after each loop
  angle = 0;                //resets angle back to 0 after each loop
  stepCount = 0;            //resets stepCount back to 0 after each loop
  // read the state of the pushbutton value:
  buttonState = digitalRead(Start_PB_Pin);  // read the state of the pushbutton value:
  if (buttonState == HIGH)  //if the button is pressed, run the code contained in the if statement below
  {
    delay(10);                //This delay is to "de-bounce" the push button
    while (stepCount < 1024)  //1024 steps equals 180 degrees for this stepper motor
    {
    myStepper.setSpeed(10); //Keep the stepper speed at 10, higher speeds result in issues with skipping steps
    myStepper.step(1);      //Move by one step, or 360 degrees / 2048 steps = 0.176 degrees in each step through the "while" loop
    Photo_Resist_Value=analogRead(Photo_Resist_Pin);  // Read the value of the analog photoresistor
    angle = angle + 360.0/2048.0;  //Increase the angle corresponding to each stepper motor step, 2048 steps = 360 degrees
    Serial.print(angle);    //Print angle - Serial Output can be used by any Serial Monitor
    Serial.print(",");      //Comma delimited separate of data
    Serial.println(Photo_Resist_Value); //Print Photo Resistor value, then create a new line
    
    //WRITE an if statement below that causes the stepper
    //motor to locate the brightest light step position and value 
    //before it returns to starting position.
    //i.e.
    // if Bright_Light_Reading is less than or equal to the Photo_Resist_Value,
    //then assign Bright_Light_Reading to the current Photo_Resist_Value
    //assign Bright_stepCount to the current step count (called stepCount)
    //assign Bright_angle to the current angle (called angle)
    //NOTE THAT ALL OF THESE VARIABLES ARE ALREADY DEFINED.

    stepCount++; //Keeps incrementing step count by 1
    
    if (stepCount >= 1024)
      {
      //Serial.println(Bright_stepCount);           //Uncomment to output Brightest step count (if helpful)
      delay(1000);                                  //Delay for 1 second after scan and then
      //Use the myStepper.step function here to rotate back to the brightest step location found during sweep
      //Hint: consider that the stepper has already rotated 1024 steps by this point, and that negative steps rotate backwards
      Serial.println("Brightest angle, value: ");   //Print out the brightest angle and light reading to Serial Monitor
      Serial.print(Bright_angle);
      Serial.print(",");
      Serial.println(Bright_Light_Reading);
      delay(1000);                                    //Delay for 1 second
      //Use the myStepper.step function to rotate the stepper back to the original starting postion of the sweep
      //Hint: at this point, the stepper should be at the brightest location, and needs to rotate the remaining steps back to the starting position (step 0)
      delay(1000);                                    //Delay for 1 second
      }
   }  // ends the while loop after the sweep algorithm is performed
  }   // ends the push button-based if statement to reset
}     // goes back to the top of the void loop
