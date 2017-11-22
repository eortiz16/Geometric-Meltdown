#include "Headers.h"

extern Game game;

void MainMenu::build_main_menu()
{
	game.icons.title.box.center.x = game.win.width / 2.0;
	game.icons.title.box.center.y = game.win.height / 2.0;

	game.icons.pill.box.center.x = game.win.width / 2.0;
	game.icons.pill.box.center.y = game.win.height / 4.0;

	game.icons.title.box.width = game.icons.title.w;
	game.icons.title.box.height = game.icons.title.h;

	game.icons.pill.box.width = game.icons.pill.w;
	game.icons.pill.box.height = game.icons.pill.h;
}

void MainMenu::handler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game.icons.title.render();
	game.icons.pill.render();
	game.level1.player1.render();
}

void Image::render()
{
	cout << filename << " dimensions: " << w << "x" << h << endl;
	float A = box.center.x - box.width / 2;
	float B = box.center.y - box.height / 2;
	float C = box.center.y + box.height / 2;
	float D = box.center.x + box.width / 2;


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND); 

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4ub(255, 255, 255, 40);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(A, B);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(A, C);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(D, C);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(D, B);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}