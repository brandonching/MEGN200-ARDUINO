int tempPin = A0; // initialize the Analog Pin to read the Thermistor
int tempReading = 0;  // initialize temp reading variable
double tempK = 0.0; // initialize temp in Kelvin variable
float tempC = 0.0;  // initialize temp in Celcius variable
float tempF = 0.0;  // initialize temp in Fahrenheight variable
long curtime = 0;   // initialize sampling time tracking variable

void setup() {
  Serial.begin(9600); // initialize the serial connection for data collection
}

void loop() {
  tempReading = analogRead(tempPin);  // read the analog pin connected to the thermistor output
  // below is the algorithm based on the data sheet and calibration to convert voltage reading to temperature in Kelvin
  tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  
  tempC = tempK - 273.15;             // conversion from Kelvin to Celcius
  tempF = (tempC * 9.0)/ 5.0 + 32.0;  // conversion from Kelvin to Fahrenheit
  curtime = millis();       // variable to keep track of sample time (if needed for data processing)
  Serial.print(curtime); Serial.print(","); // print current time to keep track of sample time (if needed for data processing), with a comma delimeter to separate values
  Serial.println(tempC);    // print thermistor temperature in Celcius
  
  delay(500);   // this delay slows the code down so the data collects slower and is more readable
}
