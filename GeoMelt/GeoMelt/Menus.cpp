#include "Headers.h"

extern Game game;

void MainMenu::build_main_menu()
{
	game.icons.title.box.center.x = game.win.width / 2.0f;
	game.icons.title.box.center.y = game.win.height / 2.0f;

	game.icons.pill.box.center.x = game.win.width / 2.0f;
	game.icons.pill.box.center.y = game.win.height / 4.0f;

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
	GLfloat A = box.center.x - box.width / 2;
	GLfloat B = box.center.y - box.height / 2;
	GLfloat C = box.center.y + box.height / 2;
	GLfloat D = box.center.x + box.width / 2;

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255, 255);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(A, B);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(A, C);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(D, C);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(D, B);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}