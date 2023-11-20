#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "tower.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

// Class for running the game logic

class Game{
public:
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window_;
    std::list<Tower> towers_;
    std::list<Enemy> enemies_;
    std::list<Projectile> projectiles_;


};

#endif