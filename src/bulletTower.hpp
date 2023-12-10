#ifndef BULLET_TOWER_H
#define BULLET_TOWER_H
#include "tower.hpp"
#include "bulletProjectile.hpp"
class BulletTower : public Tower {
public:
    BulletTower(sf::Vector2f);
    BulletProjectile* shoot() override;
};
#endif //BULLET_TOWER