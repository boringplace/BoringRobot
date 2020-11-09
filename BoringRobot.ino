#include <IoAbstraction.h>

#include "util.h"
#include "robot.h"
#include "program.h"

IoAbstractionRef arduinoIo = ioUsingArduino();
char slotString[10] = { 0 };

static int pollTaskId = -1;
static int programTaskId = -1;
static volatile bool programStarted = false;

Robot robot;

void programTask()
{
  if (!programStarted)
    return;

  programStarted = program();
}

static void startProgram()
{
  if (programTaskId < 0) {
    programTaskId = taskManager.scheduleFixedRate(10, programTask);
    log("Start BoringRobot");
    programStarted = true;
    robot.status("Started");
  }
}

static void startStopProgram()
{
  if (programTaskId < 0) {
    startProgram();
    return;
  }

  if (!programStarted) {
    log("Restart BoringRobot");
    programStarted = true;
    robot.status("Restarted");
  } else {
    log("Stop BoringRobot");
    programStarted = false;
    robot.status("Stoped");
  }
}

static void initialRobot() {
  log("Initial BoringRobot");

  robot.init(name);
  robot.status("Ready");

  log("slots[]", taskManager.checkAvailableSlots(slotString, 10));

  pollTaskId = taskManager.scheduleFixedRate(100, [] {
    robot.poll();
  });
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  log("Setup BoringRobot");

  log("slots[]", taskManager.checkAvailableSlots(slotString, 10));

  taskManager.scheduleOnce(1000, initialRobot);
}

void loop() {
  taskManager.runLoop();
}
