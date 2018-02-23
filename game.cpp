/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
	score = 0;
	startingRocks = 5;
	for (int i = 0; i < startingRocks; i++)
	{
		Rock* newRock = new BigRock();
		rocks.push_back(newRock);
	}
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
	for (vector<Rock*>::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		delete *it;
		*it = NULL;
	}
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceBullets();
   advanceShip();
   advanceRocks();
   handleCollisions();
   cleanUpZombies();
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	// draw the rocks if their alive
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->draw();
		}
	}
	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}
	if (ship.isAlive()) // draw the ship if it is alive
	{
		ship.draw();
		ship.setThrust(false);
		ship.setReverse(false);
	}
	else // if the ship is dead the game is over
	{
		char text[] = "Game Over";
	    drawText(Point(-20, 0), text);
	}

	// Put the score on the screen
	Point scoreLocation;
	scoreLocation.setX(topLeft.getX() + 5);
	scoreLocation.setY(topLeft.getY() - 5);
	drawNumber(scoreLocation, score);

	if (!rocks.size()) // if all the rocks are gone
	{
		char text[] = "You Win!";
		drawText(Point(-20, 0), text);
	}
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
	if (ui.isSpace() && ship.isAlive()) // want also make sure the ship is alive
	{                                   // before firing 
		Bullet newBullet;
		newBullet.fire(ship.getPoint(), ship.getAngle());
		Velocity bVelocity = newBullet.getVelocity();
		Velocity sVelocity = ship.getVelocity();
		float x = bVelocity.getDx() + sVelocity.getDx();
		float y = bVelocity.getDy() + sVelocity.getDy();
		newBullet.setVelocity(Velocity(x, y));

		bullets.push_back(newBullet);
	}

	if (ui.isRight())
	{
		ship.turnRight();
	}

	if (ui.isLeft())
	{
		ship.turnLeft();
	}

	if (ui.isUp()) 
	{
		ship.applyThrust();
		ship.setThrust(true);
	}
	if (ui.isDown()) 
	{
		ship.applyReverse();
		ship.setReverse(true);
		
	}
	if (ui.isDown() && ui.isRight() && ui.isLeft()) // hyper jump
	{
		ship.setPoint(Point(random(-200, 200), random(-200, 200)));
	}
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between asteroids and bullets and between 
* the ship and asteroids.
**************************************************************************/
void Game::handleCollisions()
{
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
			// this bullet is alive, see if its too close

			// check if the bird is at this point (in case it was hit)

		for (int j = 0; j < rocks.size(); j++)
		{
			if(rocks[j]->isAlive() && bullets[i].isAlive())
			{
				if (getClosestDistance(*rocks[j], bullets[i]) < rocks[j]->getRadius())
				{
					//we have a hit!
					// hit the asteroid
					int points = rocks[j]->hit();
					score += points;
                    // the bullet is dead as well
					bullets[i].kill();
					
					if (!rocks[j]->isAlive()) // if the rock is dead break it up!
					{
						rocks[j]->breakUp(rocks);
					}
				}
			}
		}	
	} 
	// loop through all the rocks and see if they are about to hit the ship
	for (vector<Rock*>::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		Rock * asteroid = *it;
		if (getClosestDistance(*asteroid, ship) < asteroid->getRadius() + ship.getRadius())
		{
			ship.kill(); // sad day :(
		}
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
			int age = bullets[i].getAge() + 1;
			bullets[i].setAge(age);

			if (age >= 40) // bullets only live for 40 frames
				bullets[i].kill();
			//once a it goes out the screen bring it back on the other side
			if (!isOnScreen(bullets[i].getPoint()))
			{
				bullets[i].wrapObject(topLeft, bottomRight, OFF_SCREEN_BORDER_AMOUNT);
			}
		}
	}
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/***************************************
* GAME :: ADVANCE Rocks
* Go through each rock* and advance it.
***************************************/
void Game::advanceRocks()
{
	vector<Rock*>::iterator it = rocks.begin();

	while (it != rocks.end())
	{
		Rock* pRock = *it;
		if (pRock->isAlive())
		{
			pRock->advance();
			//once a it goes out the screen bring it back on the other side
			if (!isOnScreen(pRock->getPoint()))
			{
				pRock->wrapObject(topLeft, bottomRight, OFF_SCREEN_BORDER_AMOUNT);
			}
			else
				it++;
		}
	}
}

/***************************************
* GAME :: ADVANCE Ship
* Move the ship!
***************************************/
void Game::advanceShip()
{
	ship.advance();
	//once a it goes out the screen bring it back on the other side
	if (!isOnScreen(ship.getPoint()))
	{
		ship.wrapObject(topLeft, bottomRight, OFF_SCREEN_BORDER_AMOUNT);
	}
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate bird)
* As it is removing dead things it will some times but smaller rocks in the 
* place of larger dead rocks
**************************************************************************/
void Game::cleanUpZombies()
{
	
	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

	// Look for dead rocks
	vector<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock* pRock = *rockIt;

		if (!pRock->isAlive())
		{
			delete pRock;
			pRock = NULL;
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++; // advance
		}
	}
}





