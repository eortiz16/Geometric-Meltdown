#include "headers.h"
#include "geoMelt.h"

Game game;

Game::Game()
{	
	/*
	//DevIL Init
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	//picons.set_attributes();
	//icons.set_attributes();
	//sicons.set_attributes();
	mainMenu.build_main_menu();
	*/
	game_initb();
	render = FIELD;
	game_details();
}

void Game::game_details()
{
	cout << "Monitor Resolution: " << game.monitor.width << "x"
		<< game.monitor.height << endl;
	cout << "Window Resolution: " << game.win.width << "x"
		<< game.win.height << endl;
}

Initialize::Initialize()
{
	game.game_inita();
}

void Game::game_inita()
{
	const GLFWvidmode * scrn;
	//Error Handling - If GLFW Libraries Not Present
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		game.~Game();
		exit(EXIT_FAILURE);
	}

	//Create GLFW Window
	scrn = glfwGetVideoMode(glfwGetPrimaryMonitor());
	monitor.width = scrn->width;
	monitor.height = scrn->height;
	if (scrn->width < HDX || scrn->width < HDY)
	{
		win.width = scrn->width;
		win.height = scrn->width;
		win.ratio = (GLfloat)win.width / (GLfloat)win.height;
	}
	else
	{
		win.width = HDX;
		win.height = HDY;
		win.ratio = (GLfloat)win.width / (GLfloat)win.height;
	}
}

void Game::game_initb()
{
	window = glfwCreateWindow(win.width, win.height, "Geometric Meltdown", NULL, NULL);

	//Error Handling - If Window is Not Created
	if (!window)
	{
		glfwTerminate(); //Destroys all Remaining Windows and Cursors
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(game.window);
	glfwSetKeyCallback(game.window, key_callback);
}

int main(void)
{
	//Seed Random Number Generation
	srand((unsigned int)time(0));
	
	//Whlie Window is Open
	while (!glfwWindowShouldClose(game.window))
	{
		glfwGetWindowSize(game.window, &game.win.width, &game.win.height);
		glfwGetFramebufferSize(game.window, &game.win.width, &game.win.height);
		glViewport(0, 0, game.win.width, game.win.height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glOrtho(-game.win.width / 2, 1.5 * game.win.width,
			-game.win.height / 2, 1.5 * game.win.height, -1, 1);
		glClearColor(0, 0, 0, 0);
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

		glfwSwapBuffers(game.window);
		glfwPollEvents();
	}
	//Termination Procedure
	glfwDestroyWindow(game.window);
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
		case GLFW_KEY_ENTER:
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
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS)
			{
				if (game.render == TIME)
					game.level3.change = true;
			}
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS)
			{
				game.level1.player1.direction = LEFT;
				game.level1.player2.direction = RIGHT;
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS)
			{
				game.level1.player1.direction = RIGHT;
				game.level1.player2.direction = LEFT;
			}
			break;
		default: 
			break;
	}
}

void debug()
{
	char choice = 'n';
	while (choice == 'n')
	{
		cout << "Continue? " << endl;
		cin >> choice;
	}
}