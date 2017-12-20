#include "headers.h"
#include "render.h"

Line::Line()
{
	width = 2.0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
}

void Line::render()
{
	glLineWidth(width);
	glColor3i((GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b);
	glBegin(GL_LINES);
	glVertex2f(from.x, from.y);
	glVertex2f(to.x, to.y);
	glEnd();
}

void Background::render()
{
	glBegin(GL_QUADS);
	glColor4ub((GLubyte)color[0].r, (GLubyte)color[0].g, (GLubyte)color[0].b, 255);
	glVertex2f(body.center.x - body.width / 2, body.center.y - body.height / 2);
	glColor4ub((GLubyte)color[1].r, (GLubyte)color[1].g, (GLubyte)color[1].b, 255);
	glVertex2f(body.center.x - body.width / 2, body.center.y + body.height / 2);
	glColor4ub((GLubyte)color[2].r, (GLubyte)color[2].g, (GLubyte)color[2].b, 255);
	glVertex2f(body.center.x + body.width / 2, body.center.y + body.height / 2);
	glColor4ub((GLubyte)color[3].r, (GLubyte)color[3].g, (GLubyte)color[3].b, 255);
	glVertex2f(body.center.x + body.width / 2, body.center.y - body.height / 2);
	glEnd();	
	glfwPollEvents();
}

void RoundCornerBox::render()
{
	vRectangle.render();
	hRectangle.render();

	for (int j = 0; j < 4; j++)
	{
		corner[j].render();
	}
}

void RoundCornerBox::build()
{
	int size = 250; // diameter of circle

	vRectangle.height = height; // actual height
	hRectangle.width = width; // actual width

	//Set center of both boxes
	vRectangle.center.x = center.x;
	vRectangle.center.y = center.y;
	hRectangle.center.x = center.x;
	hRectangle.center.y = center.y;

	vRectangle.width = hRectangle.width - size;
	hRectangle.height = vRectangle.height - size;
	hRectangle.boundary_assignment();
	vRectangle.boundary_assignment();

	//bottom left
	corner[0].radius = size / 2.0f;
	corner[0].center.x = vRectangle.boundary.left;
	corner[0].center.y = hRectangle.boundary.bottom;

	//top left
	corner[1].radius = size / 2.0f;
	corner[1].center.x = vRectangle.boundary.left;
	corner[1].center.y = hRectangle.boundary.top;

	//top right
	corner[2].radius = size / 2.0f;
	corner[2].center.x = vRectangle.boundary.right;
	corner[2].center.y = hRectangle.boundary.top;

	//bottom right
	corner[3].radius = size / 2.0f;
	corner[3].center.x = vRectangle.boundary.right;
	corner[3].center.y = hRectangle.boundary.bottom;
}

void Platform::stroke_assignment()
{
	stroke[0].from.x = body.boundary.left;
	stroke[0].from.y = body.boundary.bottom;
	stroke[0].to.x = body.boundary.left;
	stroke[0].to.y = body.boundary.top;

	stroke[1].from.x = body.boundary.left;
	stroke[1].from.y = body.boundary.top;
	stroke[1].to.x = body.boundary.right;
	stroke[1].to.y = body.boundary.top;

	stroke[2].from.x = body.boundary.right;
	stroke[2].from.y = body.boundary.top;
	stroke[2].to.x = body.boundary.right;
	stroke[2].to.y = body.boundary.bottom;

	stroke[3].from.x = body.boundary.right;
	stroke[3].from.y = body.boundary.bottom;
	stroke[3].to.x = body.boundary.left;
	stroke[3].to.y = body.boundary.bottom;
}

void Shape::boundary_assignment()
{
	boundary.top = center.y + height / 2;
	boundary.bottom = center.y - height / 2;
	boundary.left = center.x - width / 2;
	boundary.right = center.x + width / 2;
}

void Circle::render()
{
	GLfloat arg1, arg2;

	glColor3ub((GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b);
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

void Quad::render()
{
	glColor3ub((GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b);
	glBegin(GL_QUADS);
	glVertex2f(center.x - width / 2, center.y - height / 2);
	glVertex2f(center.x - width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y - height / 2);
	glEnd();
}

