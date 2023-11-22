#ifndef BOMB_PROJECTILE
#define BOMB_PROJECTILE

#include "projectile.hpp"
#include <list>

class BombProjectile : public Projectile
{
private:
    int blastRange_;
    std::list<std::shared_ptr<Enemy>> targetEnemies_; //enemies within owner towers range
public:
    BombProjectile(sf::Vector2f shootDirection, sf::Vector2f position, Tower& owner, std::list<std::shared_ptr<Enemy>> targetEnemies, int blastRange = 7) 
    : Projectile(shootDirection, position, owner, 5.0, "bomb", 50, 5), blastRange_(blastRange), targetEnemies_(targetEnemies) {}    // ^ tbd
                                                // ^            ^  ^  tbd
       
    bool hasHitEnemy(std::shared_ptr<Enemy> enemy);
    void update();
};


#endif