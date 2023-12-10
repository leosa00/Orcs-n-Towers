#ifndef POISON_TOWER
#define POISON_TOWER
#include "tower.hpp"
#include "enemy.hpp"
#include <list>
#include <memory>

class PoisonTower : public Tower{
public:
    PoisonTower(sf::Vector2f);
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    Projectile* shoot() override;
private:
    std::list<std::shared_ptr<Enemy>> lockedEnemies_;
};
#endif 