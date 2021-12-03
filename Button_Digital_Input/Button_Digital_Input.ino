/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.
*/

// constants won't change. They're used here to set pin numbers:
const int offButtonPin = 13;     // the number of the pushbutton pin
const int onButtonPin = 4;


// variables will change:
int onButtonState = 0;         // variable for reading the pushbutton status
int offButtonState = 0;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input with an internal pullup resistor:
  pinMode(offButtonPin, INPUT_PULLUP);
  pinMode(onButtonPin, INPUT_PULLUP);
  // the internal 20k Ohm pullup resistor sets the button to be HIGH by default and LOW when pressed
  // the internal 20k Ohm pullup resistor also limits current through the button (just need to sense the voltage change)
}

void loop() {
  // read the state of the pushbutton value:
  onButtonState = digitalRead(onButtonPin);
  offButtonState = digitalRead(offButtonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  if (onButtonState == LOW) {
    // turn LED on:
    Serial.println("test");
    delay(50);  // slight delay to help "debounce" the button
  }
  if (offButtonState == LOW) {
    // turn LED off:
    Serial.println("test");
    delay(50);  // slight delay to help "debounce" the button
  }
}
