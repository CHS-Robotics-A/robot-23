#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api.hpp"
using namespace okapi::literals;

//Motor ports
#define topLMot 1
#define topRMot 2
#define botLMot 3
#define botRMot 4

// Motor encoder ports
// Encoder 1
#define enc1p1 'A' //1
#define enc1p2 'B' //2
//Encoder 2
#define enc2p1 'C' //3
#define enc2p2 'D' //4

//Wheel gear ratio
#define gearRatioDrive 84.0/60.0

//Wheel diam
//Mecanum
#define mecDiam 4_in
//omni
#define omniDiam 4_in

//Whl track
#define wheelTrack 5_in
//Tracking whl traxk
#define traWhlTrack 5_in
//TODO: measure and change


//The gearboxes we use for drive
#define gearboxDrive okapi::AbstractMotor::gearset::green