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
	//assign center of each char select bg
	int xSpacing = -3.0f * HDX / 4.0f;
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		int size = 100;
		char_select_box[i].vertical_box.center.x = xSpacing;
		char_select_box[i].vertical_box.height = HDY / 2.0f; // actual height
		char_select_box[i].vertical_box.color.r = 255;
		char_select_box[i].vertical_box.color.g = 255;
		char_select_box[i].vertical_box.color.b = 255;

		char_select_box[i].horizontal_box.center.x = xSpacing;
		char_select_box[i].horizontal_box.width = HDX / 4.5f; // actual width
		
		char_select_box[i].horizontal_box.color.r = 255;
		char_select_box[i].horizontal_box.color.g = 255;
		char_select_box[i].horizontal_box.color.b = 255;
		
		char_select_box[i].vertical_box.width = char_select_box[i].horizontal_box.width - size;
		char_select_box[i].horizontal_box.height = char_select_box[i].vertical_box.height - size;
		char_select_box[i].horizontal_box.boundary_assignment();
		char_select_box[i].vertical_box.boundary_assignment();

		xSpacing += HDX / 2.0f;
		
		//bottom left
		char_select_box[i].corner[0].radius = size / 2;
		char_select_box[i].corner[0].center.x = char_select_box[i].vertical_box.left_bnd;
		char_select_box[i].corner[0].center.y = char_select_box[i].horizontal_box.bottom_bnd;
		char_select_box[i].corner[0].color.r = 255;
		char_select_box[i].corner[0].color.g = 255;
		char_select_box[i].corner[0].color.b = 255;

		//top left
		char_select_box[i].corner[1].radius = size / 2;
		char_select_box[i].corner[1].center.x = char_select_box[i].vertical_box.left_bnd;
		char_select_box[i].corner[1].center.y = char_select_box[i].horizontal_box.top_bnd;
		char_select_box[i].corner[1].color.r = 255;
		char_select_box[i].corner[1].color.g = 255;
		char_select_box[i].corner[1].color.b = 255;

		//top right
		char_select_box[i].corner[2].radius = size / 2;
		char_select_box[i].corner[2].center.x = char_select_box[i].vertical_box.right_bnd;
		char_select_box[i].corner[2].center.y = char_select_box[i].horizontal_box.top_bnd;
		char_select_box[i].corner[2].color.r = 255;
		char_select_box[i].corner[2].color.g = 255;
		char_select_box[i].corner[2].color.b = 255;

		//bottom right
		char_select_box[i].corner[3].radius = size / 2;
		char_select_box[i].corner[3].center.x = char_select_box[i].vertical_box.right_bnd;
		char_select_box[i].corner[3].center.y = char_select_box[i].horizontal_box.bottom_bnd;
		char_select_box[i].corner[3].color.r = 255;
		char_select_box[i].corner[3].color.g = 255;
		char_select_box[i].corner[3].color.b = 255;
	}
}

void CharacterSelectMenu::handler()
{
	for (int i = 0; i < 4; i++)
	{
		char_select_box[i].vertical_box.render_quad();
		char_select_box[i].horizontal_box.render_quad();

		for (int j = 0; j < 4; j++)
		{
			char_select_box[i].corner[j].render_circle();
		}
	}
}