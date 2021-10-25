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
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int lastButtonState = LOW;
int ledState = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input with an internal pullup resistor:
  pinMode(buttonPin, INPUT_PULLUP);
  // the internal 20k Ohm pullup resistor sets the button to be HIGH by default and LOW when pressed
  // the internal 20k Ohm pullup resistor also limits current through the button (just need to sense the voltage change)
}

void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  
  if (buttonState != lastButtonState) {
    delay(50);
    lastButtonState = buttonState;
    if (buttonState == HIGH) {
      if (ledState == 0) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      ledState = 1;
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      ledState = 0;
      }
  }
    
  }
}
