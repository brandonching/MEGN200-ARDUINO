int LED_PIN = 11;  // the ~ PWM pin the LED is attached to, above void setup()

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogValue = analogRead(A0);
  int brightness = map(analogValue, 0, 1023, 0, 255);
  analogWrite(LED_PIN, brightness);
// print out the value
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Brightness: ");
  Serial.println(brightness);
  delay(100);


}
