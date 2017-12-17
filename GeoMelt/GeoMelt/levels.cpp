#include "headers.h"
#include "levels.h"

void Field_Level::build(Assets assets)
{
	srand((unsigned int)time(NULL));

	//Background Color Assignment
	background.body.center.x = 0;
	background.body.center.y = 0;
	background.body.width = 2.0f * width_resolution;
	background.body.height = 2.0f * height_resolution;

	background.set_color(assets.backgroundPalette.day);

	//Sun Attributes
	sun.radius = (GLfloat)height_resolution;
	sun.color = assets.palette.sun;
	sun.center.x = (GLfloat)width_resolution;
	sun.center.y = (GLfloat)height_resolution;

	//Floor Center
	platform[0].body.center.x = 0.0; 

	//Floor Dimensions
	platform[0].body.width = 5.0f * width_resolution / 6.0f;
	platform[0].body.height = height_resolution / 20.0f;
	platform[0].body.center.y = -height_resolution / 3.0f;

	//Floor Boundaries - For Physics
	platform[0].body.boundary_assignment();

	//Assign Color to Floor
	platform[0].body.color = assets.palette.platform;

	//Assign Floor Outline Attributes
	for (int i = 0; i < MAX_STROKE; i++)
	{
		platform[0].body.stroke[i].width = 2.0;
		platform[0].body.stroke[i].color = assets.palette.black;
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
	player[0] = new Ball;
	player[0]->build(assets);
	player[0]->body.color = assets.characterPalette.red_b;
	player[0]->reflection.color = assets.characterPalette.red_r;
	player[0]->body.center.x = -600;
	player[0]->body.center.y = (GLfloat)height_resolution;
	player[0]->controller.id = 0;

	player[1] = new Boxy;
	player[1]->build(assets);
	player[1]->body.color = assets.characterPalette.green_b;
	player[1]->reflection.color = assets.characterPalette.green_r;
	player[1]->body.center.x = -600;
	player[1]->body.center.y = height_resolution / 2.0f;
	player[1]->controller.id = 1;

	player[2] = new Ball;
	player[2]->build(assets);
	player[2]->body.color = assets.characterPalette.yellow_b;
	player[2]->reflection.color = assets.characterPalette.yellow_r;
	player[2]->body.center.x = 600;
	player[2]->body.center.y = (GLfloat)height_resolution;
	player[2]->controller.id = 2;

	player[3] = new Boxy;
	player[3]->build(assets);
	player[3]->body.color = assets.characterPalette.pink_b;
	player[3]->reflection.color = assets.characterPalette.pink_r;
	player[3]->body.center.x = 600;
	player[3]->body.center.y = height_resolution / 2.0f;
	player[3]->controller.id = 3;
}

void Field_Level::handler()
{
	render();

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (player[i]->stats.lifeState == ALIVE)
		player[i]->render();
	}
}

void Level::physics(Level lvl)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (lvl.player[i]->stats.lifeState != ELIMINATED)
			lvl.player[i]->update_position(lvl);
	}
}

void Field_Level::render()
{
	background.render();
	sun.render_circle();
	for (int i = 0; i < MAX_CLOUD; i++)
		clouds[i].render();
	platform[0].body.render();

	for (int i = 0; i < MAX_STROKE; i++)
		platform[0].body.stroke[i].render();
}

Field_Level::~Field_Level()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		player[i] = NULL;
		delete player[i];
	}
}

void Cloud::handler()
{
	GLfloat arg1;
	GLfloat arg2;

	//Use Data from Center Cloud
	arg1 = body[1].center.x + (body[1].radius * 3);
	arg2 = body[1].center.x - (body[1].radius * 3);

	//Reset if Last Cloud Offscreen
	if (arg1 < - width_resolution && direction == LEFT)
		set_cloud_group();
	else if (arg2 > width_resolution && direction == RIGHT)
		set_cloud_group();

	//Conduct Cloud Physics
	physics();
}

void Cloud::set_cloud_group()
{
	float clr = (float)(rand() % 55 + 200);
	GLfloat size = (GLfloat)(rand() % CLOUD_RANGE) + CLOUD_START;
	int level = (rand() % (2 * height_resolution)) - height_resolution;

	//For All Shapes Assign Color, Size, Y Coordinate
	for (int i = 0; i < CLOUD_GROUP; i++)
	{
		body[i].color.r = clr;
		body[i].color.g = clr;
		body[i].color.b = clr;
		body[i].radius = size;
		body[i].center.y = (GLfloat)level;
	}

	if (direction == LEFT) //Starting on Right
		body[1].center.x = (GLfloat) width_resolution + body[0].radius;
	else //Starting on Left
		body[1].center.x = - width_resolution - body[0].radius;

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

void Night_Level::build(Assets assets)
{
	//Background Attributes
	background.body.center.x = 0;
	background.body.center.y = 0;
	background.body.width = 2.0f * width_resolution;
	background.body.height = 2.0f * height_resolution;

	//Color assignment
	background.set_color(assets.backgroundPalette.night);

	//Moon Attributes
	moon.color = assets.palette.moon;
	moon.center.x = width_resolution / 2.0f;
	moon.center.y = height_resolution / 2.0f;
	moon.radius = height_resolution / 2.0f;

	//Star Attributes
	for (int i = 0; i < MAX_STAR; i++)
	{
		stars[i].offset = rnd();
		stars[i].body.radius = 3;
		stars[i].body.color = assets.palette.white;
		stars[i].compute_coordinates(i);
	}

	//Platform Horizontal Center
	platform[0].body.center.x = 0;
	platform[1].body.center.x = -750;
	platform[2].body.center.x = 0;
	platform[3].body.center.x = 750;

	//Platform Dimensions
	platform[0].body.width = 5.0f * width_resolution / 6.0f;
	platform[0].body.height = height_resolution / 20.0f;
	platform[0].body.center.y = -height_resolution / 3.0f;

	for (int i = 1; i < MAX_PLATFORM; i++)
	{
		platform[i].body.width = width_resolution / 4.0f;
		platform[i].body.height = height_resolution / 20.0f;
		platform[i].body.center.y = 100.0f;
	}

	for (int i = 0; i < MAX_PLATFORM; i++)
	{
		//Floor Boundaries - For Physics
		platform[i].body.boundary_assignment();

		//Assign Color to Floor
		platform[i].body.color = assets.palette.platform;
		
		//Assign Floor Outline Attributes
		platform[i].body.stroke_assignment();
	}

	//Player Position
	player[0] = new Ball;
	player[0]->build(assets);
	player[0]->body.color = assets.characterPalette.red_b;
	player[0]->reflection.color = assets.characterPalette.red_r;
	player[0]->body.center.x = -600;
	player[0]->body.center.y = (GLfloat)height_resolution;
	player[0]->controller.id = 0;

	player[1] = new Boxy;
	player[1]->build(assets);
	player[1]->body.color = assets.characterPalette.black_b;
	player[1]->reflection.color = assets.characterPalette.black_r;
	player[1]->body.center.x = -500;
	player[1]->body.center.y = (GLfloat)200;
	player[1]->controller.id = 1;

	player[2] = new Ball;
	player[2]->build(assets);
	player[2]->body.color = assets.characterPalette.white_b;
	player[2]->reflection.color = assets.characterPalette.white_r;
	player[2]->body.center.x = 600;
	player[2]->body.center.y = (GLfloat)height_resolution;
	player[2]->controller.id = 2;

	player[3] = new Boxy;
	player[3]->build(assets);
	player[3]->body.color = assets.characterPalette.pink_b;
	player[3]->reflection.color = assets.characterPalette.pink_r;
	player[3]->body.center.x = 550;
	player[3]->body.center.y = (GLfloat)100;
	player[3]->controller.id = 3;
}

void Night_Level::handler()
{
	render();
	
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (player[i]->stats.lifeState == ALIVE)
			player[i]->render();
	}
}

void Night_Level::render()
{
	background.render();
	for (int i = 0; i < MAX_STAR; i++)
	{
		stars[i].change_color();
		stars[i].body.render_circle();
	}
	moon.render_circle();
	for (int i = 0; i < MAX_PLATFORM; i++)
	{
		platform[i].body.render();
		for (int j = 0; j < MAX_STROKE; j++)
			platform[i].body.stroke[j].render();
	}
}

Night_Level::~Night_Level()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		player[i] = NULL;
		delete player[i];
	}
}

void Star::compute_coordinates(int count)
{
	int w = 2 * width_resolution;
	int h = 2 * height_resolution;
	int r1 = rand() % 400 - 200;
	int r2 = rand() % 400 - 200;
	float horizonalPartition = (float)w / 8;
	float verticalPartition = (float)h / 5;
	
	//Produces Randomly arranged stars
	body.center.x = ((count % 8 + 1) * horizonalPartition) - w / 2 - horizonalPartition / 2 + r1;
	body.center.y = ((count % 5 + 1) * verticalPartition) - h / 2 - verticalPartition / 2 + r1;

	//Produces Uniform Stars
	//body.center.x = ((count % 8 + 1) * horizonalPartition) - w / 2 - horizonalPartition / 2;
	//body.center.y = ((count % 5 + 1) * verticalPartition) - h / 2 - verticalPartition / 2;
}

void Star::change_color()
{
	//Stars Flicker in the Night Sky
	if (rand() % 2 == 0) 
	{ 
		body.color.r = 255; 
		body.color.g = (float) (rand() % (255 - 0));
		body.color.b = 215;
	}
	else 
	{ 
		body.color.r = (float)(rand() % (255 - 0));
		body.color.g = 215;
		body.color.b = 255;
	}
}

void Time_Level::build(Assets assets)
{
	srand((unsigned int)time(NULL));

	//Background Attribute Assignment
	time_of_day = EVENING;
	background.body.center.x = 0;
	background.body.center.y = 0;
	background.body.width = 2.0f * width_resolution;
	background.body.height = 2.0f * height_resolution;

	transition = false;

	//Initialize Background
	background.set_color(assets.backgroundPalette.evening);

	//Sun Attributes
	sun.radius = (GLfloat)height_resolution;
	sun.color = assets.palette.sun;
	sun.center.x = (GLfloat)width_resolution;
	sun.center.y = (GLfloat)height_resolution;

	//Moon Attributes
	moon.color = assets.palette.moon;
	moon.center.x = width_resolution / 2.0f;
	moon.center.y = height_resolution / 2.0f;
	moon.radius = height_resolution / 2.0f;

	//Star Attributes
	for (int i = 0; i < MAX_STAR; i++)
	{
		stars[i].offset = rnd();
		stars[i].body.radius = 3;
		stars[i].body.color = assets.palette.white;
		stars[i].compute_coordinates(i);
	}

	//Floor Dimensions
	platform[0].body.width = 5.0f * width_resolution / 6.0f;
	platform[0].body.height = height_resolution / 20.0f;
	platform[0].body.center.x = 0.0f;
	platform[0].body.center.y = -height_resolution / 3.0f;

	//Floor Boundaries - For Physics
	platform[0].body.boundary_assignment();

	//Assign Color to Floor
	platform[0].body.color = assets.palette.platform;

	//Assign Floor Outline Attributes
	for (int i = 0; i < MAX_STROKE; i++)
	{
		platform[0].body.stroke[i].width = 2.0;
		platform[0].body.stroke[i].color = assets.palette.black;
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
			clouds[i].direction = LEFT;

		//Assign Uniform Cloud Groups
		clouds[i].set_cloud_group();
	}

	//Player Position
	player[0] = new Ball;
	player[0]->build(assets);
	player[0]->body.color = assets.characterPalette.red_b;
	player[0]->reflection.color = assets.characterPalette.red_r;
	player[0]->body.center.x = -600;
	player[0]->body.center.y = (GLfloat)height_resolution;
	player[0]->controller.id = 0;

	player[1] = new Boxy;
	player[1]->build(assets);
	player[1]->body.color = assets.characterPalette.black_b;
	player[1]->reflection.color = assets.characterPalette.black_r;
	player[1]->body.center.x = -500;
	player[1]->body.center.y = (GLfloat)height_resolution / 2;
	player[1]->controller.id = 1;

	player[2] = new Ball;
	player[2]->build(assets);
	player[2]->body.color = assets.characterPalette.white_b;
	player[2]->reflection.color = assets.characterPalette.white_r;
	player[2]->body.center.x = 600;
	player[2]->body.center.y = (GLfloat)height_resolution;
	player[2]->controller.id = 2;

	player[3] = new Boxy;
	player[3]->build(assets);
	player[3]->body.color = assets.characterPalette.pink_b;
	player[3]->reflection.color = assets.characterPalette.pink_r;
	player[3]->body.center.x = 500;
	player[3]->body.center.y = (GLfloat)height_resolution / 2;
	player[3]->controller.id = 3;
}

void Time_Level::transition_handler(Palette_BG pal)
{
	if (transition == true)
		switch (time_of_day)
		{
		case DAY:
			transition_to(pal.afternoon);
			break;
		case AFTERNOON:
			transition_to(pal.evening);
			break;
		case EVENING:
			transition_to(pal.night);
			break;
		case NITE:
			transition_to(pal.dark_night);
			break;
		case DNITE:
			transition_to(pal.morning);
			break;
		case MORNING:
			transition_to(pal.day);
			break;
		}
}

void Time_Level::handler()
{
	render();

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (player[i]->stats.lifeState == ALIVE)
			player[i]->render();
	}
}

void Time_Level::render()
{
	background.render();
	if (time_of_day == DAY || time_of_day == AFTERNOON)
		sun.render_circle();
	else if (time_of_day != DAY && time_of_day != AFTERNOON)
	{
		for (int i = 0; i < MAX_STAR; i++)
		{
			stars[i].change_color();
			stars[i].body.render_circle();
		}
		moon.render_circle();
	}
	for (int i = 0; i < MAX_CLOUD; i++)
		clouds[i].render();
	platform[0].body.render();
	for (int i = 0; i < MAX_STROKE; i++)
		platform[0].body.stroke[i].render();
}

//changes color of background by factor of 1 each frame
void Time_Level::transition_to(Color *clr)
{
	//Transition from bg to clr
	Color *bg;

	//Adjust Color of Corners
	for (int i = 0; i < 4; i++)
	{
		bg = &background.color[i];

		//Update RED
		if (bg->r < clr[i].r)
			bg->r += TRANSITION_RATE_TOD;
		else if (bg->r > clr[i].r)
			bg->r -= TRANSITION_RATE_TOD;

		//Update GREEN
		if (bg->g < clr[i].g)
			bg->g += TRANSITION_RATE_TOD;
		else if (bg->g > clr[i].g)
			bg->g -= TRANSITION_RATE_TOD;

		//Update BLUE
		if (bg->b < clr[i].b)
			bg->b += TRANSITION_RATE_TOD;
		else if (bg->b > clr[i].b)
			bg->b -= TRANSITION_RATE_TOD;

		//If all corners are done updating
		if (bg->r == clr[i].r && bg->g == clr[i].g && bg->b == clr[i].b)
			background.transition_done[i] = true;
	}

	if (background.transition_done[0] == true && background.transition_done[1] == true
		&& background.transition_done[2] == true && background.transition_done[3] == true) 
	{
		//Transition is Done, Reset Attributes
		for (int i = 0; i < CORNERS; i++)
			background.transition_done[i] = false;
		
		transition = false;
		time_of_day++;
	}
}

Time_Level::~Time_Level()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		player[i] = NULL;
		delete player[i];
	}
}

Palette_BG::Palette_BG()
{
	enum TOD { DAY, AFTERNOON, EVENING, NITE, DNITE, MORNING };

	for (int i = 0; i < CORNERS; i++)
	{
		//BOTTOM
		if (i != 1 && i != 2) {
			day[i].r = 0;
			day[i].g = 155;
			day[i].b = 255;

			afternoon[i].r = 20;
			afternoon[i].g = 135;
			afternoon[i].b = 255;

			evening[i].r = 100;
			evening[i].g = 65;
			evening[i].b = 255;

			night[i].r = 70;
			night[i].g = 50;
			night[i].b = 120;

			dark_night[i].r = 10;
			dark_night[i].g = 15;
			dark_night[i].b = 60;

			morning[i].r = 100;
			morning[i].g = 75;
			morning[i].b = 202;

			overcast[i].r = 175;
			overcast[i].g = 175;
			overcast[i].b = 175;
		}
		else //TOP
		{
			day[i].r = 0;
			day[i].g = 60;
			day[i].b = 255;

			afternoon[i].r = 50;
			afternoon[i].g = 125;
			afternoon[i].b = 255;

			evening[i].r = 0;
			evening[i].g = 50;
			evening[i].b = 175;

			night[i].r = 25;
			night[i].g = 25;
			night[i].b = 75;

			dark_night[i].r = 10;
			dark_night[i].g = 10;
			dark_night[i].b = 20;

			morning[i].r = 10;
			morning[i].g = 10;
			morning[i].b = 50;

			overcast[i].r = 215;
			overcast[i].g = 215;
			overcast[i].b = 215;
		}
	}
}