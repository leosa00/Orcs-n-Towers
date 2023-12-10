# Orcs n Towers
## Overview

Orcs n Towers is a tower defence game set in a fantasy setting, where orcs and other such monsters try to reach and destroy the player's castle, the player must defend against the monsters by placing different towers with specific roles. The player will have a set number of hitpoints that are depleted when enemies reach the castle. When all hitpoints are lost the player loses.

The monsters traverse a path, along which the player can place their towers. There is three different paths of which one is chosen at random for the duration of the game. Once a monster is inside a towers range, depending on the towers it will either create a projectile that matches the towers type, or apply a slowing or poision effect on the monster.

The player can buy as many Towers as they can afford throughout the game, as well as upgrade them to increase the damage the tower will cause the monster.

The game has 5 different levels of increasing difficulty, by introducing more monsters in amount and type at quicker intervals. The game is won once the player has defeated all levels. 

## Instructions

To place towers on map, drag and drop them to an appropriate place. Towers cannot be built on the path.
Custom levels and paths can be created in levels.csv and paths.csv respectively, read formatting instructions carefully.

## How to compile the program

To compile the game, as taken from git, on the command line:

    1. create an empty directory where the build files will be written
    2. change directory to that directory
    3. run: cmake ..
    4. run: make
    5. run: ./TD

SFML (minimum version 2.5) is required.

## Testing

## Work log

##### Division of work / main responisbilities:

Pavel:
    - Tower class and it's derived classes
    - Game class

Otto:
    - Graphics
    - Menu class

Ellen:
    - Projectile class and it's derived classes (bulletProjectile, bombProjectile, missileProjectile)
    - LevelManager class
    - Reading paths from file
    - Player class

Leo:
    - Enemy class

Tuan:
    - Path

##### Weekly breakdown

**Week 1**
Pavel Filippov:
    - Initialised implementation of base tower class.

Otto Litkey: 
    - Initialised implementation of class(es) resposible for graphics.

Ellen Molin:
    - Initialised implementation of Player and base Projectile classes.

Leo Saied-Ahmad:
    - Intialised implementation of base Enemy class.

Tuan Vu:
    - Initialised implementation of Map class.

**Week 2**
Pavel Filippov:
    - Continued implementation of base tower class.

Otto Litkey: 
    - Initialised game class and ResourceContainer template class.

Ellen Molin:
    - Continued implementation of Player and base Projectile classes.

Leo Saied-Ahmad:
    - Continued implementation of base Enemy class.

Tuan Vu:
    - Continued implementation of Map class.

**Week 3**
Pavel Filippov:
    - Created update function in game class, as well as for towers.

Otto Litkey: 
    - Tested rendering, beginnings of dragging and dropping functionality for creating towers.

Ellen Molin:
    - Improved projectile class and added functionality.

Leo Saied-Ahmad:
    - Improved enemy class functionality, specifically kill and death functions.

Tuan Vu:
    - Finished implementing loading map from file, worked on drawing and being able to sell towers

**Week 4**
Pavel Filippov:
    - Created derived classes bulletTower and bombTower from tower. Moved tower update logic to it's own function

Otto Litkey: 
    - Continued testing rendering, finished drag and drop functionality for creating towers, and added way to pause game.

Ellen Molin:
    - Created derived classes bullet and bomb from projectile. Improved projectile methods to better work with derived classes.

Leo Saied-Ahmad:
    - Created path class for directing enemy movement, and updated enemy's move function to make use of it.

Tuan Vu:
    - Continued working on map class to create a path.

**Week 5**
Pavel Filippov:
    - Implemented freezing effect tower, poision effect tower and missile tower.

Otto Litkey: 
    - Implemented explosions class to visualise bombs' explosions. Worked on graphics: created textures, show tower ranges. Improved logic behind user interactions with game objects.

Ellen Molin:
    - Implemented a levelManager that handles creating and managing levels. Created a missile projectile that follows enemy.

Leo Saied-Ahmad:
    - Implemented slowing effect on enemies and refiened enemy movement. Worked on graphics: show players state, end screen when player loses.

Tuan Vu:
    - Implemented functionality so that towers can't be built on the path