#ifndef MISSILE_PROJECTILE
#define MISSILE_PROJECTILE

#include "projectile.hpp"

class MissileProjectile : public Projectile
{
private:
    std::shared_ptr<Enemy>& targetEnemy_;

public:
    MissileProjectile(sf::Vector2f position, int damage, std::shared_ptr<Enemy>& targetEnemy) 
    : Projectile(sf::Vector2f(0,0), position, damage, 70.0, "missile", 70), targetEnemy_(targetEnemy) {}

    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy);
    void update(Game& game);
    Textures::ProjectileID textureType(){ return Textures::Missile; }
};


#endif