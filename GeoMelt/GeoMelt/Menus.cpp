#include "headers.h"

//extern int width_r, height_r;

/*
void MainMenu::build()
{
	//DevIL below
	game.icons.title.box.center.x = (GLfloat)game.window.width;
	game.icons.title.box.center.y = (GLfloat)game.window.height;

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
	game.level1.player[0]->render();
}
*/

void CharacterSelectMenu::build(Assets assets)
{
	//Background Attribute Assignment
	background.body.center.x = 0;
	background.body.center.y = 0;
	background.body.width = 2.0f * width_resolution;
	background.body.height = 2.0f * height_resolution;

	for (int i = 0; i < CORNERS; i++)
	{
		background.color[i].r = assets.palette.lightGrey.r;
		background.color[i].g = assets.palette.lightGrey.g;
		background.color[i].b = assets.palette.lightGrey.b;
	}
	
	//assign center of each char select box
	float wSpace = -3.0f * width_resolution / 4.0f;
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		selectBox[i].stroke = 30.0f;

		selectBox[i].box.center.x = wSpace;
		selectBox[i].box.center.y = - height_resolution / 2.5f;
		selectBox[i].box.width = width_resolution / 3.0f;
		selectBox[i].box.height = 3.0f * height_resolution / 4.0f;
		selectBox[i].box.build();
		selectBox[i].box.set_color(assets.palette.white);

		selectBox[i].outline.center.x = selectBox[i].box.center.x;
		selectBox[i].outline.center.y = selectBox[i].box.center.y;
		selectBox[i].outline.width = selectBox[i].box.width + selectBox[i].stroke;
		selectBox[i].outline.height = selectBox[i].box.height + selectBox[i].stroke;
		selectBox[i].outline.build();
		selectBox[i].outline.set_color(assets.palette.black);

		wSpace += width_resolution / 2.0f;
	}
}

void CharacterSelectMenu::handler()
{
	background.render();
	
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		selectBox[i].outline.render();
		selectBox[i].box.render();
	}
}