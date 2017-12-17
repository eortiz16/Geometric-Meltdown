#pragma once
int main(void);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void joystick_callback(int joy, int event);
void window_size_callback(GLFWwindow* window, int width, int height);

void phys(Game *game);
static int width_resolution = HDX;
static int height_resolution = HDY;
static float aspect_ratio = (float)width_resolution / (float)height_resolution;

//=============================================
static float left_ortho = -0.75f * HDX;
static float right_ortho = 0.75f * HDX;
static float top_ortho = 0.75f * HDY;
static float bottom_ortho = -0.75f * HDY;

static Camera camera;
//=============================================

static bool resize = false;
extern GLFWwindow *window;