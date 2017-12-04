#include "headers.h"
#include "geoMelt.h"

Game game;
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
	mainMenu.build_main_menu();

	window.width = HDX;
	window.height = HDY;
	render = FIELD;
	level1.build();
	level2.build();
	level3.build();
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

	//GLFWwindow *window;

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

	
	//Whlie Window is Open
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
		glClear(GL_COLOR_BUFFER_BIT);
		switch (game.render)
		{
			case MAIN:
				game.mainMenu.handler();
				break;
			case PAUSE:
			case LEVELSEL:
			case CHARSEL:
			case FIELD:
				game.level1.handler();
				break;
			case NIGHT:
				game.level2.handler();
				break;
			case TIME:
				game.level3.handler();
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

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) 
				glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_PAGE_UP:
			if (action == GLFW_PRESS)
			{
				//Return Key changes Level
				switch (game.render)
				{
				case FIELD:
					game.render = NIGHT;
					break;
				case NIGHT:
					game.render = TIME;
					break;
				case TIME:
					game.render = MAIN;
					break;
				case MAIN:
					game.render = FIELD;
					break;
				}
			}
			break;
		case GLFW_KEY_DELETE:
			if (action == GLFW_PRESS)
			{
				if (game.render == TIME)
					game.level3.transition = true;
			}
			break;
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS)
			{
				for (int i = 0; i < MAX_PLAYER; i++)
				{
					game.level1.player[i]->direction = LEFT;
					game.level1.player[i]->move();
				}
	
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS)
			{
				for (int i = 0; i < MAX_PLAYER; i++)
				{
					game.level1.player[i]->direction = RIGHT;
					game.level1.player[i]->move();
				}
			}
			break;
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS)
			{
				for (int i = 0; i < MAX_PLAYER; i++)
				{
					game.level1.player[i]->jump();
				}
			}
			break;
		default: 
			break;
	}
}