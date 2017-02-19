#ifndef COMMAND_H
#define COMMAND_H

enum Operation {
      FORWARD,
      REVERSE,
      LEFT,
      RIGHT,
      REWIND,
      NONE
};

struct Command{
      Operation operation;
      int value;
};
#endif
