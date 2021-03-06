#include "headers.h"
#include "player.h"

void Player::update_reflection_x()
{
	//Takes the width resolution and scales down to a factor
	//controls reflection of character

	GLfloat OldMax, OldMin, OldValue;
	GLfloat NewMax, NewMin;
	GLfloat offset = 0.0f;

	OldValue = body->center.x;
	OldMin = 0;
	OldMax = (GLfloat)HDY;
	NewMin = 0;
	NewMax = sqrt(body->radius - 10);
	offset = (OldValue - OldMin) * (NewMax - NewMin);
	offset /= (OldMax - OldMin);
	offset += NewMin;
	offset *= -1;

	reflection->center.x = body->center.x + offset;
}

void Player::attack()
{
	attk = true;
	(direction == RIGHT) ?
		arm.center.x = body->center.x + body->width / 2 :
		arm.center.x = body->center.x - body->width / 2;
	armOutline.center.x = arm.center.x;
}

void Ball::build(Assets assets)
{
	//Default Character Values
	JUMP_MAX = 4;
	jumpCount = 0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	on_ground = false;
	attk = false;

	//Polymorphism
	body = new Circle;
	reflection = new Circle;

	//Default Player Dimensions
	body->width = 100;
	body->height = body->width;
	body->radius = body->width/2;

	//Arm
	arm.width = 100;
	arm.height = 25;
	arm.boundary_assignment();
	armOutline.width = 108;
	arm.height = 29;
	armOutline.color = assets.palette.black;

	//Player Boundaries
	body->boundary_assignment();

	outline.radius = body->radius + 4;
	eye.radius = (body->radius / 10) + 1;
	reflection->radius = body->radius - body->radius / 4;

	outline.center.x = body->center.x;
	outline.center.y = body->center.y;
	
	//shadow.center.x = body.center.x;
	update_reflection_x();
	reflection->center.y = body->center.y + sqrt(body->radius);
	
	//Color Assignment
	outline.color = assets.palette.black;
	eye.color = assets.palette.black;

	//Default Center
	body->center.x = 0;
	body->center.y = 0;

	//Default Direction
	direction = RIGHT;
}

Ball::~Ball()
{
	body = NULL;
	delete body;
	reflection = NULL;
	delete reflection;
}

void Ball::render()
{
	if (stats.lifeState == ALIVE)
	{
		outline.render();
		if (attk)
		{
			armOutline.render();
			arm.render();
		}
		body->render();
		reflection->render();
		eye.render();
	}
}

void Ball::update_position(Level lvl)
{
	physics(lvl.platform);
	update_reflection_x();

	outline.radius = body->radius + 4;
	reflection->radius = body->radius - body->radius / 4;

	reflection->center.y = body->center.y + sqrt(body->radius);
	outline.center.x = body->center.x;
	outline.center.y = body->center.y;

	arm.center.x = body->center.x;
	arm.center.y = body->center.y;
	armOutline.center.x = body->center.x;
	armOutline.center.y = body->center.y;

	(direction == LEFT) ?
		eye.center.x = body->center.x - body->radius / 2 :
		eye.center.x = body->center.x + body->radius / 2;
	eye.center.y = body->center.y + body->radius / 2;

	body->boundary_assignment();
}

void Ball::physics(Platform *plat)
{
	//This character is less affected by gravity
	velocity.y -= 3.0f * GLfloat(GRAVITY) / 4.0f;
	body->center.y += velocity.y;
	body->center.x += velocity.x;

	for (int i = 0; i < MAX_PLATFORM; i++)
	{
		if (body->boundary.bottom <= plat[i].body.boundary.top
			&& body->boundary.bottom > plat[i].body.boundary.bottom
			&& body->center.x >= plat[i].body.boundary.left
			&& body->center.x <= plat[i].body.boundary.right
			&& velocity.y <= 0.0)
		{
			on_ground = true;
			jumpCount = 0;
			velocity.y *= -0.25f;
			body->center.y = plat[i].body.boundary.top + body->height / 2;
			break;
		}
		else
			on_ground = false;
	}

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

	if (on_ground)
	{
		body->radius = body->width / 2;
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
	body->radius *= 0.9f;
}

void Ball::move(Direction dir)
{
	direction = dir;
	if (direction == LEFT)
		velocity.x = -5.0f;
	else 
		velocity.x = 5.0f;

	if (on_ground)
		velocity.y = 1.25f;
}

void Boxy::build(Assets assets)
{
	//Default Character Values
	JUMP_MAX = 2;
	jumpCount = 0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	on_ground = false;
	attk = false; 

	body = new Quad;
	reflection = new Quad;

	//Default Player Dimensions
	body->width = 100;
	body->height = body->width;
	body->radius = body->width / 2;

	//Arm
	arm.width = 100;
	arm.height = 25;
	arm.boundary_assignment();
	armOutline.width = 108;
	arm.height = 29;
	armOutline.color = assets.palette.black;

	//Player Boundaries
	body->boundary_assignment();
	body->center.x = 0;
	body->center.y = 0;

	eye.width = body->width/20 + 1;
	eye.height = eye.width;
	eye.radius = eye.width;

	outline.width = body->width + 8;
	outline.height = outline.width;
	outline.center.x = body->center.x;
	outline.center.y = body->center.y;

	reflection->width = body->width/1.5f;
	reflection->height = reflection->width;
	reflection->radius = reflection->width / 2;
	update_reflection_x();
	reflection->center.y = body->center.y + sqrt(body->radius)*2;

	//Color Assignment
	outline.color = assets.palette.black;
	eye.color = assets.palette.black;

	//Default Direction
	direction = LEFT;
}

Boxy::~Boxy()
{
	body = NULL;
	delete body;
	reflection = NULL;
	delete reflection;
}

void Boxy::render()
{
	if (stats.lifeState == ALIVE)
	{
		outline.render();
		if (attk)
		{
			armOutline.render();
			arm.render();
		}
		body->render();
		reflection->render();
		eye.render();
	}
}

void Boxy::update_position(Level lvl)
{
	physics(lvl.platform);

	body->boundary_assignment();

	eye.center.y = body->center.y + body->radius / 2;
	(direction == LEFT) ?
		eye.center.x = body->center.x - body->radius / 2 :
		eye.center.x = body->center.x + body->radius / 2;

	outline.center.x = body->center.x;
	outline.center.y = body->center.y;
	arm.center.x = body->center.x;
	arm.center.y = body->center.y;
	armOutline.center.x = body->center.x;
	armOutline.center.y = body->center.y;
	
	update_reflection_x();
	reflection->center.y = body->center.y + sqrt(body->radius) * 1.5f;
}

void Boxy::physics(Platform *plat)
{
	velocity.y -= GLfloat(GRAVITY);
	body->center.y += velocity.y;
	body->center.x += velocity.x;

	for (int i = 0; i < MAX_PLATFORM; i++)
	{
		plat[i].body.boundary_assignment();
		if (body->boundary.bottom <= plat[i].body.boundary.top
			&& body->boundary.bottom > plat[i].body.boundary.bottom
			&& body->boundary.right >= plat[i].body.boundary.left
			&& body->boundary.left <= plat[i].body.boundary.right
			&& velocity.y <= 0.0)
		{
			on_ground = true;
			jumpCount = 0;
			velocity.y *= -0.25f;
			body->center.y = plat[i].body.boundary.top + body->height / 2;
			break;
		}
		else
			on_ground = false;
	}

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

void Boxy::move(Direction dir)
{
	direction = dir;
	
	if (direction == LEFT)
		velocity.x = -6.0f;
	else 
		velocity.x = 6.0f;

	if (on_ground)
		velocity.y = 1.25f;
}

void Player::respawn()
{
	stats.lifeCount--;
	if (stats.lifeState != ELIMINATED && stats.lifeCount < 0)
	{
		stats.lifeState = ELIMINATED;
	}
	else
	{
		stats.lifeState = ALIVE;
		body->center.x = 0;
		body->center.y = 550;
		velocity.x = 0;
		velocity.y = -25.0f;
	}
}

void Player::death_handler()
{	
	if (body->boundary.right < -width_resolution * 2)
	{
		if (stats.lifeCount >= 0 && stats.lifeState != ELIMINATED && stats.initDeath == false)
		{
			stats.initDeath = true;
			stats.lifeState = DEAD;
			stats.deathTimer = glfwGetTime();
		}
	}
	else if (body->boundary.left > width_resolution * 2)
	{
		if (stats.lifeCount >= 0 && stats.lifeState != ELIMINATED && stats.initDeath == false)
		{
			stats.initDeath = true;
			stats.lifeState = DEAD;
			stats.deathTimer = glfwGetTime();
		}
	}
	else if (body->boundary.top < -height_resolution * 2.5)
	{
		if (stats.lifeCount >= 0 && stats.lifeState != ELIMINATED && stats.initDeath == false)
		{
			stats.initDeath = true;
			stats.lifeState = DEAD;
			stats.deathTimer = glfwGetTime();
		}
	}
	else if (body->boundary.bottom > height_resolution * 2.5)
	{
		if (stats.lifeCount >= 0 && stats.lifeState != ELIMINATED && stats.initDeath == false)
		{
			stats.initDeath = true;
			stats.lifeState = DEAD;
			stats.deathTimer = glfwGetTime();
		}
	}
	
	if (stats.lifeState == DEAD)
	{
		if (glfwGetTime() - stats.deathTimer >= 5.0)
		{
			stats.initDeath = false;
			respawn();
		}
	}
}

Attributes::Attributes()
{
	initDeath = false;
	health = 0.0f;
	lifeCount = 4;
	lifeState = ALIVE;
}
