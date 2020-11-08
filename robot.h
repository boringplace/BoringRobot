#ifndef BORINGROBOT_H
#define BORINGROBOT_H

class Robot
{
  const char* name;

  public:
    Robot();

    void init(const char* robotName);
    void poll();
    void status(const char*);

};

#endif
