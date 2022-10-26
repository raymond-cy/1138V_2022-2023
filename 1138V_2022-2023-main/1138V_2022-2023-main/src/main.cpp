/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Yu Chen                                                   */
/*    Created:      Wed Oct 05 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    2, 3, 13, 20    
// intake               motor_group   9, 10           
// air                  digital_out   A               
// flywheel             motor_group   5, 6            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "endgame.h"
#include "Shooter_Push.h"
#include "auton.h"
//#include "robot-config.cpp"
using namespace vex;

float myVariable;

event message1 = event();

// "when started" hat block

int whenStarted1() {
  air.set(true);
  digitalOn = true;
  endgame_right.set(false);
  endgame_left.set(false);
  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  auton();
  vexcodeInit();
  Drivetrain.setDriveVelocity(100.0, percent);
  flywheel.setVelocity(100.0, percent);
  intake.setVelocity(100.0, percent);
  Controller1.ButtonR1.pressed(shooter_push);
  Controller1.ButtonR2.pressed(endgame);
  wait(15, msec);
  whenStarted1();
}
