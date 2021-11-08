/* ***************************************************************
 *  DC motor single transistor w/ current and power measurement 
 *  MEGN200 - Arduino activities Week 3
 *  Fall 2020
 *  Code Written by Jordan Sturdy
 * ***************************************************************/


/* Global Constants */ 
const int R1in = A0; // analog pin connected to + side of 10 Ohm resistor
const int R1out = A1; // analog pin connected to - side of 10 Ohm resistor
const int speed_pin = 3; // digital pin connected to the base of the transistor
const int R1Val = 10; // shunt resistor value in Ohms
const float ADCmult = 5/1023.0; // ratio converting the 10bit ADC value to a voltage

/* Global Variables */ 
int motor_speed = 255; // use full voltage for power calculation 
int Vin = 0; // voltage at + side of 10 Ohm resistor
int Vout = 0; // voltage at - side of 10 Ohm resistor
float current = 0; // mA
float mPower = 0; // mW
  
void setup() {
  Serial.begin(9600);
  pinMode(speed_pin, OUTPUT);
  analogWrite(speed_pin, 255); // run motor at full speed
}

void loop() {

  delay(500); // don't need to read fast (you can change this if you like)
  Vin = analogRead(R1in); // read the voltage at the + side of the 10 Ohm resistor
  Vout = analogRead(R1out); // read the voltage at the - side of the 10 Ohm resistor
  delay(10);

  // calculate current and power.
  // equation for current:  I = V/R
  // equation for power:  P = IV
  
  // complete the variable assignments below
  
  current = (((Vin-Vout)*ADCmult)/10)*1000; // x1000 to convert to milliamps. Convert analog read value to voltage using ADCmult.
  
  mPower = current * (Vout*ADCmult); // motor power = mA * motor volts. Which analog read corresponds to the voltage at the + motor terminal?

  // The order of serial print commands below will ensure both variables are plotted if you open the serial plotter
  // Serial.print(); prints on the same line and Serial.println(); prints data then moves to the next line
  Serial.print(current); Serial.print(" "); Serial.println(mPower); 

}
