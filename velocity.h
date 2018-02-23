#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float dX;
	float dY;
	float angle;
	float magnitude;
public:
	Velocity();
	Velocity(float dX, float dY);
	float getDx() const { return dX; }
	float getDy() const { return dY; }
	float getAngle() const { return angle; }
	float getMagnitude() const { return magnitude; }
	void setDx(float dX) { this->dX = dX; }
	void setDy(float dY) { this->dY = dY; }
	void setAngle(float angle) { this->angle = angle; }
	void setMagnitude(float magnitude) { this->magnitude = magnitude; }
};


#endif /* velocity_h */
