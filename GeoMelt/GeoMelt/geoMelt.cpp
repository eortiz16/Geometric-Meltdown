#include "Headers.h"
#include "medMelt.h"
#include <string>

Game game;

Game::Game()
{	
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	icons.set_attributesb();
	mainMenu.build_main_menu();
	game_initb();
	render = MAIN;
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
	glfwGetWindowSize(game.window, &game.win.width, &game.win.height);
	glfwGetFramebufferSize(game.window, &game.win.width, &game.win.height);
	glViewport(0, 0, game.win.width, game.win.height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glOrtho(-game.win.width / 2, 1.5 * game.win.width,
		-game.win.height / 2, 1.5 * game.win.height, -1, 1);

	while (!glfwWindowShouldClose(game.window))
	{
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

void ImageSet::set_attributesb()
{
	title.filename = "./resources/jpg/title.jpg";
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

	title.loadImg();
	pill.loadImg();
	play.loadImg();
	play.img_s.loadImg();
	options.loadImg();
	options.img_s.loadImg();
	exit.loadImg();
	exit.img_s.loadImg();
	resume.loadImg();
	resume.img_s.loadImg();
	quit.loadImg();
	quit.img_s.loadImg();
	level1.loadImg();
	level2.loadImg();
}

void Image::loadImg()
{
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	success = ilLoadImage(filename);

	if (success)
	{
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		}

		glGenTextures(1, &textureID);
		
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());
		w = (GLfloat)ilGetInteger(IL_IMAGE_WIDTH);
		h = (GLfloat)ilGetInteger(IL_IMAGE_HEIGHT);
	}
	else
	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	std::cout << "Texture creation successful." << std::endl;
}