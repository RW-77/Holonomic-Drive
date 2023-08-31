#include "vex.h"
#include <iostream>
using namespace vex;

brain Brain;
inertial BrainInertial = inertial();

motor FL_Motor = motor(PORT4, false);
motor BR_Motor = motor(PORT8, false);
motor FR_Motor = motor(PORT6, false);
motor BL_Motor = motor(PORT2, false);

motor BL_Servo = motor(PORT, false);
motor BR_Servo = motor(PORT, false);
motor FL_Servo = motor(PORT, false);
motor FR_Servo = motor(PORT, false);

controller Controller = controller();

float deadband = 5.0;
float pi = M_PI;
int v1_x, v1_y = 1; // vector representing front left and back right wheels
int v2_x, v2_y = -1; // vector representing front right and back left wheels
double FL_v = 0;
double FR_v = 0;
double BL_v = 0;
double BR_v = 0;

void movementThread() {
  while (true) {
    // x and y of movement joystick
    double j_x = Controller.Axis1.position();
    double j_y = Controller.Axis2.position();
    double theta = asin(j_y/j_x)-(pi/2);
    // x pos of rotation axis
    double r_x = Controller.Axis3.position();

  // calculate velocity distributed to opposite sets of wheels
    double v1 = norm(j_x, j_y) * sin(theta+pi/4);
    double v2 = norm(j_x, j_y) * sin(theta-pi/4);
    // use sign of cross product to determine direction of wheels
    double cp1 = j_x*v1_x + j_y*v1_y;
    double cp2 = j_x*v2_x + j_y*v2_y;

    int dir1 = (cp1 > 0) ? 1 : -1;
    int dir2 = (cp2 > 0) ? 1 : -1;
    int s1 = (cp1 > 0) ? 1 : -1;
    int s2 = (cp2 > 0) ? 1 : -1;
    v1 *= s1;
    v2 *= s2;

    double r = (abs(r_x) > deadband) ? r_x : 0;
    FL_v = v1 + r;
    FR_v = v2 - r;
    BR_v = v1 - r;
    BL_v = v2 + r;

    updateMotorSpeed();
    spinAll();
    wait(20, msec);
  }
}

void debugThread() {
  Brain.Screen.setFont(mono12);
  double t = 0;
  while(true) {
    std::cout << "t: %d" << t;
    std::cout << "m_x: " << Controller.Axis1.position();
    std::cout << "m_y: " << Controller.Axis2.position();
    std::cout << "r_x: " << Controller.Axis3.position();
    std::cout << "FL_v: " << FL_v;
    std::cout << "FR_v: " << FR_v;
    std::cout << "BL_v: " << BL_v;
    std::cout << "BR_v: " << BR_v;

    wait(0.2, seconds);
  }
}

int main() {
  // instantiating thread starts it immediately
  thread mainThread = thread(movementThread);
  thread debugThread = thread(debugThread);
}

// update motor speed for rotation
void updateMotorSpeed() {
  FL_Motor.setVelocity(FL_v, percent);
  BL_Motor.setVelocity(BL_v, percent);
  FR_Motor.setVelocity(FR_v, percent);
  BR_Motor.setVelocity(BR_v, percent);
}

void spinAll() {
  FL_Motor.spin(forward);
  BR_Motor.spin(forward);
  FR_Motor.spin(forward);
  BL_Motor.spin(forward);
}

double norm(double one, double two) {
  return sqrt(pow(one, 2) + pow(two, 2));
}
