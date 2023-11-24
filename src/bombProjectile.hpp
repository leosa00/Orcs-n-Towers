#ifndef BOMB_PROJECTILE
#define BOMB_PROJECTILE

#include "projectile.hpp"
#include <list>

class BombProjectile : public Projectile
{
private:
    int blastRange_;
public:
    BombProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int blastRange = 7) // <- tbd
    : Projectile(shootDirection, position, 5.0, "bomb", 50, 5), blastRange_(blastRange) {} 
                                        //  ^            ^  ^  tbd
       
    bool hasHitEnemy(std::shared_ptr<Enemy> enemy);
    void update(float dt, std::list<std::shared_ptr<Enemy>>& Enemies);
};


#endif