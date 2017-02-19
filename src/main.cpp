#include "Arduino.h"
#include <SoftwareSerial.h>
#include "UartSerialComm.h"
#include "Car.h"
#include "HC_SR04.h"

UartSerialComm uartComm(11, 10, 9600);//rx,tx,baud
Car car(1, 3, 2, 6, 5, 4);
HS_SR04 ultraSonicSensor(8,9);//triggerPin, echoPin

void setup() {
  Serial.begin(9600);
  Serial.println("======= Starting up car =======");
}

void loop(){

  long dist = ultraSonicSensor.getDistInCm();

  Serial.println(dist);

  Command cmd = uartComm.getCommand();
  car.drive(cmd);

  /*
  Serial.println("operation: ");
  Serial.println(cmd.operation);

  Serial.println("value: ");
  Serial.println(cmd.value);
  */
  delay(100);
}
