#ifndef MISSILE_TOWER
#define MISSILE_TOWER
#include "tower.hpp"
#include "missileProjectile.hpp"
class MissileTower : public Tower {
public:
    MissileTower(sf::Vector2f);
    MissileProjectile* shoot() override;
};
#endif