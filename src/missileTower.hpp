#ifndef MISSILE_TOWER
#define MISSILE_TOWER
#include "tower.hpp"
#include "missileProjectile.hpp"
/**
 * @class MissileTower
 * @brief Represents the Missile Tower class.
 * 
 * The Missile Tower is a specialized tower that shoots missile projectiles. It is derived from
 * the base Tower class and inherits common tower functionalities.
 */
class MissileTower : public Tower {
public:
    /** 
     * @brief Constructs a MissileTower object at the specified position.
     * 
     * @param position The initial position of the MissileTower.
    */
    MissileTower(sf::Vector2f);
    /**
     * @brief Override of the base class method to produce a MissileProjectile.
     * 
     * @return MissileProjectile* A pointer to the created MissileProjectile object.
     */    
    MissileProjectile* shoot() override;
};
#endif