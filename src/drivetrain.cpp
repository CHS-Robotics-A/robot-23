#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "const.cpp"
#include "motor.cpp"
#include "okapi/impl/device/motor/motor.hpp"
#include <vector>

okapi::XDriveModel getDriveTrain() {
    std::vector<okapi::Motor*> motors = getDriveTrainMotors();
    okapi::XDriveModel* driveTrain = new okapi::XDriveModel(motors[0], motors[1], motors[2], motors[3],)
}