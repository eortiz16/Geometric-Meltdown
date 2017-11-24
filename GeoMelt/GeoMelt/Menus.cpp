#include "headers.h"

extern Game game;

void MainMenu::build_main_menu()
{
	//DevIL below
	game.icons.title.box.center.x = game.window.width;
	game.icons.title.box.center.y = game.window.height;

	game.icons.pill.box.center.x = -game.window.width/1.5f;
	game.icons.pill.box.center.y = -game.window.height/1.5f;

	game.icons.title.box.width = (GLfloat)game.icons.title.w;
	game.icons.title.box.height = (GLfloat)game.icons.title.h;

	game.icons.pill.box.width = (GLfloat)game.icons.pill.w;
	game.icons.pill.box.height = (GLfloat)game.icons.pill.h;

	//PPM BELOW
	game.picons.title.box.center.x = game.window.width / 2.0f;
	game.picons.title.box.center.y = game.window.height / 2.0f;

	game.picons.pill.box.center.x = game.window.width / 4.0f;
	game.picons.pill.box.center.y = game.window.height / 4.0f;

	game.picons.title.box.width = (GLfloat)game.picons.title.w;
	game.picons.title.box.height = (GLfloat)game.picons.title.h;

	game.picons.pill.box.width = (GLfloat)game.picons.pill.w;
	game.picons.pill.box.height = (GLfloat)game.picons.pill.h;

	//SOIL BELOW
	game.sicons.title.box.center.x = game.window.width / 3.0f;
	game.sicons.title.box.center.y = game.window.height / 3.0f;

	game.sicons.pill.box.center.x = game.window.width / 5.0f;
	game.sicons.pill.box.center.y = game.window.height / 5.0f;

	game.sicons.title.box.width = (GLfloat)game.sicons.title.w;
	game.sicons.title.box.height = (GLfloat)game.sicons.title.h;

	game.sicons.pill.box.width = (GLfloat)game.sicons.pill.w;
	game.sicons.pill.box.height = (GLfloat)game.sicons.pill.h;
}

void MainMenu::handler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game.picons.title.render();
	game.picons.pill.render();
	game.icons.title.render();
	game.icons.pill.render();
	game.sicons.title.render();
	game.sicons.pill.render();
	game.level1.player1.render();
}

