#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "const.cpp"
#include "motor.cpp"
#include "okapi/impl/device/motor/motor.hpp"
#include <vector>
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/api.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

using namespace okapi::literals;

okapi::XDriveModel getDriveTrain() {
    std::vector<okapi::Motor> motors = getDriveTrainMotors();
    //imev5GreenTPR is a const written by someone who had the time to precision measure the TPR for the green gearset
    auto driveTrain = okapi::ChassisControllerBuilder()
        .withMotors(motors[0], motors[1], motors[2], motors[3])
        .withDimensions({gearboxDrive, (gearRatioDrive)}, {{mecDiam, wheelTrack}, okapi::imev5GreenTPR})
        .withSensors(okapi::ADIEncoder{enc1p1, enc1p2}, okapi::ADIEncoder{enc2p1, enc2p2})
        .withOdometry({{omniDiam, traWhlTrack}, okapi::quadEncoderTPR})
        .buildOdometry();
        //TODO: add PID to accompany odom
}