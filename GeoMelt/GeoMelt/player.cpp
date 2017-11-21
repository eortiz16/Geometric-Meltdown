#include "Headers.h"
#include "player.h"
extern Game game;

Ball::Ball()
{
	//Default Character Values
	JUMP_MAX = 4;
	jumpCount = 0;
	
	//Default Player Dimensions
	body.width = 100;
	body.height = body.width;
	body.radius = body.width/2;

	outline.radius = body.radius + 4;
	eye.radius = (body.radius / 10) + 1;
	shadow.radius = body.radius - body.radius / 4;

	//Default Position
	body.center.x = 0;
	body.center.y = (GLfloat)game.win.height/2;
	outline.center.x = body.center.x;
	outline.center.y = body.center.y;
	
	//shadow.center.x = body.center.x;
	shadow.center.x = scale_position(body.radius, body.center.x);
	shadow.center.y = body.center.y + sqrt(body.radius);
	
	//Color Assignment
	outline.color.r = 0;
	outline.color.g = 0;
	outline.color.b = 0;

	body.color.r = 85;
	body.color.g = 35;
	body.color.b = 160;

	shadow.color.r = 100;
	shadow.color.g = 50;
	shadow.color.b = 175;

	eye.color.r = 0;
	eye.color.g = 0;
	eye.color.b = 0;

	//Default Direction
	direction = RIGHT;
}

void Ball::render()
{
	//Player Outline
	outline.render_circle();

	//Player Body
	body.render_circle();
	
	//Player Shadow
	shadow.center.x = scale_position(body.radius, body.center.x);
	shadow.render_circle();

	//Player Eye
	eye.center.y = body.center.y + body.radius/2;
	if (direction == LEFT)
		eye.center.x = body.center.x - body.radius/2;
	else
		eye.center.x = body.center.x + body.radius/2;

	eye.render_circle();
}

//Take the width resolution and scale the entire thing down to a factor
//controls shading of character
GLfloat scale_position(GLfloat objRadius, GLfloat objCoorX)
{
	GLfloat OldMax, OldMin, OldValue;
	GLfloat NewMax, NewMin, offset;

	//if character is in the middle of the level
	if (objCoorX == (GLfloat)game.win.width / 2)
		return (GLfloat)game.win.width / 2;
	else if (objCoorX < game.win.width / 2)
	{
		OldValue = objCoorX;
		OldMin = 0;
		OldMax = (GLfloat)game.win.width / 2;
		NewMin = 0;
		NewMax = sqrt(objRadius - 10);
		offset = (OldValue - OldMin) * (NewMax - NewMin);
		offset /= (OldMax - OldMin);
		offset += NewMin;
		offset -= sqrt(objRadius - 10);
		offset = abs(offset);
		return objCoorX + offset;
	}
	else 
	{
		OldValue = objCoorX;
		OldMin = (GLfloat)game.win.width / 2;
		OldMax = (GLfloat)game.win.width;
		NewMin = 0;
		NewMax = sqrt(objRadius);
		offset = (OldValue - OldMin) * (NewMax - NewMin);
		offset /= OldMax - OldMin;
		offset += NewMin;
		return objCoorX - offset;
	}
}

Boxy::Boxy()
{
	//Default Character Values
	JUMP_MAX = 2;
	jumpCount = 0;

	//Default Position
	body.center.x = 300;
	body.center.y = (GLfloat)game.win.height;

	//Default Player Dimensions
	body.width = 100;
	body.height = body.width;
	body.radius = body.width / 2;

	//Stroke Assignment
	body.stroke_assignment();

	eye.width = body.width/20 + 1;
	eye.height = eye.width;
	eye.radius = eye.width;

	shadow.width = body.width/1.5f;
	shadow.height = shadow.width;
	shadow.radius = shadow.width / 2;
	shadow.center.x = scale_position(body.radius, body.center.x);
	shadow.center.y = body.center.y + sqrt(body.radius)*2;

	//Color Assignment
	body.color.r = 85;
	body.color.g = 35;
	body.color.b = 160;

	shadow.color.r = 100;
	shadow.color.g = 50;
	shadow.color.b = 175;

	eye.color.r = 0;
	eye.color.g = 0;
	eye.color.b = 0;

	//Default Direction
	direction = LEFT;
}

void Boxy::render()
{
	//Player Body
	body.render_quad();

	//Player Shadow
	shadow.center.x = scale_position(body.radius, body.center.x);
	shadow.render_quad();

	//Player Eye
	eye.center.y = body.center.y + body.radius / 2;
	if (direction == LEFT)
		eye.center.x = body.center.x - body.radius / 2;
	else
		eye.center.x = body.center.x + body.radius / 2;

	eye.render_circle();

	//Player Stroke	
	for (int i = 0; i < MAX_STROKE; i++)
		body.stroke[i].render_line();
}