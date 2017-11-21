#include "Headers.h"
#include "render.h"

void Shape::render_circle()
{
	GLfloat arg1, arg2;

	glColor3ub(color.r, color.g, color.b);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(center.x, center.y);
	for (int i = 0; i < 240; i++)
	{
		arg1 = center.x + (radius * (GLfloat)cos(i * 2 * M_PI / TRI_NUM));
		arg2 = center.y + (radius * (GLfloat)sin(i * 2 * M_PI / TRI_NUM));
		glVertex2f(arg1, arg2);
	}
	glEnd();
}

void Shape::render_quad()
{
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	glVertex2f(center.x - width / 2, center.y - height / 2);
	glVertex2f(center.x - width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y - height / 2);
	glEnd();
}

void Line::render_line()
{
	glLineWidth(width);
	glColor3i(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(from.x, from.y);
	glVertex2f(to.x, to.y);
	glEnd();
}

void Background::render()
{
	glColor3ub(color[0].r, color[0].g, color[0].b);
	glBegin(GL_QUADS);
	glVertex2f(body.center.x - body.width / 2, body.center.y - body.height / 2);
	glColor3ub(color[1].r, color[1].g, color[1].b);
	glVertex2f(body.center.x - body.width / 2, body.center.y + body.height / 2);
	glColor3ub(color[2].r, color[2].g, color[2].b);
	glVertex2f(body.center.x + body.width / 2, body.center.y + body.height / 2);
	glColor3ub(color[3].r, color[3].g, color[3].b);
	glVertex2f(body.center.x + body.width / 2, body.center.y - body.height / 2);
	glEnd();
}

void Shape::stroke_assignment()
{
	stroke[0].from.x = center.x - width / 2;
	stroke[0].from.y = center.y - height / 2;
	stroke[0].to.x = center.x - width / 2;
	stroke[0].to.y = center.y + height / 2;

	stroke[1].from.x = center.x - width / 2;
	stroke[1].from.y = center.y + height / 2;
	stroke[1].to.x = center.x + width / 2;
	stroke[1].to.y = center.y + height / 2;

	stroke[2].from.x = center.x + width / 2;
	stroke[2].from.y = center.y + height / 2;
	stroke[2].to.x = center.x + width / 2;
	stroke[2].to.y = center.y - height / 2;

	stroke[3].from.x = center.x + width / 2;
	stroke[3].from.y = center.y - height / 2;
	stroke[3].to.x = center.x - width / 2;
	stroke[3].to.y = center.y - height / 2;

	for (int i = 0; i < MAX_STROKE; i++)
	{
		stroke[i].width = 2.0;
		stroke[i].color.r = 0;
		stroke[i].color.g = 0;
		stroke[i].color.b = 0;
	}
}