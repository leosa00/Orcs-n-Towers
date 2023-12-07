#ifndef BOMB_PROJECTILE
#define BOMB_PROJECTILE

#include "projectile.hpp"
#include <list>

/**
 * @brief a projectile that causes damage to multiple enemies
*/
class BombProjectile : public Projectile
{
private:
    int blastRange_;
public:

    /**
     * @param blastRange_ the blast radius of the bomb
    */
    BombProjectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage) // <- tbd
    : Projectile(shootDirection, position, damage, 60.0, "bomb", 50), blastRange_(1000) {}
                                        //  ^            ^  ^  tbd
    
    /**
     * Calculates the distance between the bomb and an enemy
     * If the enemy is within the blast range, cause damage to it because it has been hit
    */
    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy) override;

    /**
     * If the bomb has reached it's maximum distance, 
     * it goes through all the enemies in the game to see if it hits any, and once done with that, is destroyed
     * If the bomb hasn't yet reached it's maximum distance, it is moved
    */
    void update(Game& game);

    /**
     * @brief returns the texture ID of the type this derived class uses
    */
    Textures::ProjectileID textureType(){ return Textures::Bomb; } 
};


#endif