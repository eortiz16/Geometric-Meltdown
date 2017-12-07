#include "Headers.h"

void Player::controller()
{
	if (glfwJoystickPresent(controllerID))
	{
		/*
		int axesCount = 0;
		const float *axes = glfwGetJoystickAxes(controllerID, &axesCount);
		cout << "# of Axes: " << axesCount << endl;

		cout << " Left Stick X:\t" << axes[0] << endl;
		cout << " Left Stick Y:\t " << axes[1] << endl;
		cout << " Right Stick X:\t" << axes[2] << endl;
		cout << " Right Stick Y:\t " << axes[3] << endl;
		cout << " Left Trigger:\t" << axes[4] << endl;
		cout << " RightTrigger:\t" << axes[5] << endl;

		int buttonCount = 0;
		const unsigned char *buttons = glfwGetJoystickButtons(controllerID, &buttonCount);
		cout << "button count:\t" << buttonCount << endl;
		*/

		//xbox 360 - 14 buttons
		
		//buttons[i]

		//A = 0
		//B = 1
		//X = 2
		//Y = 3
		//LB = 4
		//RB = 5
		//Select = 6
		//Start = 7
		//L3 = 8
		//R3 = 9
		//DPAD
		//	UP = 10
		//	Right = 11
		//	Down = 12
		//	Left = 13
	}
}