#ifndef FREEZING_TOWER
#define FREEZING_TOWER
#include "tower.hpp"
#include "enemy.hpp"
#include <list>
#include <memory>

class FreezingTower : public Tower{
public:
    FreezingTower(sf::Vector2f);
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    Projectile* shoot() override;
    void upgradeTower() override;
private:
    std::list<std::shared_ptr<Enemy>> lockedEnemies_;
    float slowCoefficient_ = 0.1;

};
#endif //FREEZING_TOWER