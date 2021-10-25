#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

// Define LED Pins
#define BLUE 3
#define GREEN 5
#define RED 6

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// define variables
int redValue;
int greenValue;
int blueValue;

void loop() {
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  delay(100);

  #define delayTime 10 // fading time between colors

  if (a < 10) {
    redValue = 255; // choose a value between 1 and 255 to change the color.
    greenValue = 0;
    blueValue = 0;
  } else if (a <= 15) {
    redValue = 255; // choose a value between 1 and 255 to change the color.
    greenValue = 255;
    blueValue = 0;
  } else {
     redValue = 0; // choose a value between 1 and 255 to change the color.
    greenValue = 255;
    blueValue = 0;
  }
  
  //Use analogWrite to output the color value to the corresponding color pin.
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  delay(delayTime);


   
}
