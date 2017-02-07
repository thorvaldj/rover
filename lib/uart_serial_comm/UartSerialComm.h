#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Command.h"

class UartSerialComm{
  private:
    SoftwareSerial serial;
    String readUartSerial();
  public:
    UartSerialComm(int rx, int tx, int baud);
    Operation getOperation(char cmd);
    Command getCommand();
};
