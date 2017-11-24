#include "headers.h"
#include "player.h"

extern Game game;

void Player::update_reflection_x()
{
	//Takes the width resolution and scales down to a factor
	//controls reflection of character

	GLfloat OldMax, OldMin, OldValue;
	GLfloat NewMax, NewMin, offset;

	//if character is in the middle of the level
	if (body.center.x == (GLfloat)game.window.width / 2)
		reflection.center.x = (GLfloat)game.window.width / 2;
	else if (body.center.x < game.window.width / 2)
	{
		OldValue = body.center.x;
		OldMin = 0;
		OldMax = (GLfloat)game.window.width / 2;
		NewMin = 0;
		NewMax = sqrt(body.radius - 10);
		offset = (OldValue - OldMin) * (NewMax - NewMin);
		offset /= (OldMax - OldMin);
		offset += NewMin;
		offset -= sqrt(body.radius - 10);
		offset = abs(offset);
		reflection.center.x = body.center.x + offset;
	}
	else
	{
		OldValue = body.center.x;
		OldMin = (GLfloat)game.window.width / 2;
		OldMax = (GLfloat)game.window.width;
		NewMin = 0;
		NewMax = sqrt(body.center.x);
		offset = (OldValue - OldMin) * (NewMax - NewMin);
		offset /= OldMax - OldMin;
		offset += NewMin;
		reflection.center.x = body.center.x - offset;
	}
}

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
	reflection.radius = body.radius - body.radius / 4;

	outline.center.x = body.center.x;
	outline.center.y = body.center.y;
	
	//shadow.center.x = body.center.x;
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius);
	
	//Color Assignment
	outline.color.r = 0;
	outline.color.g = 0;
	outline.color.b = 0;

	body.color.r = 85;
	body.color.g = 35;
	body.color.b = 160;

	reflection.color.r = 100;
	reflection.color.g = 50;
	reflection.color.b = 175;

	eye.color.r = 0;
	eye.color.g = 0;
	eye.color.b = 0;

	//Default Direction
	direction = RIGHT;
}

void Ball::render()
{
	outline.render_circle();
	body.render_circle();

	//Adjust Shadow
	update_reflection_x();
	reflection.render_circle();

	eye.center.y = body.center.y + body.radius/2;
	(direction == LEFT) ?
		eye.center.x = body.center.x - body.radius/2 :
		eye.center.x = body.center.x + body.radius/2 ;
	eye.render_circle();
	
}

void Ball::update_position()
{
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius);
	outline.center.x = body.center.x;
	outline.center.y = body.center.y;
}

Boxy::Boxy()
{
	//Default Character Values
	JUMP_MAX = 2;
	jumpCount = 0;

	//Default Player Dimensions
	body.width = 100;
	body.height = body.width;
	body.radius = body.width / 2;

	//Stroke Assignment
	body.stroke_assignment();

	eye.width = body.width/20 + 1;
	eye.height = eye.width;
	eye.radius = eye.width;

	reflection.width = body.width/1.5f;
	reflection.height = reflection.width;
	reflection.radius = reflection.width / 2;
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius)*2;

	//Color Assignment
	body.color.r = 85;
	body.color.g = 35;
	body.color.b = 160;

	reflection.color.r = 100;
	reflection.color.g = 50;
	reflection.color.b = 175;

	eye.color.r = 0;
	eye.color.g = 0;
	eye.color.b = 0;

	//Default Direction
	direction = LEFT;
}

void Boxy::render()
{
	body.render_quad();

	//Adjust Shadow
	update_reflection_x();
	reflection.render_quad();

	eye.center.y = body.center.y + body.radius / 2;
	(direction == LEFT) ?
		eye.center.x = body.center.x - body.radius / 2 :
		eye.center.x = body.center.x + body.radius / 2 ;
	eye.render_circle();

	for (int i = 0; i < MAX_STROKE; i++)
		body.stroke[i].render_line();
}

void Boxy::update_position()
{
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius) * 2;
	body.stroke_assignment();
}