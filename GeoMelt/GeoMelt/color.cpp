#include "headers.h"

void Background::set_color(Color *clr)
{
	for (int i = 0; i < CORNERS; i++)
	{
		color[i].r = clr[i].r;
		color[i].g = clr[i].g;
		color[i].b = clr[i].b;
	}
}

void RoundCornerBox::set_color(Color clr)
{
	vRectangle.color.r = clr.r;
	vRectangle.color.g = clr.g;
	vRectangle.color.b = clr.b;

	hRectangle.color.r = clr.r;
	hRectangle.color.g = clr.g;
	hRectangle.color.b = clr.b;

	for (int j = 0; j < CORNERS; j++)
	{
		corner[j].color.r = clr.r;
		corner[j].color.g = clr.g;
		corner[j].color.b = clr.b;
	}
}

Palette::Palette()
{
	sun.r = 255;
	sun.g = 255;
	sun.b = 100;

	moon.r = 225;
	moon.g = 225;
	moon.b = 215;

	platform.r = 99;
	platform.g = 160;
	platform.b = 0;

	black.r = 0;
	black.g = 0;
	black.b = 0;

	grey.r = 150;
	grey.g = 150;
	grey.b = 150;

	darkGrey.r = 25;
	darkGrey.g = 25;
	darkGrey.b = 25;

	lightGrey.r = 210;
	lightGrey.g = 210;
	lightGrey.b = 210;

	white.r = 255;
	white.g = 255;
	white.b = 255;

	red.r = 255;
	red.g = 0;
	red.b = 0;

	darkRed.r = 150;
	darkRed.g = 0;
	darkRed.b = 0;

	green.r = 0;
	green.g = 255;
	green.b = 0;

	darkGreen.r = 0;
	darkGreen.g = 150;
	darkGreen.b = 0;

	blue.r = 0;
	blue.g = 0;
	blue.b = 255;

	darkBlue.r = 0;
	darkBlue.g = 0;
	darkBlue.b = 150;
}

void Shape::set_color(Color clr)
{
	color.r = clr.r;
	color.g = clr.g;
	color.b = clr.b;
}

void Line::set_color(Color clr)
{
	color.r = clr.r;
	color.g = clr.g;
	color.b = clr.b;
}