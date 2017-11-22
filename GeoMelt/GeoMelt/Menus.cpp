#include "Headers.h"

extern Game game;

MainMenu::MainMenu()
{
	title.center.x = (GLfloat)game.win.width / 2.0f;
	title.center.y = (GLfloat)game.win.height / 2.0f;
	title.width = 1000;
	title.height = 300;
}

void MainMenu::handler()
{
	render();
}

void MainMenu::render()
{
	float A = title.center.x - title.width / 2;
	float B = title.center.y - title.height / 2;
	float C = title.center.y + title.height / 2;
	float D = title.center.x + title.width / 2;

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, game.icons.title.texture);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
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