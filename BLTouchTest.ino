/*
  BLTouch Test

Copyright 2017 Steven Knudsen

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
THE SOFTWARE.  

*/

#define ZMIN_PIN    2 // interrupt
#define CONTROL_PIN 9 // PWM

// Arduino Pro 5V 16 MHz PWM numbers
// 1   - min value 8 us
// 255 - max value constant
// 254 - max - 1 value 2030 us

// BLTouch
// Control Function    Timing          Write value
//  Pin down           550 - 800 us    69 - 100
//  Pin up             1400 - 1600 us  175 - 200
//  Self-test          1700 - 1900 us  213 - 238
//  Alarm reset        2100 - 2400 us  255 + delayMicroseconds(2200) + 0

#define PIN_DOWN  80
#define PIN_UP    190
#define SELF_TEST 225

void setup() {
  Serial.begin(115200);
  // Might want LED for something...
  pinMode(LED_BUILTIN, OUTPUT);
  // Set to known output/state
  analogWrite(CONTROL_PIN, 0);
  // If setup called from power on event, let BLTouch run it's self test
  delay(2000);
  selfTest();
  attachInterrupt(digitalPinToInterrupt(ZMIN_PIN), alarm, RISING);
  analogWrite(CONTROL_PIN, PIN_DOWN);
}

void selfTest()
{
  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(CONTROL_PIN, SELF_TEST);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  analogWrite(CONTROL_PIN, 0);
  delay(50);
}

void alarm()
{
  Serial.println("alarm");
}
void resetAlarm()
{
  analogWrite(CONTROL_PIN, 255);
  delayMicroseconds(2200);
  analogWrite(CONTROL_PIN, 0);
  delay(5); // for good measure
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}
