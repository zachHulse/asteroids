/***********************************************************************
* Header File:
*    Bullet : Class for projectiles shot from the ship
* Author:
*    Zachary Hulse
* Summary:
*    Bullet will be a member of the flying object class with additional
* functions for firing and drawing a bullet.
************************************************************************/
#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "uiDraw.h"
#include <cmath>
using namespace std;

// Put your Bullet class here
class Bullet : public FlyingObject
{
private:
	int age;

public:
	Bullet();
	int getAge() { return age; }
	void setAge(int age) { this->age = age; }
	void fire(Point point, float angle);
	void draw();
};



#endif /* bullet_h */
