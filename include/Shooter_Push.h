#include "robot-config.h"
bool digitalOn;
void shooter_push() {
    air.set(true);
    wait(700, msec);
    air.set(false);
    wait(15, msec);
}