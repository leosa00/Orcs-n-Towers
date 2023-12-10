#ifndef BULLET_TOWER_H
#define BULLET_TOWER_H
#include "tower.hpp"
#include "bulletProjectile.hpp"
/**
 * @class Bullet Tower
 * @brief Represents the Bullet Tower class.
 * 
 * The Bullet Tower is a specialized tower that shoots bullet projectiles. It is derived from
 * the base Tower class and inherits common tower functionalities.
 */
class BulletTower : public Tower {
public:
    /** 
     * @brief Constructs a BulletTower object at the specified position.
     * 
     * @param position The initial position of the BulletTower.
    */
    BulletTower(sf::Vector2f position);
    /**
     * @brief Override of the base class method to produce a BulletProjectile.
     * 
     * @return BulletProjectile* A pointer to the created BulletProjectile object.
     */
    BulletProjectile* shoot() override;
};
#endif //BULLET_TOWER