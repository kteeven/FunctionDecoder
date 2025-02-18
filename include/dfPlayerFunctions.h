#ifndef dfPlayerFunctions
#define dfPlayerFunctions

#include "SoftwareSerial.h"
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"

void readCommand(DFRobotDFPlayerMini &obj);
void initDF(DFRobotDFPlayerMini &obj, SoftwareSerial &obj1);
void printHelp();
void printDetail(uint8_t type, int value);

#endif