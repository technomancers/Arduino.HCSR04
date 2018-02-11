#include <hcsr04.h>

HCSR04 ultrasonic(12, 13);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(ultrasonic.distance(.0343));
  delay(250);
}
