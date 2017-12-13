#pragma once
int main(void);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void joystick_callback(int joy, int event);
void window_size_callback(GLFWwindow* window, int width, int height);

void phys(Game *game);
static int width_r = HDX;
static int height_r = HDY;
static bool resize = false;
extern GLFWwindow *window;