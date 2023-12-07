#ifndef MISSILE_PROJECTILE
#define MISSILE_PROJECTILE

#include "projectile.hpp"

/**
 * @brief a projectile that targets (follows) a specific enemy
*/
class MissileProjectile : public Projectile
{
private:
    std::shared_ptr<Enemy> targetEnemy_;

public:
    /**
     * Missile target does not need a pre-calculated directional vector,
     * as its direction needs to be re-calculated everytime before it moves,
     * hence the shootDirection is (0,0)
     * @param targetEnemy is the enemy that the missile is targeting (following)
    */
    MissileProjectile(sf::Vector2f position, int damage, std::shared_ptr<Enemy> targetEnemy) 
    : Projectile(sf::Vector2f(0,0), position, damage, 70.0, "missile", 70), targetEnemy_(targetEnemy) {}

    /**
     * Checks whether the missile has hit its target or not.
     * If the missile's and enemy's sprites intersect, there has been a hit
     * and the missile causes damage to the enemy and returns true.
     * @param enemy is a reference to an Enemy object
    */
    bool hasHitEnemy(std::shared_ptr<Enemy>& enemy);

    /**
     * Firstly makes sure that the target enemy still exists, if it doesn't the missile is destroyed.
     * If the enemy still exists it checks whether or not is has hit it, 
     * if there's been a hit, the missile is destroyed.
     * If it has not hit the enemy, it re-calculates its directional vector, 
     * based on its and the target enemy's current positions, and moves towards the target.
     * @param game is a reference to the running game instance
    */
    void update(Game& game);
    Textures::ProjectileID textureType(){ return Textures::Missile; }
};


#endif