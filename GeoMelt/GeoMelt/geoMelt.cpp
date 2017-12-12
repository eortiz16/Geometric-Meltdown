#include "headers.h"
#include "geoMelt.h"
#include <thread>

GLFWwindow *window;
int width_r = HDX;
int height_r = HDY;

Game::Game()
{	
	//DevIL Init
	//ilutRenderer(ILUT_OPENGL);
	//ilInit();
	//iluInit();
	//ilutInit();
	//ilutRenderer(ILUT_OPENGL);

	//picons.set_attributes();
	//icons.set_attributes();
	//sicons.set_attributes();
	
	render = FIELD;

	//mainMenu.build();
	menus.chacterSelection.build(assets);
	levels.field.build(assets);
	levels.night.build(assets);
	levels.time.build(assets);
}

void Game::display_details()
{
	cout << "Monitor Resolution:	" << width_r << "x" << height_r << endl;
	cout << "Window Resolution:	" << width_r << "x" << height_r << endl;
}

void Game::set_resolution()
{
	if (monitor->width < HDX || monitor->width < HDY)
	{
		width_r = monitor->width;
		height_r = monitor->height;
	}
	else
	{
		width_r = HDX;
		height_r = HDY;
	}
}

int main(void)
{
	//Seed Random Number Generation
	srand((unsigned int)time(0));

	Game game;

	//Error Handling - If GLFW Libraries Not Present
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	game.monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
	game.set_resolution();
	game.display_details();

	//Create GLFW Window
	window = glfwCreateWindow(width_r, height_r, "Geometric Meltdown", NULL, NULL);

	//Error Handling - If Window is Not Created
	if (!window)
	{
		glfwTerminate(); //Destroys all Remaining Windows and Cursors
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetJoystickCallback(joystick_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	//Start new thread
	thread p(&phys,&game);
	p.detach();

	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width_r, &height_r);
		glfwGetFramebufferSize(window, &width_r, &height_r);
		glShadeModel(GL_SMOOTH);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, width_r, height_r);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glOrtho(-width_r, width_r, -height_r, height_r, -1, 1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (game.render)
		{
		case MAIN:
			//game.mainMenu.handler();
			break;
		case PAUSE:
		case LEVELSEL:
		case CHARSEL:
			game.menus.chacterSelection.handler();
			break;
		case FIELD:
			game.levels.field.handler();
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game.levels.field.player[i]->death_handler();
				game.levels.field.player[i]->read_input(&game.levels.field.player[i]->controller);
			}
			break;
		case NIGHT:
			game.levels.night.handler();
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game.levels.night.player[i]->death_handler();
				game.levels.night.player[i]->read_input(&game.levels.night.player[i]->controller);
			}
			break;
		case TIME:
			game.levels.time.handler();
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game.levels.time.player[i]->death_handler();
				game.levels.time.player[i]->read_input(&game.levels.time.player[i]->controller);
			}
			break;
		case POLLUTION:
			break;
		default:
			break;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Termination Procedure
	p.~thread();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}

void phys(Game *game)
{
	
	while (!glfwWindowShouldClose(window))
	{
		switch (game->render)
		{
		case FIELD:
			for (int i = 0; i < MAX_CLOUD; i++)
				game->levels.field.clouds[i].handler();
			game->levels.field.physics(game->levels.field);
			break;
		case NIGHT:
			game->levels.night.physics(game->levels.night);
			break;
		case TIME:
			game->levels.time.transition_handler(game->assets.backgroundPalette);
			for (int i = 0; i < MAX_CLOUD; i++)
				game->levels.time.clouds[i].handler();
			game->levels.time.physics(game->levels.time);
			break;
		default:
			break;
		}
		Sleep(10);
	}
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	cout << "\nWindow Resized: " << width << " x " << height << "\n";
	width_r = width;
	height_r = height;
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) 
				glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			break;
	}
}

void joystick_callback(int joy, int event)
{
	if (event == GLFW_CONNECTED)
		cout << "Player " << joy + 1 << ": controller connected" << endl;
	else if (event == GLFW_DISCONNECTED)
		cout << "Player " << joy + 1 << ": controller disconnected" << endl;
}