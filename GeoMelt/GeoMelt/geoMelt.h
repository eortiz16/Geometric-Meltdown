#pragma once
int main(void);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void joystick_callback(int joy, int event);