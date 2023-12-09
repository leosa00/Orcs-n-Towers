#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H
#include "tower.hpp"
#include "bombProjectile.hpp"
class BombTower : public Tower {
public:
    BombTower(sf::Vector2f);
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    BombProjectile* shoot() override;
};
#endif //BOMB_TOWER