#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

int CA1, CA2, CA3, CA4;
bool BtnL1, BtnL2, BtnR1, BtnR2, BtnA, BtnB, BtnX, BtnY, BtnUp, BtnDown, BtnLeft, BtnRight;

double kCA1 = 0.75;  //右摇杆转弯系数
double kCA2 = 1;   //右摇杆直走系数
double kCA3 = 0.5;   //左摇杆直走系数
double kCA4 = 0.3;   //左摇杆转弯系数
double blindCA = 5;
int batteryalert_level=20;
int controlmode = 1;

int flage = 1;
int flage1 = 1;
int flage2 = 0;
int flage3 = 0;
int flage4=0;
int flage5=0;
int flage6=0;
int flage7=0;
int flage8=0;
int flage9=0;
int flage10=0;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT2, ratio18_1, true);
motor leftMotorB = motor(PORT3, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT13, ratio18_1, false);
motor rightMotorB = motor(PORT20, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1.4);
motor intakeMotorA = motor(PORT9, ratio18_1, true);
motor intakeMotorB = motor(PORT10, ratio18_1, true);
motor_group intake = motor_group(intakeMotorA, intakeMotorB);
digital_out air = digital_out(Brain.ThreeWirePort.A);
digital_out endgame = digital_out(Brain.ThreeWirePort.B);
motor flywheelMotorA = motor(PORT5, ratio18_1, true);
motor flywheelMotorB = motor(PORT6, ratio18_1, false);
motor_group flywheel = motor_group(flywheelMotorA, flywheelMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;
bool DrivetrainNeedsToBeStopped_Controller1 = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

double p;
double i;
double d;

bool initializing = false;
bool SCREEN_ON =true;//false为所有屏幕关闭
bool BSCREEN_ON =true;//false为主机屏幕关闭
bool CSCREEN_ON =true;//false为遥控器屏幕关闭
int lock2 = 48;
int lock3 = 0;

void LeftVol(int vol_input) {
  leftMotorA.spin(fwd, 0.12*vol_input, voltageUnits::volt);
  leftMotorB.spin(fwd, 0.12*vol_input, voltageUnits::volt);
    // LeftMotor3.spin(fwd, 0.12*vol_input, voltageUnits::volt);
}

void RightVol(int vol_input) {
  rightMotorA.spin(fwd, 0.12*vol_input, voltageUnits::volt);
  rightMotorB.spin(fwd, 0.12*vol_input, voltageUnits::volt);
    // RightMotor3.spin(fwd, 0.12*vol_input, voltageUnits::volt);
}

void BaseMotorStop(int mode = 0) {
  if (mode == 2) {
    leftMotorA.stop(hold);
    rightMotorA.stop(hold);
    leftMotorB.stop(hold);
    rightMotorB.stop(hold);
  }
  else if (mode == 1) {
    leftMotorA.stop(brake);
    rightMotorA.stop(brake);
    leftMotorB.stop(brake);
    rightMotorB.stop(brake);
  }
  else {
    leftMotorA.stop(coast);
    rightMotorA.stop(coast);
    leftMotorB.stop(coast);
    rightMotorB.stop(coast);
  }
  
}
// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {

    CA1 = Controller1.Axis1.position();
    CA2 = Controller1.Axis2.position();
    CA3 = Controller1.Axis3.position();
    CA4 = Controller1.Axis4.position();
    BtnL1 = Controller1.ButtonL1.pressing();
    BtnL2 = Controller1.ButtonL2.pressing();
    BtnR1 = Controller1.ButtonR1.pressing();
    BtnR2 = Controller1.ButtonR2.pressing();
    BtnA = Controller1.ButtonA.pressing();
    BtnB = Controller1.ButtonB.pressing();
    BtnX = Controller1.ButtonX.pressing();
    BtnY = Controller1.ButtonY.pressing();
    BtnUp = Controller1.ButtonUp.pressing();
    BtnDown = Controller1.ButtonDown.pressing();
    BtnLeft = Controller1.ButtonLeft.pressing();
    BtnRight  = Controller1.ButtonRight.pressing();   
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    if( controlmode == 0 && !BtnA && ( abs(CA1)>blindCA || abs(CA2)>blindCA  ) ) {
        LeftVol( CA2 * kCA2 + CA1 * kCA1  ) ;
        RightVol( CA2 * kCA2 - CA1 * kCA1  );
      }
    else if( controlmode ==1 && !BtnA && (  abs(CA4)>40  ) ) {
        LeftVol(  CA4 * kCA4 ) ;
        RightVol(  - CA4 * kCA4 );
    }
    else if ( controlmode == 1 && !BtnA && ( abs(CA1)>blindCA || abs(CA2)>blindCA  ) ) 
      {
        LeftVol(CA2 * kCA2 + CA1 * kCA1  ) ;
        RightVol( CA2 * kCA2 - CA1 * kCA1 );
      }
  
    else if ( BtnY&&!BtnA) {
        flage10=0;
      }
    else if ( flage10==1) {
       BaseMotorStop(1);
      }
    else if ( flage10==0) {
       BaseMotorStop(0);
      }
    else {
        BaseMotorStop(0);
      }
///////////////////////////////////////////////////////////////////////////////////////////
   
   
    /*
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis4
      // right = Axis3 - Axis4
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller1) {
          // stop the drive motors
          LeftDriveSmart.stop();
          RightDriveSmart.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
        DrivetrainNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      */
////////////////////////////////////////////////////////////////////////////////////
      // check the ButtonL1/ButtonL2 status to control flywheel
      if (Controller1.ButtonL1.pressing()) {
        flywheel.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        flywheel.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        flywheel.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control intake
      if (Controller1.ButtonX.pressing()) {
        intake.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        intake.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        intake.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
      }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}