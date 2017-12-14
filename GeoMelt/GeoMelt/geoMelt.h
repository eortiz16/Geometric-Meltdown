#pragma once
int main(void);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void joystick_callback(int joy, int event);
void window_size_callback(GLFWwindow* window, int width, int height);

void phys(Game *game);
static int width_resolution = HDX;
static int height_resolution = HDY;
static int aspect_ratio = width_resolution / height_resolution;
static float width_ortho = 3.0f * HDX / 4.0f;
static float height_ortho = 3.0f * HDY / 4.0f;
static bool resize = false;
extern GLFWwindow *window;