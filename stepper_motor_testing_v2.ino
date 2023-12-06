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
  // put your setup code here, to run once:
  pinmode(driverPUL, OUTPUT);
  pinmode(driverDIR, OUTPUT);
}

void loop() {
  // Sets the High and Low periods of the PUL signal.
  // Hardcodes the DIR signal.
  digitalWrite(driverPUL, HIGH);
  digitalWrite(driverDIR, HIGH);
  delayMicroseconds(step_delay);
  digitalWrite(driverPUL, LOW);
  delayMicroseconds(step_delay);
}

// Set the speed of motor in rpm.
// The hope here is that defining the step_delay in microseconds helps acheive higher
// frequency switching on output pins.
void setSpeed(whatSpeed) {
  // Delay is in microseconds.
  step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;
}