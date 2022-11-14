#include "okapi/impl/device/motor/motor.hpp"
#include <vector>
#include "const.cpp"


std::vector<okapi::Motor*> getDriveTrainMotors() {
    std::vector<okapi::Motor*> v(4);
    v[0] = new okapi::Motor(topLMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    v[1] = new okapi::Motor(topRMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    v[2] = new okapi::Motor(botLMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    v[3] = new okapi::Motor(botRMot, false, gearboxDrive, okapi::AbstractMotor::encoderUnits::degrees);
    
    return v;
}