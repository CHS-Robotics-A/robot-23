#include "main.h"
using namespace pros::literals;

//Motor ports
#define topLMot 1
#define topRMot 2
#define botLMot 3
#define botRMot 4

#define intake1 7
#define intake2 9

#define fly1 8
#define fly2 10

#define indexer 'B'
#define endgame 'A'

#define intakeRPM 600

#define strafeU okapi::ControllerAnalog::rightX
#define strafeD okapi::ControllerAnalog::leftY
#define rot okapi::ControllerAnalog::leftX

//logging output
#define logOut "/ser/sout"

//log level
#define logLevel okapi::Logger::LogLevel::debug

//Wheel gear ratio
#define gearRatioDrive 84.0/60.0

//Wheel diam
//Mecanum
#define mecDiam 4
//omni
#define omniDiam 4

//Whl track (inches)
#define wheelTrack 5
//Tracking whl traxk
#define traWhlTrack 5
//TODO: measure and change
#define midWhlDist 5

//Encoder ticks per rotation
#define encoderTPR 90

//quad wheel TPI
#define quadTPI (float)encoderTPR / (float)omniDiam

#define gainTemp 3

//The gearboxes we use for drive
#define gearboxDrive pros::E_MOTOR_GEAR_200

// Motor encoder ports
// Encoder 1
#define enc1p1 1 //A
#define enc1p2 2 //B
//Encoder 2
#define enc2p1 3 //C
#define enc2p2 4 //D
//Encoder 3
#define enc3p1 5 //E
#define enc3p2 6 //F