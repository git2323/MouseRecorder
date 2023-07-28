#pragma once

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "inputDevice.h"
#include "inputDeviceManager.h"
#include "inputDeviceNode.h"
#include <inputDeviceSet.h>
#include <buttonThrower.h>
#include <cIntervalManager.h>
#include <cLerpNodePathInterval.h>
#include <depthWriteAttrib.h>

//classes
class joystick {

public:
	InputDeviceManager* _mgr = {};
	InputDeviceSet inpdevset;
	PT(InputDevice) inpdev;
	void ask_for_joystick(bool);
	void set_joystick(int);
	//void calibrate();
	//void print_calib_data();
	//void load_calib_data();
	//void assign_axis();
	//void get_assignment_data();
	//void kbd_input_off(bool);
	//double get_pitch_value(bool);
	//double get_yaw_value(bool);
	//double get_ele_value(bool);
	//double get_ail_value(bool);
};

class MyCallback : public CallbackObject
{
public:
	ALLOC_DELETED_CHAIN(MyCallback);
	virtual void do_callback(CallbackData* pCbData);
};