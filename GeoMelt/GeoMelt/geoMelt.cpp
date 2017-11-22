#include "Headers.h"
#include "medMelt.h"
#include <string>

Game game;

Game::Game()
{	
	icons.set_attributes();
	mainMenu.build_main_menu();
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

void ImageSet::set_attributes()
{
	cout << "***Loading Assets***" << endl;

	title.filename = "./resources/ppm/title.ppm";
	pill.filename = "./resources/ppm/pill.ppm";
	play.filename = "./resources/ppm/play_u.ppm";
	play.img_s.filename = "./resources/ppm/play_s.ppm";
	options.filename = "./resources/ppm/options_u.ppm";
	options.img_s.filename = "./resources/ppm/options_s.ppm";
	exit.filename = "./resources/ppm/exit_u.ppm";
	exit.img_s.filename = "./resources/ppm/exit_s.ppm";
	resume.filename = "./resources/ppm/resume_u.ppm";
	resume.img_s.filename = "./resources/ppm/resume_s.ppm";
	quit.filename = "./resources/ppm/quit_u.ppm";
	quit.img_s.filename = "./resources/ppm/quit_s.ppm";
	level1.filename = "./resources/ppm/level1.ppm";
	level2.filename = "./resources/ppm/level2.ppm";

	title.texture_map();
	pill.texture_map();
	play.texture_map();
	play.img_s.texture_map();
	options.texture_map();
	options.img_s.texture_map();
	exit.texture_map();
	exit.img_s.texture_map();
	resume.texture_map();
	resume.img_s.texture_map();
	quit.texture_map();
	quit.img_s.texture_map();
	level1.texture_map();
	level2.texture_map();
}

void Image::texture_map()
{
	//Load Images
	img = ppm6GetImage(filename);

	//Aspect Ratio
	w = img->width;
	h = img->height;

	ratio = (GLfloat)img->width / (GLfloat)img->height;

	//Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, img->width, img->height, 0, GL_RGB, 
		GL_UNSIGNED_BYTE, img->data);
	
	//Silhouette
	glBindTexture(GL_TEXTURE_2D, sil);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	unsigned char *sData = buildAlphaData(img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, sData);
	free(sData);
}