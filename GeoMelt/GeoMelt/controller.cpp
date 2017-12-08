#include "Headers.h"

void Player::read_input(Controller *c)
{
	if (glfwJoystickPresent(c->id))
	{
		c->buttons = glfwGetJoystickButtons(c->id, &c->buttonCount);

		if (c->buttons[0] == GLFW_PRESS && c->singlePress[0] == false)
		{
			jump();
			c->singlePress[0] = true;
		}
		else if (c->buttons[0] == GLFW_RELEASE && c->singlePress[0] == true)
		{
			c->singlePress[0] = false;
		}
	}
}

void Controller::build()
{
	for (int i = 0; i < 14; i++)
		cout << singlePress[i] << endl;
}

//xbox 360 - 14 buttons

//buttons[i]

//	A = 0
//	B = 1
//	X = 2
//	Y = 3
//	LB = 4
//	RB = 5
//	Select = 6
//	Start = 7
//	L3 = 8
//	R3 = 9
//DPAD
//	UP = 10
//	Right = 11
//	Down = 12
//	Left = 13

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