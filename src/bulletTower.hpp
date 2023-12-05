#ifndef BULLET_TOWER_H
#define BULLET_TOWER_H
#include "tower.hpp"
#include "bulletProjectile.hpp"
class BulletTower : public Tower {
public:
    BulletTower(sf::Vector2f);
    /*update() method for BulletTower uses update() from base class,
      hence I have commented it out*/
    //void update(std::list<std::shared_ptr<Enemy>> &enemies) override;
    BulletProjectile& shoot() override;
    std::shared_ptr<Tower> getClassObject() override;
private:
    //void draw() override;
};
#endif //BULLET_TOWER_H