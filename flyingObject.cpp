/*************************************************************
* File: flyingObject.cpp
* Author: Zachary Hulse
*
* Description: Contains the function bodies for the flyingObject class.
*************************************************************/
#include "flyingObject.h"

/*********************************************
* FlyingObject :: CONSTRUCTOR
*********************************************/
FlyingObject::FlyingObject()
{
	point = Point(0, 0);
	velocity = Velocity();

	setAlive(true);

}

/*********************************************
* FlyingObject :: ADVANCE
* Moving is objects is done here;
*********************************************/
void FlyingObject::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}

/*********************************************
* FlyingObject :: WRAPOBJECT
* If our FlyingObject goes off screen this function will make
* it appear on the other side
*********************************************/
void FlyingObject::wrapObject(Point topLeft, Point bottomRight, float borderAmount)
{
	float x = point.getX();
	float y = point.getY();
	if (x <= topLeft.getX() - borderAmount)
		point.setX(bottomRight.getX());
	else if (x >= bottomRight.getX() + borderAmount)
		point.setX(topLeft.getX());
	else if (y <= bottomRight.getY() - borderAmount)
		point.setY(topLeft.getY());
	else if (y >= topLeft.getY() + borderAmount)
		point.setY(bottomRight.getY());
	setPoint(point);
}