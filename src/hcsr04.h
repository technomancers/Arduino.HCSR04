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
#ifndef hcsr04_h
#define hcsr04_h

#include "Arduino.h"

class HCSR04
{
  public:
    HCSR04(int trigPin, int echoPin);
    int distance(float speedOfSound);
    void setRetry(bool retry);
    void setNumRetries(int retries);
    void setBadValue(int badValue);
    void setMinTolerance(int minTol);
    void setMaxTolerance(int maxTol);
  private:
    unsigned int _echoInMicroseconds();
    int _trigPin;
    int _echoPin;
    bool _retry = true;
    int _retries = 100;
    int _badValue = -1;
    int _minTol = 0;
    int _maxTol = 500;
};

#endif
