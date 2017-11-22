#include "Headers.h"
#include "medMelt.h"

Game game;

Game::Game()
{	
	game_details();
	game_initb();
	render = FIELD;
}

void Game::game_details()
{
	cout << "Monitor Resolution: " << game.monitor.width << "x"
		<< game.monitor.height << endl;
	cout << "Window Resolution: " << game.win.width << "x"
		<< game.win.height << endl;
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

ImageSet::ImageSet()
{
	//Load Images
	title.img = ppm6GetImage("./resources/ppm/title.ppm");
	pill.img = ppm6GetImage("./resources/ppm/pill.ppm");
	play_u.img = ppm6GetImage("./resources/ppm/play_u.ppm");
	play_s.img = ppm6GetImage("./resources/ppm/play_s.ppm");
	options_u.img = ppm6GetImage("./resources/ppm/options_u.ppm");
	options_s.img = ppm6GetImage("./resources/ppm/options_s.ppm");
	exit_u.img = ppm6GetImage("./resources/ppm/exit_u.ppm");
	exit_s.img = ppm6GetImage("./resources/ppm/exit_s.ppm");
	resume_u.img = ppm6GetImage("./resources/ppm/resume_u.ppm");
	resume_s.img = ppm6GetImage("./resources/ppm/resume_s.ppm");
	quit_u.img = ppm6GetImage("./resources/ppm/quit_u.ppm");
	quit_s.img = ppm6GetImage("./resources/ppm/quit_s.ppm");
	level1.img = ppm6GetImage("./resources/ppm/level1.ppm");
	level2.img = ppm6GetImage("./resources/ppm/level2.ppm");

	//Texture
	glGenTextures(1, &title.texture);
	glGenTextures(1, &pill.texture);
	glGenTextures(1, &play_u.texture);
	glGenTextures(1, &play_s.texture);
	glGenTextures(1, &options_u.texture);
	glGenTextures(1, &options_s.texture);
	glGenTextures(1, &exit_u.texture);
	glGenTextures(1, &exit_s.texture);
	glGenTextures(1, &resume_u.texture);
	glGenTextures(1, &resume_s.texture);
	glGenTextures(1, &quit_u.texture);
	glGenTextures(1, &quit_s.texture);
	glGenTextures(1, &level1.texture);
	glGenTextures(1, &level2.texture);

	title.texture_map();
	play_u.texture_map();
	play_s.texture_map();
	options_u.texture_map();
	options_s.texture_map();
	exit_u.texture_map();
	exit_s.texture_map();
	resume_u.texture_map();
	resume_s.texture_map();
	quit_u.texture_map();
	quit_s.texture_map();
	level1.texture_map();
	level2.texture_map();
}

void Image::texture_map()
{
	//Aspect Ratio
	ratio = (GLfloat)img->width / (GLfloat)img->height;
	
	//Texture Map for Each Image
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char *data = buildAlphaData(img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);
	free(data);
}