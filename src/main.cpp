// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2, 13, 20    
// flywheel             motor_group   3, 4            
// intake               motor_group   5, 6            
// pneumaticS           digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2, 19, 20    
// flywheel             motor_group   3, 4            
// intake               motor_group   5, 6            
// pneumaticS           digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
void shooter(){
    pneumaticS.set(false);
    wait(0.2, seconds);
    pneumaticS.set(true);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  whenStarted1();
  Drivetrain.setDriveVelocity(100.0, percent);
  flywheel.setVelocity(100.0, percent);
  intake.setVelocity(100.0, percent);
  Controller1.ButtonR1.pressed(shooter);
  wait(15, msec);
}
