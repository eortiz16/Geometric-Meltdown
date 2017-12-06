#include "headers.h"
#include "render.h"

extern GLFWwindow *window;

void Shape::render_circle()
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

void Shape::render_quad()
{
	glColor3ub((GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b);
	glBegin(GL_QUADS);
	glVertex2f(center.x - width / 2, center.y - height / 2);
	glVertex2f(center.x - width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y + height / 2);
	glVertex2f(center.x + width / 2, center.y - height / 2);
	glEnd();
}

Line::Line()
{
	width = 2.0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
}

void Line::render_line()
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
	vertical_box.render_quad();
	horizontal_box.render_quad();

	for (int j = 0; j < 4; j++)
	{
		corner[j].render_circle();
	}
}

void RoundCornerBox::build()
{
	int size = 100; // diameter of circle

	vertical_box.height = height; // actual height
	
	horizontal_box.center.x = vertical_box.center.x;
	horizontal_box.center.y = vertical_box.center.y;
	horizontal_box.width = width; // actual width

	vertical_box.width = horizontal_box.width - size;
	horizontal_box.height = vertical_box.height - size;
	horizontal_box.boundary_assignment();
	vertical_box.boundary_assignment();

	//bottom left
	corner[0].radius = size / 2;
	corner[0].center.x = vertical_box.left_bnd;
	corner[0].center.y = horizontal_box.bottom_bnd;

	//top left
	corner[1].radius = size / 2;
	corner[1].center.x = vertical_box.left_bnd;
	corner[1].center.y = horizontal_box.top_bnd;

	//top right
	corner[2].radius = size / 2;
	corner[2].center.x = vertical_box.right_bnd;
	corner[2].center.y = horizontal_box.top_bnd;

	//bottom right
	corner[3].radius = size / 2;
	corner[3].center.x = vertical_box.right_bnd;
	corner[3].center.y = horizontal_box.bottom_bnd;
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
}

void Shape::boundary_assignment()
{
	top_bnd = center.y + height / 2;
	bottom_bnd = center.y - height / 2;
	left_bnd = center.x - width / 2;
	right_bnd = center.x + width / 2;
}

void Game::render_triangle()
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(::window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	//glfwSwapBuffers(::window); //global
	glfwPollEvents();
}