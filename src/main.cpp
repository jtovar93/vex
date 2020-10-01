/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Sep 21 2020                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <string> 

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
vex::motor LFront = vex::motor(vex::PORT1);
vex::motor RFront = vex::motor(vex::PORT10);
vex::motor LBack = vex::motor(vex::PORT11);
vex::motor RBack = vex::motor(vex::PORT20);

vex::controller Controller1 = vex::controller();

// set driveMode = 1 for all motors to one joystick
// set driveMode = 2 for two different joysticks both forward - forward, backwards - backward, inverted - turn
// set drive mode = 3 for left joystick forward and backward, and right for turning
int driveMode = 3;

//the following numbers are incluing 1 and the number listed
//screen has a maximum of 50 columns
//screen has a maximum of 20 rows

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

void printJoystick1ToScreen(){
  Brain.Screen.setCursor(3,25);
  Brain.Screen.print("Left or Right Joystick:");
  Brain.Screen.setCursor(4,25);
  Brain.Screen.print(Controller1.Axis1.position());
}

void printJoystick2ToScreen(){
  Brain.Screen.setCursor(3,25);
  Brain.Screen.print("Left Joystick:");
  Brain.Screen.setCursor(4,25);
  Brain.Screen.print(Controller1.Axis2.position());
}

void printJoystick3ToScreen(){
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Right Joystick:");
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print(Controller1.Axis3.position());
}

void clearJoystick1FromScreen(){
  Brain.Screen.setCursor(4,25);
  Brain.Screen.print("                   ");
}

void clearJoystick2FromScreen(){
  Brain.Screen.setCursor(4,25);
  Brain.Screen.print("                   ");
}

void clearJoystick3FromScreen(){
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("                   ");
}

void clearStatusMessage(){
  Brain.Screen.setCursor(10,5);
  Brain.Screen.print("                                                  ");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  bool printed = false; 
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //driveMode 1 will simply go front and back
    if(driveMode == 1){
      LFront.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      LBack.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      RFront.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
      RBack.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);

      if(!printed){
      Brain.Screen.print("Drive Mode 1");
      printed = true;
      }
      if(Controller1.Axis3.position() != 0){
        printJoystick3ToScreen();
      }
      else{
        clearJoystick3FromScreen();
      }
    }
    //driveMode 2 will be able to turn but will require both joysticks
    else if(driveMode == 2){
      LFront.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      LBack.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      RFront.spin(vex::directionType::rev, Controller1.Axis2.position(), vex::velocityUnits::pct);
      RBack.spin(vex::directionType::rev, Controller1.Axis2.position(), vex::velocityUnits::pct);
      if(!printed){
        Brain.Screen.print("Drive Mode 2");
        printed = true;
      }
      if(Controller1.Axis3.position() != 0){
        printJoystick3ToScreen();
      }
      else{
        clearJoystick3FromScreen();
      }
      if(Controller1.Axis2.position() != 0){
        printJoystick2ToScreen();
      }
      else{
        clearJoystick2FromScreen();
      }

      if((Controller1.Axis3.position() > 0 && Controller1.Axis2.position() > 0) && (Controller1.Axis3.position() == Controller1.Axis2.position()) ){
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is moving forward exclusively");
      }
      else if((Controller1.Axis3.position() < 0 && Controller1.Axis2.position() < 0) && (Controller1.Axis3.position() == Controller1.Axis2.position()) ){
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is moving in reverse exclusively");
      }
      else if((Controller1.Axis3.position() < 0 && Controller1.Axis2.position() > 0)){
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is turning left");
      }
      else if((Controller1.Axis3.position() > 0 && Controller1.Axis2.position() < 0)){
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is turning right");
      }
      // else if(Controller1.Axis3.position() > 0 ){
      //   Brain.Screen.setCursor(10,5);
      //   Brain.Screen.print("Robot is turning right widely");
      // }
      // else if(Controller1.Axis3.position() < 0 ){
      //   Brain.Screen.setCursor(10,5);
      //   Brain.Screen.print("Robot is turning right widely in reverse");
      // }
      // else if(Controller1.Axis2.position() > 0 ){
      //   Brain.Screen.setCursor(10,5);
      //   Brain.Screen.print("Robot is turning left widely");
      // }
      // else if(Controller1.Axis2.position() < 0 ){
      //   Brain.Screen.setCursor(10,5);
      //   Brain.Screen.print("Robot is turning left widely in reverse");
      // }
      else{
        clearStatusMessage();
      }

      
    }
    //driveMode3 will allow all forward and backward with joystick3 with joystick 2 modifiers to turn
    else if(driveMode == 3){
      if(!printed){
        Brain.Screen.print("Drive Mode 3");
        printed = true;
      }

      clearJoystick1FromScreen();
      clearJoystick3FromScreen();

      //all wheels forward
      if(Controller1.Axis3.position() > 0){
        LFront.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        LBack.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RFront.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RBack.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is moving forward");
      }
      //all wheels backward
      else if(Controller1.Axis3.position() < 0){
        LFront.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        LBack.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RFront.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RBack.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Robot is moving in reverse");
      }
      //right joystick to left or right flips input to turn in direction
      else if((Controller1.Axis1.position() != 0)){
        int turnSpeed = Controller1.Axis1.position();
        
        LFront.spin(vex::directionType::fwd, turnSpeed, vex::velocityUnits::pct);
        LBack.spin(vex::directionType::fwd, turnSpeed, vex::velocityUnits::pct);
        RFront.spin(vex::directionType::rev, -turnSpeed, vex::velocityUnits::pct);
        RBack.spin(vex::directionType::rev,-turnSpeed, vex::velocityUnits::pct);
        Brain.Screen.setCursor(10,5);
        Brain.Screen.print("Turning Left");
      }





      else if(Controller1.Axis3.position() == 0){
        LFront.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        LBack.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RFront.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
        RBack.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
      }

      if(Controller1.Axis3.position() != 0){
        printJoystick3ToScreen();
      }
      else{
        clearJoystick3FromScreen();
        clearStatusMessage();
      }

      if(Controller1.Axis1.position() != 0){
        printJoystick1ToScreen();
      }
      else{
        clearJoystick1FromScreen();
      }
    }


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton(); 


  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
