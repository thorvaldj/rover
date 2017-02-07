#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Command.h"

class Car{
  private:
    int a_on, a1, a2, b_on, b1, b2;
    static const int max_number_of_commands=100;
    int current_command_index=0;
    Command route[max_number_of_commands];

  public:
      Car(int a_on, int a1, int a2, int b_on, int b1, int b2);

      void drive(Command cmd);
      void addCommandToRoute(Command cmd);
      void rewindRoute();
      void forward(int ms);
      void reverse(int ms);
      void left(int ms);
      void right(int ms);

      void motorAOn();
      void motorAStop();
      void motorAForward();
      void motorAReverse();
      void motorBOn();
      void motorBStop();
      void motorBForward();
      void motorBReverse();
};
