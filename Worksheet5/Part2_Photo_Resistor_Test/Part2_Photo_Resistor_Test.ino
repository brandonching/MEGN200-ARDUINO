int Photo_Resist_Pin = A0;  // Arduino A0 pin connected to the Vout of the photo resistor voltage divider
int Photo_Resist_Value;     // Variable to store photoresistor value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // Used for debugging and to read photoresistor value
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN = 13, this LED is built into pin 13
}

// Modify the code in the void loop() below

void loop() {
  // put your main code here, to run repeatedly:
  Photo_Resist_Value = analogRead(Photo_Resist_Pin); // analogRead() the photoresistor value - will be a digial value between 0 to 1023 (0V to 5V)
  Serial.println(Photo_Resist_Value); // Serial.println() the photoresistor value to prints the value to serial monitor or plotter
  delay(100); // short delay to slow the code down and to read the Serial Monitor
  
  // add an if/else statement here; refer to the basic Blink code
  if (Photo_Resist_Value <=250) {// turn the built-in LED on pin 13 on when the photoresistor is covered
    digitalWrite(LED_BUILTIN, HIGH);
  } else { // turn the built-in LED on pin 13 off when not covered. 
    digitalWrite(LED_BUILTIN, LOW);
  }
}
