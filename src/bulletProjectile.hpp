#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "projectile.hpp"

class BulletProjectile : public Projectile
{
private:
    std::shared_ptr<Enemy> targetEnemy_;
public:
    BulletProjectile(sf::Vector2f shootDirection, sf::Vector2f position, Tower& owner, std::shared_ptr<Enemy> targetEnemy) 
    : Projectile(shootDirection, position, owner, targetEnemy, 10.0, "bullet", 20, 10), targetEnemy_(targetEnemy) {}
                                                            //   ^              ^   ^ tbd
    bool hasHitEnemy(std::shared_ptr<Enemy> enemy);
    void update();
};


#endif