#include "robot-config.h"
void auton(void){
    Drivetrain.setDriveVelocity(-30, percent);
    intake.setVelocity(100, percent);
    wait(1500, msec);
}