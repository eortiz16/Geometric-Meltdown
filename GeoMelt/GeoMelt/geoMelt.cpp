#include "headers.h"
#include "geoMelt.h"
#include <thread>

GLFWwindow *window;

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
	window.width = HDX;
	window.height = HDY;
	render = TIME;

	//mainMenu.build();
	menus.chacterSelection.build(window, assets);
	levels.field.build(window, assets);
	levels.night.build(window, assets);
	levels.time.build(window, assets);
}

void Game::display_details()
{
	cout << "Monitor Resolution:	" << monitor->width << "x" << monitor->height << endl;
	cout << "Window Resolution:	" << window.width << "x" << window.height << endl;
}

void Game::set_resolution()
{
	if (monitor->width < HDX || monitor->width < HDY)
	{
		window.width = monitor->width;
		window.height = monitor->width;
		window.ratio = (GLfloat)window.width / (GLfloat)window.height;
	}
	else
	{
		window.width = HDX;
		window.height = HDY;
		window.ratio = (GLfloat)HDY / (GLfloat)HDX;
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
	window = glfwCreateWindow(game.window.width, game.window.height, "Geometric Meltdown", NULL, NULL);

	//Error Handling - If Window is Not Created
	if (!window)
	{
		glfwTerminate(); //Destroys all Remaining Windows and Cursors
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetJoystickCallback(joystick_callback);

	//Start new thread
	thread p(&phys,&game);
	p.detach();

	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &game.window.width, &game.window.height);
		glfwGetFramebufferSize(window, &game.window.width, &game.window.height);
		glShadeModel(GL_SMOOTH);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, game.window.width, game.window.height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glOrtho(-game.window.width, game.window.width,
			-game.window.height, game.window.height, -1, 1);

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
			game.levels.field.handler(game.levels.field, game.window);
			break;
		case NIGHT:
			game.levels.night.handler(game.levels.night, game.window);
			break;
		case TIME:
			game.levels.time.handler(game.levels.time, game.window, game.assets);
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
				game->levels.field.clouds[i].handler(game->window);

			game->levels.field.physics(game->levels.field, game->window);
			break;
		case NIGHT:
			game->levels.night.physics(game->levels.night, game->window);
			break;
		case TIME:
			game->levels.time.transition_handler(game->assets.backgroundPalette);

			for (int i = 0; i < MAX_CLOUD; i++)
				game->levels.time.clouds[i].handler(game->window);

			game->levels.time.physics(game->levels.time, game->window);
			break;
		default:
			break;
		}
		Sleep(10);
	}
}

static void error_callback(int error, const char* description)
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
	{
		cout << "Player " << joy + 1 << ": controller connected" << endl;
	}
	else if (event == GLFW_DISCONNECTED)
	{
		cout << "Player " << joy + 1 << ": controller disconnected" << endl;
	}
}