/*********************************************************************
* File: rocks.cpp
* Description: Contains the implementaiton of the rock class
*  methods.
*
*********************************************************************/
#include "rocks.h"
#include "uiDraw.h"
#include <cmath>
#include <vector>

/*********************************************
* ROCK :: CONSTRUCTOR
*********************************************/
Rock::Rock()
{
	setPoint(Point(random(-200, 200), random(-200, 200)));
	Point point = getPoint();
}

/*********************************************
* BIGROCK :: CONSTRUCTOR
*********************************************/
BigRock::BigRock()
{
	rotation = BIG_ROCK_SPIN;
	float dx = BIG_ROCK_SPEED * (-cos(3.14159265358979323846 / 180.0 * random(0, 360)));
	float dy = BIG_ROCK_SPEED * (sin(3.14159265358979323846 / 180.0 * random(0,360)));
    velocity.setDx(dx);
	velocity.setDy(dy);

	type = 1;
	lives = 5;
	radius = 16;
}

/*********************************************
* BIGROCK :: DRAW
* Draws the large asteroid on screen;
*********************************************/
void BigRock::draw()
{
	 rotation += BIG_ROCK_SPIN;
	 drawLargeAsteroid(getPoint(), rotation);
}

/*********************************************
* BIGROCK :: HIT
* Removes rock lives and returns points.
* If the rock is killed extra point are returned.
*********************************************/
int BigRock::hit()
{
	int bonus = 0;
	lives--;
	if (!lives)
	{
		bonus = 4;
		kill();
	}
	return 1 + bonus;
}

/*********************************************
* BIGROCK :: BREAKUP
* When a large rock is destroyed this method is called
* to create one medium and two small rocks.
*********************************************/
void BigRock::breakUp(vector <Rock*> &rocks)
{	
	Point point(this->point.getX(), this->point.getY());
	Velocity velocity(this->velocity.getDx(), this->velocity.getDy());
	velocity.setDy(velocity.getDy() + 1.0);
	Rock *newRock = new MediumRock(point, velocity);
	rocks.push_back(newRock);

	velocity.setDy(velocity.getDy() - 2.0);
	newRock = new MediumRock(point, velocity);
	rocks.push_back(newRock);

	velocity.setDy(velocity.getDy() + 1.0);
	velocity.setDx(velocity.getDx() + 2.0);
	newRock = new SmallRock(point, velocity);
	rocks.push_back(newRock);
}

/*********************************************
* MEDIUMROCK :: CONSTRUCTOR
*********************************************/
MediumRock::MediumRock(Point point,Velocity velocity)
{
	rotation = MEDIUM_ROCK_SPIN;
	type = 2;
	lives = 3;
	radius = 8;
	this->point = point;
	this->velocity = velocity;
	alive = true;
	
}

/*********************************************
* MEDIUMROCK :: DRAW
* Draws the medium asteroid;
*********************************************/
void MediumRock::draw()
{
	rotation += MEDIUM_ROCK_SPIN;
	drawMediumAsteroid(getPoint(), rotation);
}

/*********************************************
* MEDIUMROCK :: HIT
* Removes rock lives and returns points.
* If the rock is killed extra point are returned.
*********************************************/
int MediumRock::hit()
{
	int bonus = 0;
	lives--;
	if (!lives)
	{
		bonus = 2;
		kill();
	}
	return 1 + bonus;
}

/*********************************************
* MEDIUMROCK :: BREAKUP
* When a medium rock is destroyed this method 
* is called to create two small rocks.
*********************************************/
void MediumRock::breakUp(vector <Rock*> &rocks)
{
	Point point(this->point.getX(), this->point.getY());
	Velocity velocity(this->velocity.getDx(), this->velocity.getDy());
	velocity.setDx(velocity.getDx() + 3.0);
	Rock *newRock = new SmallRock(point, velocity);
	rocks.push_back(newRock);

	velocity.setDx(velocity.getDx() - 6.0);
	newRock = new SmallRock(point, velocity);
	rocks.push_back(newRock);
}

/*********************************************
* SMALLROCK :: CONSTRUCTOR
*********************************************/
SmallRock::SmallRock(Point point, Velocity velocity)
{
	rotation = SMALL_ROCK_SPIN;
	type = 3;
	lives = 1;
	radius = 4;
	this->point = point;
	this->velocity = velocity;
	alive = true;
}

/*********************************************
* SMALLROCK :: DRAW
* Draws the small rock on screen;
*********************************************/
void SmallRock::draw()
{
	rotation += MEDIUM_ROCK_SPIN;
	drawSmallAsteroid(getPoint(), rotation);
}

/*********************************************
* SMALLROCK :: HIT
* Removes rock lives and returns points if .
*********************************************/
int SmallRock::hit()
{
	int bonus = 0;
	lives--;
	if (!lives)
	{
		bonus = 1;
		kill();
	}
	return 1 + bonus;
}

/*********************************************
* SMALLROCK :: BREAKUP
* No new rocks are created when a small rock is destroyed
* but this method overwrites to virtual breakUp method in ROCK
*********************************************/
void SmallRock::breakUp(vector <Rock*> &rocks)
{
	alive = false;
}