#include "Arduino.h"

class HS_SR04{
private:
  int triggerPin;
  int echoPin;
  long ultrasonicPingMs();
public:
  HS_SR04(int triggerPin, int echoPin):triggerPin(triggerPin), echoPin(echoPin){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

  };

  long getDistInCm();



};
