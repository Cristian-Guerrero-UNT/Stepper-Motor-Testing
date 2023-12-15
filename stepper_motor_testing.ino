/*
Create pulse and direction signals as per the PUL/DIR mode described in the DM860T manual.
I am aware that there are limitations to the switching speed of the Arduino pins.
Output performance has not been tested.
*/

// Define pins
int driverPUL = 6;
int driverDIR = 7;

// Variables
long step_delay; 
const int number_of_steps = 200; // Number of steps that the stepper motor is capable of.
int whatSpeed = 1; //Set speed of motor in rpm.

void setup() {
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);

  // Hardcodes the DIR signal.
  digitalWrite(driverDIR, HIGH);
  
  // The hope here is that defining the step_delay in microseconds helps acheive higher
  // frequency switching on output pins.
  step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;
}

void loop() {
  // Sets the High and Low periods of the PUL signal.
  // Note: delayMicroseconds() can only reliably produce a delay up to 16,383 microseconds.
  // https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
  // For delays greater than 16,383 microseconds (16.383 milliseconds) use delay() instead.

  // If step_delay is greater than 16,383 microseconds (whatSpeed ~ 18.3 RPM) use this sequence.
  digitalWrite(driverPUL, HIGH);
  delay(step_delay);
  digitalWrite(driverPUL, LOW);
  delay(step_delay);

  // If step_delay is less than 16,383 microseconds (whatSpeed ~ 18.3 RPM) use this sequence.
  digitalWrite(driverPUL, HIGH);
  delayMicroseconds(step_delay);
  digitalWrite(driverPUL, LOW);
  delayMicroseconds(step_delay);
}
