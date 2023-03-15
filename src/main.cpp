#include "main.h"
#include "headers/gui/home.hpp"
#include <algorithm>
#include <cstdio>
#include "okapi/api/chassis/model/skidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderXDriveModel.hpp"
#include "okapi/api/chassis/controller/chassisController.hpp"
#include "okapi/impl/control/async/asyncMotionProfileControllerBuilder.hpp"
#include "HolonomicLib/API.hpp"
#include "headers/const.hpp"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/rtos.hpp"
#include <math.h>

using namespace okapi::literals;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	createDisplay();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	pros::ADIDigitalOut piston (endgame);
	piston.set_value(true);

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	
	/*
	auto profile = okapi::AsyncMotionProfileControllerBuilder().withLimits(
		{
			1.0,
			2.0,
			10.0
		}
	).withOutput(chassis)
	.buildMotionProfileController();

	profile->generatePath({
		{0_ft, 0_ft, 0_deg},
		{0_ft, 3_ft, 0_deg}
	}, "Test");

	profile->setTarget("Test");

	profile->waitUntilSettled();
	*/

	//motor groups

	okapi::Controller master(okapi::ControllerId::master);
	okapi::Controller slave(okapi::ControllerId::partner);

	auto chassis = okapi::ChassisControllerBuilder().withMotors({topLMot, botLMot}, {topRMot, botRMot}).withDimensions({okapi::AbstractMotor::gearset::green}, {{4_in, 12.5_in}, okapi::imev5GreenTPR}).build();

	auto xModel = std::dynamic_pointer_cast<okapi::SkidSteerModel>(chassis->getModel());

	xModel->forward(200);

	int flyState = 0;

	auto upArrow = okapi::ControllerButton(okapi::ControllerDigital::down);
	auto downArrow = okapi::ControllerButton(okapi::ControllerDigital::up);
	auto r2 = okapi::ControllerButton(okapi::ControllerDigital::Y);
	auto r1 = okapi::ControllerButton(okapi::ControllerDigital::L1);

	auto l1 = okapi::ControllerButton(okapi::ControllerDigital::R2);
	auto l2 = okapi::ControllerButton(okapi::ControllerDigital::R1);

	auto xButton = okapi::ControllerButton(okapi::ControllerDigital::B);
	auto bButton = okapi::ControllerButton(okapi::ControllerDigital::X);

	auto intake = okapi::MotorGroup({-intake1, intake2});
	auto fly = okapi::MotorGroup({fly1, -fly2});

	float flyspeed = 600;

	pros::ADIDigitalOut piston (indexer);
	pros::ADIDigitalOut spiderman (endgame);

	bool verify = false;

	fly.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

	intake.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	
  	while (true) {
		//arcade drive
    	xModel->arcade(
      		master.getAnalog(strafeU),
      		master.getAnalog(strafeD),
      		master.getAnalog(rot)
		);
		

		if (upArrow.isPressed() == true) {
			intake.moveVoltage(12000);
			upArrow.changedToReleased();
		} else if (downArrow.isPressed() == true) {
			//intake.moveVelocity(-500);
			intake.moveVoltage(-12000);
			downArrow.changedToReleased();
		} else if (r2.isPressed() == true) {
			intake.moveVelocity(0);
			r2.changedToReleased();
		}

		if (l2.isPressed() == true) {
			fly.moveVelocity(flyspeed);
			flyState = 1;
			l2.changedToReleased();
		} else if (l1.isPressed() == true) {
			fly.moveVelocity(0);
			flyState=0;
			l1.changedToReleased();
		}

		if (xButton.isPressed() == true) {
			piston.set_value(true);
			xButton.changedToReleased();
		} else if (bButton.isPressed() == true) {
			piston.set_value(false);
			bButton.changedToReleased();
		}

		if (slave.getDigital(okapi::ControllerDigital::L1)) {
			if (verify == true) spiderman.set_value(true);
			else verify = true;
			r1.changedToReleased();
		} 


		if (slave.getDigital(okapi::ControllerDigital::A)) {
			flyspeed = 600;
		}
		if (slave.getDigital(okapi::ControllerDigital::B)) {
			flyspeed = 300;
		}
		if (slave.getDigital(okapi::ControllerDigital::X)) {
			flyspeed = 135;
		}
		if (slave.getDigital(okapi::ControllerDigital::Y)) {
			flyspeed = 100;
		}
		if (slave.getDigital(okapi::ControllerDigital::up)) {
			flyspeed = 120;
		}
		if (slave.getDigital(okapi::ControllerDigital::down)) {
			flyspeed = 110;
		}
		if (slave.getDigital(okapi::ControllerDigital::left)) {
			flyspeed = 115;
		}
		if (slave.getDigital(okapi::ControllerDigital::right)) {
			flyspeed = 125;
		}

		flyspeed = std::min(std::max(50.0f, flyspeed+(slave.getAnalog(strafeD)/100)), 600.0f);
		if (flyState) fly.moveVelocity(flyspeed);
		else fly.moveVelocity(0);




		slave.setText(1, 1, std::to_string(flyspeed));
		slave.setText(2, 1, flyState? "Off": "On");

		//little bit of delay
    	pros::delay(1);




  	}


}
