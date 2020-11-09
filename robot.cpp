#include "util.h"
#include "robot.h"

Robot::Robot(): name("UnknownRobot") {};

void Robot::init(const char* robotName) {
  name = robotName;
}

void Robot::status(const char *newStatus) {
  log(name, newStatus);
}

void Robot::poll() {
  status("Poll");
}
