/***********************************************************************
* Header File:
*    FlyingObject : A class for flying things.
* Author:
*    Zachary Hulse
* Summary:
*    Rocks, Bullets, and the ship had enough in common that I could create
* a parent class to hold a point, a velocity, and if its alive. As well 
* as kill, and advance functions to kill it when its been hit and move it.
************************************************************************/
#ifndef flyingObject_h
#define flyingObject_h

#include "velocity.h"
#include "point.h"
#include "uiDraw.h"
class FlyingObject
{
protected:
	Point point;
	Velocity velocity;
	bool alive;
	int rotation;
	int radius;

public:
	FlyingObject();
	Point getPoint() const { return point; }
	Velocity getVelocity() const { return velocity; }
	void setPoint(Point point) { this->point = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }
	bool isAlive() { return alive; } // inline getters
	void setAlive(bool alive) { this->alive = alive; }
	void kill() { alive = false; }
	void advance();
	void wrapObject(Point topLeft, Point bottomRight, float borderAmount);
	virtual void draw() = 0;
	
};



#endif /* flyingObject_h */
