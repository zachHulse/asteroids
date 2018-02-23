#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define BIG_ROCK_SPEED 1

#include "flyingObject.h"
#include <vector>
#include <iostream>
using namespace std;


class Rock : public FlyingObject
{
protected:
	int type;
	int lives;
public:
	Rock();
	int getType() { return type; }
	void setType(int type) { this->type = type; }
	int getLives() { return lives; }
	void setLives(int lives) { this->lives = lives; }
	virtual int hit() = 0;
	virtual void breakUp(vector <Rock*> &rocks) = 0;
};

class BigRock : public Rock
{
private:

public:
	BigRock();
    virtual void draw();
	int hit();
	void breakUp(vector <Rock*> &rocks);
};

class MediumRock : public Rock
{
private:
	
public:
	MediumRock(Point point, Velocity velocity);
	virtual void draw();
	int hit();
	void breakUp(vector <Rock*> &rocks);
};

class SmallRock : public Rock
{
private:

public:
	SmallRock(Point point, Velocity velocity);
	virtual void draw();
	int hit();
	void breakUp(vector <Rock*> &rocks);
};


#endif /* rocks_h */
