###############################################################
# Program:
#     Project 13, Asteroids
#     Brother Walker, CS165
# Author:
#     Zachary Hulse
# Summary:
#     This is the game asteroids with a few of my own extras. The game starts out 
#     with five large asteroids and the ship that the user can control. The ship
#     is controled with the four arrow keys and the space bar. The game ends when 
#     either the ship is hit by an asteroid or the ship destroyes all the asteroid
#     by firing at them with the space bar. 

# Above and Beyond
#     For extra I implemented a reverse thruster that turns the flame on the ship
#     yellow moves the ship backward when the down arrow is pressed. If down, left,
#     and right arrows are all pressed at the same time ship will hyper jump and 
#     appear at another point on the screen. I also slowed the thrusters a little
#     I felt that the ship moved too fast to control easily before. 
#
#     I also added score to my game. You get one point for shooting a rock and extra
#     points for destroying medium and large rocks. Those rocks also take more shots
#     to destroy. Five shots for a large rock and three shots for a medium. The score
#     is displayed in the top left of the screen. 

#     If the ship is destroyed "Game Over" is displayed in the middle of the screen
#     and if all the asteroids are destroyed "You Win!" is displayed.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
