#include "headers.h"

extern Game game;

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

void CharacterSelectMenu::build()
{
	//Assigning Window Dimensions
	GLfloat w = (GLfloat)game.window.width;
	GLfloat h = (GLfloat)game.window.height;

	//Background Color Assignment
	background.body.center.x = 0;
	background.body.center.y = 0;
	background.body.width = 2 * w;
	background.body.height = 2 * h;

	for (int i = 0; i < CORNERS; i++)
	{
		background.color[i].r = 51;
		background.color[i].g = 153;
		background.color[i].b = 255;
	}
	
	//assign center of each char select bg
	float xSpacing = -3.0f * HDX / 4.0f;
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		select_box[i].vertical_box.center.x = xSpacing;
		select_box[i].vertical_box.center.y = -HDY / 2.5f;
		select_box[i].width = HDX / 3.0f;
		select_box[i].height = 3.0f * HDY / 4.0f;

		select_box_outline[i].vertical_box.center.x = xSpacing;
		select_box_outline[i].vertical_box.center.y = -HDY / 2.5f;
		select_box_outline[i].width = select_box[i].width + 20;
		select_box_outline[i].height = select_box[i].height + 20;

		select_box[i].vertical_box.color.r = 255;
		select_box[i].vertical_box.color.g = 255;
		select_box[i].vertical_box.color.b = 255;

		select_box[i].horizontal_box.color.r = 255;
		select_box[i].horizontal_box.color.g = 255;
		select_box[i].horizontal_box.color.b = 255;

		select_box_outline[i].vertical_box.color.r = 0;
		select_box_outline[i].vertical_box.color.g = 0;
		select_box_outline[i].vertical_box.color.b = 0;

		select_box_outline[i].horizontal_box.color.r = 0;
		select_box_outline[i].horizontal_box.color.g = 0;
		select_box_outline[i].horizontal_box.color.b = 0;

		for (int j = 0; j < CORNERS; j++)
		{
			select_box[i].corner[j].color.r = 255;
			select_box[i].corner[j].color.g = 255;
			select_box[i].corner[j].color.b = 255;

			select_box_outline[i].corner[j].color.r = 0;
			select_box_outline[i].corner[j].color.g = 0;
			select_box_outline[i].corner[j].color.b = 0;
		}

		select_box[i].build();
		select_box_outline[i].build();

		xSpacing += HDX / 2.0f;
	}
}

void CharacterSelectMenu::handler()
{
	background.render();

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		select_box_outline[i].render();
		select_box[i].render();
	}
}