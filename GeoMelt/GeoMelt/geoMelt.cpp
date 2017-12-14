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
	
	render = FIELD;
	//mainMenu.build();
	menus.chacterSelection.build(assets);
	levels.field.build(assets);
	levels.night.build(assets);
	levels.time.build(assets);
}

void Game::display_details()
{
	cout << "Monitor Resolution:	" << monitor->width << "x" << monitor->height << endl;
	cout << "Window Resolution:	" << width_resolution << "x" << height_resolution << endl;
}

void Game::set_resolution()
{
	if (monitor->width < HDX || monitor->width < HDY)
	{
		width_resolution = monitor->width;
		height_resolution = monitor->height;
	}
	else
	{
		width_resolution = HDX;
		height_resolution = HDY;
	}
	aspect_ratio = width_resolution / height_resolution;
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
	window = glfwCreateWindow(width_resolution, height_resolution, "Geometric Meltdown", NULL, NULL);

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

	bool flag = false;
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width_resolution, &height_resolution);
		glfwGetFramebufferSize(window, &width_resolution, &height_resolution);
		glShadeModel(GL_SMOOTH);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, width_resolution, height_resolution);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		
		glOrtho(-width_ortho, width_ortho, -height_ortho, height_ortho, -1, 1);

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
			break;
		case NIGHT:
			game.levels.night.handler();
			break;
		case TIME:
			game.levels.time.handler();
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
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game->levels.field.player[i]->death_handler();
				game->levels.field.player[i]->read_input(&game->levels.field.player[i]->controller);
			}
			game->levels.field.camera(game->levels.field);
			break;
		case NIGHT:
			game->levels.night.physics(game->levels.night);
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game->levels.night.player[i]->death_handler();
				game->levels.night.player[i]->read_input(&game->levels.night.player[i]->controller);
			}
			game->levels.night.camera(game->levels.night);
			break;
		case TIME:
			game->levels.time.transition_handler(game->assets.backgroundPalette);
			for (int i = 0; i < MAX_CLOUD; i++)
				game->levels.time.clouds[i].handler();
			game->levels.time.physics(game->levels.time);
			for (int i = 0; i < MAX_PLAYER; i++)
			{
				game->levels.time.player[i]->death_handler();
				game->levels.time.player[i]->read_input(&game->levels.time.player[i]->controller);
			}
			game->levels.time.camera(game->levels.time);
			break;
		default:
			break;
		}
		/*
		if (resize == true)
		{
			game->levels.field.build(game->assets);
			game->levels.night.build(game->assets);
			game->levels.time.build(game->assets);
			resize = false;
		}
		*/
		Sleep(10);
	}
}

bool fla = false;
void Level::camera(Level lvl)
{
	//find furthest player away from center (x and y)
	float percent;
	float x = 0;
	float y = 0;

	// obtain furthest distance away from center
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		//if (lvl.player[i]->stats.lifeState == ALIVE)
		{
			if (abs(player[i]->body.center.x) + player[i]->body.radius > x)
				x = abs(player[i]->body.center.x);// +250;
			if (abs(player[i]->body.center.y) + player[i]->body.radius > y)
				y = abs(player[i]->body.center.y);// +141;
		}
	}

	if (fla)
	{
		//All characters in bounds
		// Where is camera at though?
		if (width_ortho > 0.75f * HDX)
		{
			width_ortho *= 0.9952f;
			height_ortho *= 0.9952f;

			if (width_ortho <= 0.75f * HDX)
			{
				width_ortho = 0.75f * HDX;
				height_ortho = 0.75f * HDY;
				fla = false;
			}
		}
		else
		{
			fla = false;
		}
	}
	else
	{
		// Set max camera distance
		if (x > 1.5f * HDX || y > 1.5f * HDY)
		{
			width_ortho = 1.5f * HDX;
			height_ortho = 1.5f * HDY;
		}
		//X is further away
		else if (x > y && x > (0.75f* width_resolution))
		{
			percent = (abs(x) - (0.75f * width_resolution)) / width_resolution;
			height_ortho = (1.0f + percent) *  0.75f * HDY;
			width_ortho = (1.0f + percent) * 0.75f * HDX;
		}
		//Y if further away
		else if (y > x && y > (0.75f * height_resolution))
		{
			percent = (abs(y) - (0.75f * height_resolution)) / height_resolution;
			height_ortho = (1.0f + percent) *  0.75f * HDY ;
			width_ortho = (1.0f + percent) * 0.75f * HDX;
		}
		//else in bounds
		else
		{
			//Slowly reset camera
			fla = true;
		}
	}
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	cout << "\nWindow Resized: " << width << " x " << height << "\n";
	width_resolution = width;
	height_resolution = height;
	aspect_ratio = width_resolution / height_resolution;
	resize = true;
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

/*
bool fla = false;
int source = 0;
int source_x = 0;
int source_y = 0;
void Level::camera(Level lvl)
{
	//find furthest player away from center (x and y)
	float percent;
	float x = 0;
	float y = 0;

	// obtain furthest distance away from center
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (lvl.player[i]->stats.lifeState == ALIVE)
		{
			if (abs(player[i]->body.center.x) > x)
			{
				x = abs(player[i]->body.center.x + player[i]->body.radius) + 200;
				source_x = i;
			}
			if (abs(player[i]->body.center.y) > y)
			{
				y = abs(player[i]->body.center.y + player[i]->body.radius) + 200;
				source_y = i;
			}
		}
	}

	if (fla)
	{
		if (width_ortho > (3 * HDX / 4) + (0.1f * HDX)
			|| height_ortho > (3 * HDY / 4) + (0.1f * HDY))
		{
			cout << "@";
			width_ortho *= 0.9999;
			height_ortho *= 0.9999;
		}
		if (width_ortho <= x || height_ortho <= y)
		{
			cout << "exit";
			fla = false;
		}
	}
	else
	{
		if (x > 2 * HDX || y > 2 * HDY)
		{
			width_ortho = 2 * HDX;
			height_ortho = 2 * HDY;
		}
		else if (x > (y * aspect_ratio) && x > (3 * width_resolution / 4))
		{
			percent = (abs(x) - (3 * width_resolution / 4)) / width_resolution;
			width_ortho = (1.0f + percent) * 3.0f * HDX / 4.0f;
			height_ortho = (1.0f + percent) * 3.0f * HDY / 4.0f;
		}
		else if ((y * aspect_ratio) > x && y > 3 * height_resolution / 4)
		{
			percent = (abs(y) - (3 * height_resolution / 4)) / height_resolution;
			height_ortho = (1.0f + percent) *  3.0f * HDY / 4.0f;
			width_ortho = (1.0f + percent) * 3.0f * HDX / 4.0f;
		}
		else if (x < (3 * width_resolution / 4) && y < (3 * height_resolution / 4))
		{
			cout << "1";
			//Players within boundary? Slowly reset camera
			if (player[source]->stats.lifeState == DEAD)
			{
				cout << "2";
				if (x > y)
					source = source_x;
				else if (y > x)
					source = source_y;
				fla = true;
			}
			else
				fla = false;
		}
	}
}
*/
