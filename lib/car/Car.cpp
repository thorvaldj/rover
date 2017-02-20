#include "Car.h"

Car::Car(int a_on, int a1, int a2, int b_on, int b1, int b2):
a_on(a_on), a1(a1), a2(a2), b_on(b_on), b1(b1), b2(b2) {

  for( int i = 0; i < this->max_number_of_commands; ++i )
    this->route[i] = Command{ NONE, 0 };

  //initialize the output pins to control the four motors
  pinMode(a_on, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b_on, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  motorAOn();
  motorBOn();
}

void Car::addCommandToRoute(Command cmd){
  this->cci = (this->cci + 1) % max_number_of_commands;
  this->route[this->cci] = cmd;
}

void Car::rewindRoute(){
  Serial.println("rewinding");
  int shifted_index = this->cci;
  do {
    Command cmd = route[shifted_index];

    if( cmd.operation == NONE ) break;

    auto out = String( shifted_index )
             + " :: "
             + String( cmd.operation )
             + " :: "
             + String( cmd.value );
    Serial.println(out);
    switch (cmd.operation) {
      case FORWARD: reverse(cmd.value); break;
      case REVERSE: forward(cmd.value); break;
      case LEFT: right(cmd.value); break;
      case RIGHT: left(cmd.value); break;
      default: break;
    }
    
    delay(500);
    if( --shifted_index < 0 )
      shifted_index += max_number_of_commands;
  } while (shifted_index != this->cci);
  this->route[ this->cci ].operation = NONE;
}

void Car::drive(Command cmd){
  // only log drive operations
  if(cmd.operation != NONE && cmd.operation != REWIND){
    addCommandToRoute(cmd);
  }

  switch (cmd.operation) {
    case FORWARD: forward(cmd.value); break;
    case REVERSE: reverse(cmd.value); break;
    case LEFT: left(cmd.value); break;
    case RIGHT: right(cmd.value); break;
    case REWIND: rewindRoute();break;
    default: break;
  }
}

void Car::forward(int ms){
  motorAForward();
  motorBForward();
  if(ms>0){
    delay(ms);
    motorAStop();
    motorBStop();
  }
}
void Car::reverse(int ms){
  motorAReverse();
  motorBReverse();
  if(ms>0){
    delay(ms);
    motorAStop();
    motorBStop();
  }
}
void Car::left(int ms){
  motorAForward();
  motorBReverse();
  if(ms>0){
    delay(ms);
    motorAStop();
    motorBStop();
  }
}

void Car::right(int ms){
  motorAReverse();
  motorBForward();
  if(ms>0){
    delay(ms);
    motorAStop();
    motorBStop();
  }
}

void Car::motorAOn() {
  digitalWrite(a_on, HIGH);
}

void Car::motorAStop() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, HIGH);
}

void Car::motorAForward() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);

}

void Car::motorAReverse() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
}

void Car::motorBOn() {
  digitalWrite(b_on, HIGH);
}

void Car::motorBStop() {
  digitalWrite(b1, HIGH);
  digitalWrite(b2, HIGH);
}

void Car::motorBForward() {
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);

}

void Car::motorBReverse() {
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
}
