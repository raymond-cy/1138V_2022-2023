#include "robot-config.h"
bool digitalOn;
void shooter_push() {
  if (digitalOn) {
    air.set(false);
    digitalOn = false;
    wait(15, msec);
  }
  else{
    air.set(true);
    digitalOn = true;
    wait(15, msec);
  }
}