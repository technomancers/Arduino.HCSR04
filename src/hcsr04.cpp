/*
A library for using the HC-SR04 Ultrasonic Sensor
Copyright (C) 2018  Technomancers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Arduino.h"
#include "hcsr04.h"

HCSR04::HCSR04(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, HIGH);
  _trigPin = trigPin;
  _echoPin = echoPin;
}

int HCSR04::distance(float speedOfSound)
{
  int iteration = 0;
LOOP:
  iteration++;
  if (iteration > _retries)
  {
    return _badValue;
  }
  unsigned int duration = _echoInMicroseconds();
  int distance = (duration * speedOfSound / 2);
  if (distance < _minTol || distance > _maxTol)
  {
    if (_retry){
      delayMicroseconds(10); //Trigger pin needs to stay high for atleast 10 microseconds
      goto LOOP;
    }else{
      return _badValue;
    }
  }
  return distance;
}

unsigned int HCSR04::_echoInMicroseconds()
{
  digitalWrite(_trigPin, LOW);
  // Arduino Primo doesn't have access to pulseIn.
  while(digitalRead(_echoPin) == LOW); //Wait for the high signal
  unsigned int pulseStart = micros();
  while(digitalRead(_echoPin) == HIGH); //Wait for the low signal
  unsigned int pulse = micros() - pulseStart;
  digitalWrite(_trigPin, HIGH);
  return pulse;
}

void HCSR04::setRetry(bool retry)
{
  _retry = retry;
}

void HCSR04::setNumRetries(int retries)
{
  _retries = retries;
}

void HCSR04::setBadValue(int badValue)
{
  _badValue = badValue;
}

void HCSR04::setMinTolerance(int minTol)
{
  _minTol = minTol;
}

void HCSR04::setMaxTolerance(int maxTol)
{
  _maxTol = maxTol;
}
