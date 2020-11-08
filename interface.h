#ifndef BORINGROBOT_INTERFACE_H
#define BORINGROBOT_INTERFACE_H

class Robot;

class RobotInterface
{
  Robot &robot;

  public:
    RobotInterface(Robot &_robot): robot(_robot) {}
};

inline RobotInterface &interface(Robot& _robot = 0)
{
    static RobotInterface robotInterface(_robot);
    return robotInterface;
}

#endif
