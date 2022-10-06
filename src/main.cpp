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
// Drivetrain           drivetrain    1, 2, 20, 21    
// flywheel             motor_group   3, 4            
// intake               motor_group   5, 6            
// pneumaticS           digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
//#include "robot-config.cpp"
using namespace vex;

float myVariable;

bool digitalOn;

event message1 = event();

// "when started" hat block
int whenStarted1() {
  pneumaticS.set(true);
  digitalOn = true;
  return 0;
}

// "when Controller1 ButtonR1 pressed" hat block
void onevent_Controller1ButtonR1_pressed_0() {
  if (digitalOn) {
    pneumaticS.set(false);
    wait(0.1, seconds);
    digitalOn = false;
  }
  else {
    pneumaticS.set(true);
    wait(0.1, seconds);
    digitalOn = false;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drivetrain.setDriveVelocity(100.0, percent);
  flywheel.setVelocity(100.0, percent);
  intake.setVelocity(100.0, percent);
  Controller1.ButtonR1.pressed(onevent_Controller1ButtonR1_pressed_0);
  wait(15, msec);
  whenStarted1();
}
