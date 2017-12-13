#include "headers.h"

Color::Color(const Color &obj)
{
	r = obj.r;
	g = obj.g;
	b = obj.b;
}

void Background::set_color(Color *clr)
{
	for (int i = 0; i < CORNERS; i++)
		color[i] = clr[i];
}

void RoundCornerBox::set_color(Color clr)
{
	vRectangle.color = clr;
	hRectangle.color = clr;

	for (int j = 0; j < CORNERS; j++)
		corner[j].color = clr;
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

Palette_CHAR::Palette_CHAR()
{
	red_b.r = 255;
	red_b.g = 75;
	red_b.b = 75;

	red_r.r = 255;
	red_r.g = 125;
	red_r.b = 125;

	green_b.r = 75;
	green_b.g = 255;
	green_b.b = 75;

	green_r.r = 150;
	green_r.g = 255;
	green_r.b = 150;

	blue_b.r = 150;
	blue_b.g = 150;
	blue_b.b = 255;

	blue_r.r = 180;
	blue_r.g = 180;
	blue_r.b = 255;

	yellow_b.r = 255;
	yellow_b.g = 225;
	yellow_b.b = 0;

	yellow_r.r = 255;
	yellow_r.g = 250;
	yellow_r.b = 0;

	pink_b.r = 255;
	pink_b.g = 150;
	pink_b.b = 150;

	pink_r.r = 255;
	pink_r.g = 180;
	pink_r.b = 180;

	purple_b.r = 85;
	purple_b.g = 35;
	purple_b.b = 160;

	purple_r.r = 100;
	purple_r.g = 50;
	purple_r.b = 175;

	white_b.r = 225;
	white_b.g = 225;
	white_b.b = 225;

	white_r.r = 255;
	white_r.g = 255;
	white_r.b = 255;

	black_b.r = 75;
	black_b.g = 75;
	black_b.b = 75;

	black_r.r = 125;
	black_r.g = 125;
	black_r.b = 125;
}

void Line::set_color(Color clr)
{
	color = clr;
}