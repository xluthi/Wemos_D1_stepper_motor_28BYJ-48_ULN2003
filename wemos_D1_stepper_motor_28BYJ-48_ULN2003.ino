/* Demo/Test sketch for stepper motor 28BYJ-48 controlled with an ULN2003, on an ESP8266 (Wemos D1 mini)
 *  Runs one stepper forwards and backwards, accelerating and decelerating
 *  at the limits.
 *  Derived from Celem https://pastebin.com/70QZmCj5

   Copyright (C) 2019 Xavier Lüthi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  D5     // IN1 on the ULN2003 driver 1
#define motorPin2  D6     // IN2 on the ULN2003 driver 1
#define motorPin3  D8     // IN3 on the ULN2003 driver 1
#define motorPin4  D7     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Compiled on ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);

  pinMode(LED_BUILTIN, OUTPUT);  // initialize onboard LED as output
  digitalWrite(LED_BUILTIN, HIGH);
  
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(50.0);
  stepper.setSpeed(200);
  /* 2048 == 1/2 rotation of the axis.
   * 64 steps per full rotation for the motor, to be multiplied by 64
   * (the reducing factor of the complete motor) --> 64 * 64 = 4096 steps per rotation
   * 
   * At boot, the motor will turn 1/2 rotation clockwise, then 1 turn anti-clockwise.
   */
  stepper.moveTo(2048);
  
}

void loop()
{
  //Change direction when the stepper reaches the target position
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  stepper.run();
  //Serial.println(stepper.distanceToGo());
}
