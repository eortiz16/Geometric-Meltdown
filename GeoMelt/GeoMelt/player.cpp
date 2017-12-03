#include "headers.h"
#include "player.h"

extern Game game;

void Player::update_reflection_x()
{
	//Takes the width resolution and scales down to a factor
	//controls reflection of character

	GLfloat OldMax, OldMin, OldValue;
	GLfloat NewMax, NewMin;
	GLfloat offset = 0.0f;

	//if character is in the middle of the level
	if (body.center.x == 0.0f)
		reflection.center.x = 0.0f;
	else 
	{
		OldValue = body.center.x;
		OldMin = 0;
		OldMax = (GLfloat)HDY;
		NewMin = 0;
		NewMax = sqrt(body.radius - 10);
		offset = (OldValue - OldMin) * (NewMax - NewMin);
		offset /= (OldMax - OldMin);
		offset += NewMin;
	}

	if (body.center.x > 0.0f)
		offset *= -1;

	reflection.center.x = body.center.x + offset;
}

Ball::Ball()
{
	//Default Character Values
	JUMP_MAX = 4;
	jumpCount = 0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	on_ground = false;
	
	//Default Player Dimensions
	body.width = 100;
	body.height = body.width;
	body.radius = body.width/2;

	//Player Boundaries
	body.top_bnd = body.center.y + body.radius;
	body.bottom_bnd = body.center.y - body.radius;
	body.left_bnd = body.center.x - body.radius;
	body.right_bnd = body.center.x + body.radius;

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

void Ball::update_position(Level lvl)
{
	physics(lvl);
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius);
	outline.center.x = body.center.x;
	outline.center.y = body.center.y;

	//Player Boundaries
	body.top_bnd = body.center.y + body.radius;
	body.bottom_bnd = body.center.y - body.radius;
	body.left_bnd = body.center.x - body.radius;
	body.right_bnd = body.center.x + body.radius;
}

void Ball::physics(Level lvl)
{
	//This character is less affected by gravity
	velocity.y -= 3.0f * GLfloat(GRAVITY) / 4.0f;
	body.center.y += velocity.y;
	body.center.x += velocity.x;

	//for (int i = 0; i < MAX_PLATFORM; i++)
	int i = 0;
	if (body.bottom_bnd <= lvl.platform[i].body.top_bnd
		&& body.bottom_bnd > lvl.platform[i].body.bottom_bnd
		&& body.center.x >= lvl.platform[i].body.left_bnd
		&& body.center.x <= lvl.platform[i].body.right_bnd
		&& velocity.y < 0.0)
	{
		on_ground = true;
		jumpCount = 0;
		velocity.y *= -0.25f;
		body.center.y = lvl.platform[i].body.top_bnd + body.height / 2;
	}
	else
		on_ground = false;

	//affect horizontal momentum with friction
	if (velocity.x < 0.0 && on_ground)
	{
		velocity.x += (GLfloat)FRICTION;
		if (velocity.x > 0.0)
			velocity.x = 0.0;
	}
	else if (velocity.x > 0.0 && on_ground)
	{
		velocity.x -= (GLfloat)FRICTION;
		if (velocity.x < 0.0)
			velocity.x = 0.0;
	}
}

void Ball::jump()
{
	on_ground = false;
	if (jumpCount < JUMP_MAX)
	{
		exhale(); //Change character's size
		velocity.y = 7.0f;
		jumpCount++;
	}
}

void Ball::exhale()
{

}

void Ball::move()
{
	if (direction == LEFT) 
		velocity.x = -5.0f;
	else // RIGHT
		velocity.x = 5.0f;

	if (on_ground)
		velocity.y = 1.25f;
}

Boxy::Boxy()
{
	//Default Character Values
	JUMP_MAX = 2;
	jumpCount = 0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	on_ground = false;

	//Default Player Dimensions
	body.width = 100;
	body.height = body.width;
	body.radius = body.width / 2;

	//Player Boundaries
	body.top_bnd = body.center.y + body.height / 2;
	body.bottom_bnd = body.center.y - body.height / 2;
	body.left_bnd = body.center.x - body.height / 2;
	body.right_bnd = body.center.x + body.height / 2;

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

	//Adjust Reflection
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

void Boxy::update_position(Level lvl)
{
	physics(lvl);
	update_reflection_x();
	reflection.center.y = body.center.y + sqrt(body.radius) * 2;
	body.stroke_assignment();

	//Player Boundaries
	body.top_bnd = body.center.y + body.height / 2;
	body.bottom_bnd = body.center.y - body.height / 2;
	body.left_bnd = body.center.x - body.height / 2;
	body.right_bnd = body.center.x + body.height / 2;
}

void Boxy::physics(Level lvl)
{
	velocity.y -= GLfloat(GRAVITY);
	body.center.y += velocity.y;
	body.center.x += velocity.x;

	//for (int i = 0; i < MAX_PLATFORM; i++)
	int i = 0;
	if (body.bottom_bnd <= lvl.platform[i].body.top_bnd 
		&& body.bottom_bnd >= lvl.platform[i].body.bottom_bnd
		&& body.center.x >= lvl.platform[i].body.left_bnd
		&& body.center.x <= lvl.platform[i].body.right_bnd 
		&& velocity.y < 0.0)
	{
		on_ground = true;
		jumpCount = 0;
		velocity.y *= -0.25f;
		body.center.y = lvl.platform[i].body.top_bnd + body.height / 2;
	}
	else
		on_ground = false;

	//affect horizontal momentum with friction
	if (velocity.x < 0.0 && on_ground)
	{
		velocity.x += (GLfloat)FRICTION;
		if (velocity.x > 0.0)
			velocity.x = 0.0;
	}
	else if (velocity.x > 0.0 && on_ground)
	{
		velocity.x -= (GLfloat)FRICTION;
		if (velocity.x < 0.0)
			velocity.x = 0.0;
	}
}

void Boxy::jump()
{
	on_ground = false;
	//Check if jumpcount is less than jumpmax
	if (jumpCount < JUMP_MAX)
	{
		velocity.y = 7.0f;
		jumpCount++;
	}
}

void Boxy::move()
{
	if (direction == LEFT)
		velocity.x = -6.0f;
	else // RIGHT
		velocity.x = 6.0f;

	if (on_ground)
		velocity.y = 1.25f;
}