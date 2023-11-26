#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "projectile.hpp"

class BulletProjectile : public Projectile
{
private:
    std::shared_ptr<Enemy> targetEnemy_;
public:
    BulletProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage, std::shared_ptr<Enemy> targetEnemy) 
    : Projectile(shootDirection, position, damage, 10.0, "bullet", 20), targetEnemy_(targetEnemy) {}
    
    //Projectile(shootDirection, position, damage, 10.0, "bullet", 20, 10)   
    // Sorry, I'm not understanding what the two numbers at the end of this constructor call are
    // Projectile() constructor only accepts one number after type, which is maxDistance   
 
 
    bool hasHitEnemy(std::shared_ptr<Enemy> enemy);
    void update(Game& game);
};


#endif