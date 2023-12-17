/*
Create pulse and direction signals as per the PUL/DIR mode described in the DM860T manual.

Note: delayMicroseconds() can only reliably produce a delay up to 16,383 microseconds.
https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
For delays greater than 16,383 microseconds (16.383 milliseconds) use delay() instead.
*/


// Define pins
int driverPUL = 6;
int driverDIR = 7;

// Variables
long step_delay; 
bool useMicroseconds = true;
const int number_of_steps = 400; // Number of steps that it will take to make 1 revolution.
int whatSpeed = 1; //Set speed of motor in rpm.

void setup() {
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);

  // Hardcodes the DIR signal for Clowckwise rotation.
  digitalWrite(driverDIR, HIGH);

  // Hardcodes the DIR signal for CounterClowckwise rotation.
  // digitalWrite(driverDIR, LOW);
  
  // step_delay is first calculated in microseconds.
  step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;

  // If the combination of number_of_steps and whatSpeed produces a value that is greaater than
  // what the delayMicroseconds() function can handle, step_delay is calculated in milliseconds.
  if (step_delay > 16383) {
    step_delay = 60L * 1000L / number_of_steps / whatSpeed;
    useMicroseconds = false;
  }
}

void loop() {
  // Sets the High and Low periods of the PUL signal.
  // If step_delay is calculated in microseconds, this sequence will be used.
  if (useMicroseconds == true) {
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(driverPUL, LOW);
    delayMicroseconds(step_delay);
  }

  // If step_delay is calculated in milliseconds, this sequence will be used.
  else {
    digitalWrite(driverPUL, HIGH);
    delay(step_delay);
    digitalWrite(driverPUL, LOW);
    delay(step_delay);
  }
}
