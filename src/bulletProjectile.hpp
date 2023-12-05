#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "projectile.hpp"

class BulletProjectile : public Projectile
{
public:
    BulletProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage) 
    : Projectile(shootDirection, position, damage, 300, "bullet", 70) {}

    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy);
    void update(Game& game);
    Textures::ProjectileID textureType(){ return Textures::Bullet; }
    float rotationAngle() const; //this one is used to calculate rotation angle of a projectile.
};


#endif