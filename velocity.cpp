#include "velocity.h"


// Put your velocity methods here
/***************************************************************
* VELOCITY :: DEFALT CONSTRUCTOR
*
***************************************************************/
Velocity::Velocity()
{
	setDx(0.0);
	setDy(0.0);
	setAngle(60.0);
	setMagnitude(0.0);
}

/***************************************************************
* VELOCITY :: NON-DEFALT CONSTRUCTOR
*
***************************************************************/
Velocity::Velocity(float dX, float dY)
{
	setDx(dX);
	setDy(dY);
}