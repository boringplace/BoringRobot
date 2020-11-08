#include "util.h"

#include <Arduino.h>

void log(const char* logLine) {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println(logLine);
}

void log(const char* logLine, int value) {
  Serial.print(millis());
  Serial.print(": ");
  Serial.print(logLine);
  Serial.println(value);
}

void log(const char* logPrefix, const char* logLine) {
  Serial.print(millis());
  Serial.print(": ");
  Serial.print(logPrefix);
  Serial.print(": ");
  Serial.println(logLine);
}
