# Orcs n Towers
## Overview

Orcs n Towers is a tower defence game set in a fantasy setting, where orcs and other such monsters try to reach and destroy the player's castle, the player must defend against the monsters by placing different towers with specific roles. The player will have a set number of hitpoints that are depleted when enemies reach the castle.When all hitpoints are lost the player loses.

The monsters traverse a path, along which the player can place their towers. Once a monster is inside a towers range, depending on the towers it will either create a projectile that matches the towers type or apply a slowing effect on the monster.

The player can buy as many Towers as they can afford throughout the game, as well as upgrade them to increase the damage the tower will cause the monster.

## Instructions

Custom levels and paths can be created in levels.csv and paths.csv respectively, read formatting instructions carefully.

## How to compile the program

To compile the game from the command line:

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
    - Projectile class and it's derived classes
    - LevelManager class
    - Reading paths from file
    - Player class

Leo:
    - Enemy class

Tuan:
    - Path

