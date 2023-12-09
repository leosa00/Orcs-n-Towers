#ifndef POISON_TOWER
#define POISON_TOWER
#include "tower.hpp"
#include "enemy.hpp"
#include <list>
#include <memory>

class PoisonTower : public Tower{
public:
    PoisonTower(sf::Vector2f);
    void update(std::list<std::shared_ptr<Enemy>> &enemies) override;
    Projectile* shoot() override;
    std::shared_ptr<Tower> getClassObject(); //reduntant, delete this in all the tower when tidying code. 
private:
    std::list<std::shared_ptr<Enemy>> lockedEnemies_;
};
#endif 