#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.3

#define ANGLE_MAX 360
#define ANGLE_MIN 0
#define ANGLE_START 90

#include "velocity.h"
#include "point.h"
#include "uiDraw.h"
#include "flyingObject.h"

// Put your Ship class here
class Ship : public FlyingObject
{
private:
	float angle;
	bool thrust;
	bool reverse;

public:
	Ship();
	bool isThrust() { return thrust; }
	void setThrust(bool thrust) { this->thrust = thrust; }
	bool isReverse() { return reverse; }
	void setReverse(bool reverse) { this->reverse = reverse; }
	float getAngle() { return angle; }
	void turnLeft();
	void turnRight();
	void applyThrust();
	void applyReverse();
	void draw();
		
};

#endif /* ship_h */
