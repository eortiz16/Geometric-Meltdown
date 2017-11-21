#include "Headers.h"
#include "medMelt.h"

const GLFWvidmode * scrn;
Game game;

Game::Game()
{	
	cout << "Resolution: " << win.width << "x" << win.height << endl;
	game_initb();
	render = FIELD;
}

void Game::game_inita()
{
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
		game.~Game();
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
		scrn = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwGetWindowSize(game.window, &game.win.width, &game.win.height);
		glfwGetFramebufferSize(game.window, &game.win.width, &game.win.height);
		glViewport(0, 0, game.win.width, game.win.height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glClearColor(0,0,0,0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glOrtho(-game.win.width / 2, 1.5 * game.win.width,
			-game.win.height / 2, 1.5 * game.win.height, -1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render Current State
		switch (game.render)
		{
			case MAIN:
			case PAUSE:
			case LEVELSEL:
			case CHARSEL:
			case FIELD:
				game.level1.field_handler();
				break;
			case NIGHT:
				game.level2.night_handler();
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
				case NIGHT:
					game.render = FIELD;
					break;
				case FIELD:
					game.render = NIGHT;
					break;
				}
			}
			break;
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS)
			{
				game.level1.player.direction = LEFT;
				game.level1.player2.direction = RIGHT;
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS)
			{
				game.level1.player.direction = RIGHT;
				game.level1.player2.direction = LEFT;
			}
			break;
		default: 
			break;
	}
}

void Game::load_images()
{
	//Extract Files

	system("dir");
	//====LOAD IMAGES========
	game.icons.gameTitle.icon = ppm6GetImage("./resources/ppm/title.ppm");
	game.icons.pillIcon.icon = ppm6GetImage("./resource/ppm/pill.ppm");

	//Texture
	glGenTextures(1, &game.icons.gameTitle.texture);
	glGenTextures(1, &game.icons.pillIcon.texture);

	//Title==================================================================
	int w = game.icons.gameTitle.icon->width;
	int h = game.icons.gameTitle.icon->height;

	glBindTexture(GL_TEXTURE_2D, game.icons.gameTitle.texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
		game.icons.gameTitle.icon->data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, game.icons.gameTitle.sil);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char *silData = buildAlphaData(game.icons.gameTitle.icon);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, silData);
	free(silData);

	//Pill Icon==============================================================
	glBindTexture(GL_TEXTURE_2D, game.icons.pillIcon.texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	w = game.icons.pillIcon.icon->width;
	h = game.icons.pillIcon.icon->height;

	unsigned char *pilData = buildAlphaData(game.icons.pillIcon.icon);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, pilData);
	free(pilData);
}