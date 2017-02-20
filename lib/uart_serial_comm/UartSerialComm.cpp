#include "UartSerialComm.h"


UartSerialComm::UartSerialComm(int rx, int tx, int baud):serial(rx,tx){
  serial.begin(baud);
  serial.println("initializes rf connection");
};

Operation UartSerialComm::getOperation(char cmd){
  switch (cmd) {
    case 'f': return FORWARD;
    case 'b': return REVERSE;
    case 'l': return LEFT;
    case 'r': return RIGHT;
    case 'z': return REWIND;
    default:  return NONE;
  }
}

Command UartSerialComm::getCommand(){
    //parsing the one char operation code and value, [o]_[value]
    String input = readUartSerial();

    Operation op = getOperation(input[0]);
    int value = -1;

    if(op!=NONE){
      if(input.indexOf('_') == 1 && input.length()>2){
        String v = input.substring(2);
        value = v.toInt();
      }
    }
    return Command{op,value};

}

String UartSerialComm::readUartSerial(){
  String serial_in="";
  if(serial.available()){
    serial_in  = serial.readStringUntil('\\');
    Serial.println(serial_in);

    serial.flush();
  }
  return serial_in;
}
