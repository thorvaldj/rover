#include "Arduino.h"
#include "HC_SR04.h"

long HS_SR04::ultrasonicPingMs(){
  long duration_in_ms;
  // reset before new trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  // trigger sensor by setting pin high for 10ms
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  //reading the incoming echo pulse
  duration_in_ms = pulseIn(echoPin, HIGH);

  return duration_in_ms;
}

long HS_SR04::getDistInCm(){
  long duration_in_ms, dist_in_cm;
  duration_in_ms = ultrasonicPingMs();
  //340 m/s => 0.034 cm/microsec
  dist_in_cm = (duration_in_ms/2) * 0.034;
  return dist_in_cm;
}
