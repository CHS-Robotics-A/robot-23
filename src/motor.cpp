#include "okapi/impl/device/motor/motor.hpp"
#include <vector>
#include "const.cpp"


std::vector<okapi::Motor> getDriveTrainMotors() {
    std::vector<okapi::Motor> v(4);
    okapi::Motor* m1 = new okapi::Motor(topLMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    okapi::Motor* m2 = new okapi::Motor(topRMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    okapi::Motor* m3 = new okapi::Motor(botLMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    okapi::Motor* m4 = new okapi::Motor(botRMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    
    v[0] = *m1;
    v[1] = *m2;
    v[2] = *m3;
    v[3] = *m4;

    return v;
}