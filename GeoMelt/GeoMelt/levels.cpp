#include "Headers.h"
#include "levels.h"

extern Game game;

Field_Level::Field_Level()
{
	srand((unsigned int)time(NULL));
	
	//Assigning Window Dimensions
	game.game_inita(); // MOve this to appropriate spot
	GLfloat w = (GLfloat)game.win.width;
	GLfloat h = (GLfloat)game.win.height;

	//Background Color Assignment
	background.body.center.x = w / 2;
	background.body.center.y = h / 2;
	background.body.width = 2 * w;
	background.body.height = 2 * h;

	for (int i = 0; i < 4; i++)
		if (i != 1 && i != 2) {
			background.color[i].r = 0;
			background.color[i].g = 155;
			background.color[i].b = 255;
		} else {
			background.color[i].r = 0;
			background.color[i].g = 60;
			background.color[i].b = 255;
		}

	//Sun Attributes
	sun.radius = (GLfloat)(h / 1.1);
	sun.color.r = 255;
	sun.color.g = 255;
	sun.color.b = 100;
	sun.center.x = (GLfloat)(1.5 * w);
	sun.center.y = (GLfloat)(1.5 * h);

	//Floor Center
	platform[0].body.center.x = (GLfloat) (w / 2); 

	//Floor Dimensions
	platform[0].body.width = 3 * (GLfloat) (w / 4);
	platform[0].body.height = (GLfloat) h / 20;
	platform[0].body.center.y = platform[0].body.height / 2 + 150;

	//Assign Color to Floor
	platform[0].body.color.r = 99;
	platform[0].body.color.g = 160;
	platform[0].body.color.b = 0;

	//Assign Floor Outline Attributes
	for (int i = 0; i < MAX_STROKE; i++)
	{
		platform[0].body.stroke[i].width = 2.0;
		platform[0].body.stroke[i].color.r = 255;
		platform[0].body.stroke[i].color.g = 255;
		platform[0].body.stroke[i].color.b = 255;
	}

	//Floor Stroke Assignment
	platform[0].body.stroke_assignment();

	//Cloud Initialization
	int dir = rand() % 2;
	for (int i = 0; i < MAX_CLOUD; i++)
	{
		//Set Wind Direction for All Clouds
		(dir == 0) ? 
			clouds[i].direction = RIGHT : 
			clouds[i].direction = LEFT ;
		
		//Assign Uniform Cloud Groups
		clouds[i].set_cloud_group();
	}

	//Player Position
	player1.body.center.x = 300;
	player1.body.center.y = (GLfloat)game.win.height;
	player2.body.center.x = 0;
	player2.body.center.y = (GLfloat)game.win.height / 2;
}

void Field_Level::handler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < MAX_CLOUD; i++)
		clouds[i].handler();
	render();
	player1.update_position();
	player1.render();
	player2.update_position();
	player2.render();
}

void Field_Level::render()
{
	background.render();
	sun.render_circle();
	for (int i = 0; i < MAX_CLOUD; i++)
		clouds[i].render();
	platform[0].body.render_quad();

	for (int i = 0; i < MAX_STROKE; i++)
		platform[0].body.stroke[i].render_line();
}

void Cloud::handler()
{
	GLfloat arg1;
	GLfloat arg2;

	//Use Data from Center Cloud
	arg1 = body[1].center.x + (body[1].radius * 3);
	arg2 = body[1].center.x - (body[1].radius * 3);

	//Reset if Last Cloud Offscreen
	if (arg1 < -game.win.width / 2 && direction == LEFT)
		set_cloud_group();
	else if (arg2 > 1.5 *game.win.width && direction == RIGHT)
		set_cloud_group();

	//Conduct Cloud Physics
	physics();

}

void Cloud::set_cloud_group()
{
	int clr = rand() % 55 + 200;
	GLfloat size = (GLfloat)(rand() % CLOUD_RANGE) + CLOUD_START;
	GLfloat level = (GLfloat)(rand() % (2 * game.win.height) + (-game.win.height / 2));

	//For All Shapes Assign Color, Size, Y Coordinate
	for (int i = 0; i < CLOUD_GROUP; i++)
	{
		body[i].color.r = clr;
		body[i].color.g = clr;
		body[i].color.b = clr;
		body[i].radius = size;
		body[i].center.y = level;
	}

	if (direction == LEFT) //Starting on Right
		body[1].center.x = (GLfloat)((game.win.width * 1.5) + body[0].radius);
	else //Starting on Left
		body[1].center.x = (-game.win.width/2) - body[0].radius;

	body[0].center.x = body[1].center.x - body[1].radius;
	body[2].center.x = body[1].center.x + body[1].radius;

	//Set Speed - Based on Size (Kind of)
	speed = (int)(body[0].radius * rnd()) % MAX_SPEED + 1;
}

void Cloud::render()
{
	for (int i = 0; i < CLOUD_GROUP; i++)
		body[i].render_circle(); 
}

void Cloud::physics()
{
	//Change Position Based on Established Speed
	if (direction == LEFT)
		for (int i = 0; i < CLOUD_GROUP; i++)
			body[i].center.x -= speed;
	else
		for (int i = 0; i < CLOUD_GROUP; i++)
			body[i].center.x += speed;
}

Night_Level::Night_Level()
{
	//Assigning Window Dimensions
	w = (GLfloat)game.win.width;
	h = (GLfloat)game.win.height;

	//Background Attributes
	background.body.center.x = w / 2;
	background.body.center.y = h / 2;
	background.body.width = 2*w;
	background.body.height = 2*h;

	//Color assignment
	for (int i = 0; i < 4; i++)
		if (i != 1 && i != 2) {
			background.color[i].r = 70;
			background.color[i].g = 50;
			background.color[i].b = 120;
		} else {
			background.color[i].r = 0;
			background.color[i].g = 25;
			background.color[i].b = 120;
		}

	//Moon Attributes
	moon.color.r = 225;
	moon.color.g = 225; 
	moon.color.b = 214;
	moon.center.x = w;
	moon.center.y = h;
	moon.radius = h/2;

	//Second Star Refactoring
	for (int i = 0; i < MAX_STAR; i++)
	{
		stars[i].offset = rnd();
		stars[i].body.radius = 3;
		stars[i].body.color.r = 255;
		stars[i].body.color.g = 255;
		stars[i].body.color.b = 255;
		stars[i].compute_coordinates(i);
	}

	//Floor Center
	platform[0].body.center.x = w / 2;

	//Floor Dimensions
	platform[0].body.width = 3*w/4;
	platform[0].body.height = h/20;
	platform[0].body.center.y = platform[0].body.height / 2 + 150;

	//Assign Color to Floor
	platform[0].body.color.r = 99;
	platform[0].body.color.g = 160;
	platform[0].body.color.b = 0;

	//Assign Floor Outline Attributes
	platform[0].body.stroke_assignment();

	//Platform Attributes
	for (int i = 1; i < MAX_PLATFORM; i++) {
		if (i % 2 == 0) {
			platform[i].body.center.x = w / 2;
			platform[i].body.center.y = h - h / 2 + h / 6;
		}
		else {
			platform[i].body.center.x = w / 6 + ((w - w / 6) *
				((GLfloat)i - 1)) / 2.5f;
			platform[i].body.center.y = h - h / 2;
		}
		platform[i].body.width = 250;
		platform[i].body.height = 50;
		platform[i].body.color.r = 99;
		platform[i].body.color.g = 160;
		platform[i].body.color.b = 0;
	}

	//Player Position
	player1.body.center.x = 300;
	player1.body.center.y = (GLfloat)game.win.height;
	player2.body.center.x = 0;
	player2.body.center.y = (GLfloat)game.win.height / 2;
}

void Night_Level::handler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render();
	player1.update_position();
	player1.render();
	player2.update_position();
	player2.render();
}

void Night_Level::render()
{
	background.render();
	//render_stars(starOffset, w, h);
	for (int i = 0; i < MAX_STAR; i++)
	{
		stars[i].change_color();
		stars[i].body.render_circle();
	}
	moon.render_circle();
	platform[0].body.render_quad();
	for (int i = 0; i < MAX_STROKE; i++)
		platform[0].body.stroke[i].render_line();
}

void Star::compute_coordinates(int count)
{
	int w = 2 * game.win.width;
	int h = 2 * game.win.height;
	int r1 = rand() % 400 - 200;
	int r2 = rand() % 400 - 200;
	float horizonalPartition = (float)w / 8;
	float verticalPartition = (float)h / 5;
	
	body.center.x = (GLfloat)(((count % 8 + 1) * horizonalPartition) - w / 3.2 + r1);
	body.center.y = (GLfloat)(((count % 5 + 1) * verticalPartition) - h / 2.9 + r2);

	//Produces Uniform Stars
	//body.center.x = ((count % 8 + 1) * horizonalPartition) - w / 3.2;
	//body.center.y = ((count % 5 + 1) * verticalPartition) - h / 2.9;
}

void Star::change_color()
{
	//Stars Flicker in the Night Sky
	if (rand() % 2 == 0) 
	{ 
		body.color.r = 255; 
		body.color.g = rand() % (255 - 0);
		body.color.b = 215;
	}
	else 
	{ 
		body.color.r = rand() % (255 - 0);
		body.color.g = 215;
		body.color.b = 255;
	}
}