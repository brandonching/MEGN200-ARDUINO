/* RGB LED color picker
 *  Cycles through colors, then displays the RGB value 
 *  of the current color when a button is pushed
 *  Dr. Wheeler, 3/7/2021
 */
// Include LCD library 
#include <LiquidCrystal.h>

// Set up LCD pins
LiquidCrystal lcd(7,8,9,10,11,12);
// Store variables for RGB LED pins (Use PWM pins)
int blue = 6;
int green = 5;
int red = 3;
// Variables to keep track of color value
int redValue=255;
int greenValue=0;
int blueValue=0;
// Pin to sense button press
int button = 2; // Interrupts only allowed on pins 2 and 3!
// Variable to keep track of button state
volatile bool toggle = 1;
// Variable to keep track of what time the button was pushed for debouncing
volatile int startTime=micros();

// Interrupt function, executes when button is pressed
void buttonPress(){ 
  // Debounce button
  if (micros()-startTime>100000){
  toggle = !toggle; // Switch state of toggle variable
  Serial.println(toggle); // Useful for troubleshooting
  startTime=micros(); // Reset debounce timer
  if (toggle == 0){ // If the user stops the color cycling
  // Print out RGB values
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RGB Value:");
  lcd.setCursor(0,1);
  lcd.print("(");
  lcd.print(redValue);
  lcd.print(",");
  lcd.print(greenValue);
  lcd.print(",");
  lcd.print(blueValue);
  lcd.print(")");  
  }
  
  else{ // If the user pushes the button to restart color cycling
    /*
     * Put LCD commands here to display 
     * RGB Color Picker
     * Select color
     */
  }
  }
}

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Set up RGB pins
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  // Set up button pin
  pinMode(button,INPUT_PULLUP);
  // Set up interrupt on button press, triggers function buttonPress
  attachInterrupt(digitalPinToInterrupt(button), buttonPress, FALLING);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("RGB Color Picker");
  // Print to second line of LCD
  lcd.setCursor(0,1);
  lcd.print("Select color");
}

void loop() {
int delayTime = 10; //Controls speed of color cycling

if (toggle == 1){ //If the button is not pushed, cycle through colors
  
for(int i = 0; i < 255; i += 1) // fades out red bring green full when i=255
{
redValue -= 1;
greenValue += 1;
analogWrite(red, redValue);
analogWrite(green, greenValue);
if (toggle == 0){ // If the button is pushed, stop cycling
  break;
}
}
delay(delayTime);


redValue = 0;
greenValue = 255;
blueValue = 0;

for(int i = 0; i < 255; i += 1) // fades out green bring blue full when i=255
{
greenValue -= 1;
blueValue += 1;
analogWrite(green, greenValue);
analogWrite(blue, blueValue);
if (toggle == 0){ // If the button is pushed, stop cycling
  break;
}
delay(delayTime);
}

redValue = 0;
greenValue = 0;
blueValue = 255;

for(int i = 0; i < 255; i += 1) // fades out blue bring red full when i=255
{
blueValue -= 1;
redValue += 1;
analogWrite(blue, blueValue);
analogWrite(red, redValue);
if (toggle == 0){ // If the button is pushed, stop cycling
  break;
}
delay(delayTime);
}
}
else{ // If the button has been pushed to stop the cycling
  // Write current RGB values
  /*
   * Put code to write current RGB value here
   */
}
}
