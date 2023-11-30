#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H
#include "tower.hpp"
#include "bombProjectile.hpp"
class BombTower : public Tower {
public:
    BombTower(sf::Vector2f);
    void update(std::list<std::shared_ptr<Enemy>> &enemies) override;
    BombProjectile& shoot() override;
    std::shared_ptr<Tower> getClassObject() override;
private:
//    void draw() override;
// Draw method is inherited from sf::Sprite so I have commented this out for now
// If we want to include some animation stuff I'm not sure where it would be best to do
};
#endif //BOMB_TOWER_H