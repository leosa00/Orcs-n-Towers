#ifndef BOMB_PROJECTILE
#define BOMB_PROJECTILE

#include "projectile.hpp"
#include <list>

class BombProjectile : public Projectile
{
private:
    int blastRange_;
public:
    BombProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage) // <- tbd
    : Projectile(shootDirection, position, damage, 5.0, "bomb", 50), blastRange_(7) {}
                                        //  ^            ^  ^  tbd
       
    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy) override;
    void update(Game& game);
    Textures::ProjectileID textureType(){ return Textures::Bomb; } 
};


#endif