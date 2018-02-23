/*********************************************************************
* File: ship.cpp
* Description: Contains the implementaiton of the ship class
*  methods.
*
*********************************************************************/
#include "ship.h"
#include <cmath>

/*********************************************
* Ship :: CONSTRUCTOR
*********************************************/
Ship::Ship()
{
	velocity = Velocity();
	angle = ANGLE_START;
	radius = 10;
    setAlive(true);
	setThrust(false);
	setReverse(false);
	
}

/*********************************************
* SHIP :: TURN LEFT
* Will apply left thrust at 0.1 pixles per frame
* using one unit of fuel; 
*********************************************/
void Ship :: turnLeft()
{
		angle += ROTATE_AMOUNT;
}

/*********************************************
* SHIP :: TURN RIGHT
* Will apply right thrust at 0.1 pixles per frame
* using one units of fuel;
*********************************************/
void Ship :: turnRight()
{
		angle -= ROTATE_AMOUNT;	
}

/*********************************************
* SHIP :: APPLY THRUST 
* Will apply thrust at 0.5 pixles per frame
*********************************************/
void Ship :: applyThrust()
{
	float dx = THRUST_AMOUNT * (-cos(3.14159265358979323846 / 180.0 * (-angle + 90)));
	float dy = THRUST_AMOUNT * (sin(3.14159265358979323846 / 180.0 * (- angle + 90)));
	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);
}

/*********************************************
* SHIP :: APPLY REVERSE 
* Will apply reverse at 0.5 pixles per frame
*********************************************/
void Ship:: applyReverse()
{
	float dx = -THRUST_AMOUNT * (-cos(3.14159265358979323846 / 180.0 * (-angle + 90)));
	float dy = -THRUST_AMOUNT * (sin(3.14159265358979323846 / 180.0 * (-angle + 90)));
	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);
}

/*********************************************
* SHIP :: DRAW
* Draws the ship on screen;
*********************************************/
void Ship::draw()
{
	drawShip(getPoint(), angle, isThrust(), isReverse());
}