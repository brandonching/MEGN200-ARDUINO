/*
LCD + Ultrasonic Sensor Measurement Code
By Jeff Ackerman
10/11/21
*/

// Note: you will only change the code in the void loop
// the global variables and void setup(){} are already defined here

// include the LCD library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// note: this pin setup and wiring layout is specific to the LCD screen in the Elegoo kit

// include the SR04 Ultrasonic Sensor library and setup the pins
#include "SR04.h"
#define TRIG_PIN 4  // chose pin 4, but any digital pin could be used as the trig_pin
#define ECHO_PIN 2  // chose pin 2, but any digital pin could be used as the echo_pin
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);  // setup the pins for the SR04 library
long a; // define long variable a to store the distance values
long datum = 0; // define datum variable that will change when button is pressed
// Note: the datum starts at 0
// the datum should be re-defined to the current distance when the button is presses
// you will be measuring distance relative to the datum (positive or negative)

int push = 13;  // setup pushbutton pin
int button_state = 0; // setup pushbutton pin state to digital read pushbutton

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // the LCD has 16 characters and 2 rows
  pinMode(push,INPUT_PULLUP); // define the push button to be an input pulled up to HIGH
}

// you only need to write code in the void loop below
// you shouldn't need to modify any code given above, but you should review it

void loop() {
  button_state = digitalRead(push);// do a digitalRead of the button pin push, assign value to variable button_state
  lcd.setCursor(0, 0); // set the cursor to column 0, line 0 (1st row and 1st column)
  // (note: row counting starts with 0):
    // i.e. lcd.setCursor(column, row);
  a=sr04.Distance();// read the ultrasonic distance sensor value and store it as the variable a
  lcd.print("Distance: "); // lcd.print the text "Distance: "
  lcd.print(a-datum);// lcd.print the current distance a minus the datum (a-datum)
  lcd.print("cm");// lcd.print the distance units "cm"
  lcd.setCursor(0, 1);// set the cursor to column 0, line 1 (1st row and 1st column)
    // i.e. lcd.setCursor(column, row);
  lcd.print("Datum: ");// lcd.print "Datum: " text
  lcd.print(datum);// lcd.print the datum value
  lcd.print("cm");// lcd.print the distance units "cm"
  // create an if statement for when the button is pressed
  if (button_state == LOW) { // i.e. if the variable button_state is LOW, the button is pressed
    lcd.clear(); // when the button is pressed, clear the LCD screen using lcd.clear();
    datum = a; // re-define the variable datum to be equal to the current distance a
    delay(500); // delay for 500 ms
  } // end the if statement
  delay(500); // delay for 500 ms to slow down the code
  lcd.clear(); //Clears the display otherwise when going from the 10s to 1s you get 3cmm with an extra m

}
