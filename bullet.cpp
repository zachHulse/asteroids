/*************************************************************
* File: bullet.cpp
* Author: Zachary Hulse
*
* Description: Contains the function bodies for the bullet class.
*************************************************************/
#include "bullet.h"


// Put your bullet methods here

/***************************************************************
* Bullet :: DEFALT CONSTRUCTOR
*
***************************************************************/
Bullet::Bullet()
{

	setAlive(true);
	setAge(0);
}


/*********************************************
* Bullet :: fire()
* Takes in a point and an angle and gives the bullet a velocity.
*********************************************/
void Bullet::fire(Point point, float angle)
{
	this->point = point;
	float dx = BULLET_SPEED * (-cos(3.14159265358979323846 / 180.0 * (-angle + 90)));
	float dy = BULLET_SPEED * (sin(3.14159265358979323846 / 180.0 * (-angle + 90)));
	velocity.setDx(dx);
	velocity.setDy(dy);


}
/*********************************************
* Bullet :: draw()
* Call the uiDraw function to draw our bullet
*********************************************/
void Bullet::draw()
{
	drawDot(getPoint());
}