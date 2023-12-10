#ifndef BOMB_TOWER_H
#define BOMB_TOWER_H
#include "tower.hpp"
#include "bombProjectile.hpp"
/**
 * @class BombTower
 * @brief Represents the Bomb Tower class.
 * 
 * The Bomb Tower is a specialized tower that shoots bomb projectiles. It is derived from
 * the base Tower class and inherits common tower functionalities. Bomb tower can only lock
 * enemies of ground type. Bomb projectiles can, however, damage enemies of any type within 
 * explosion range of a bomb projectile (explosion rate is dictated solely by bomb projectile objects).
 * 
 */
class BombTower : public Tower {
public:
    /** 
     * @brief Constructs a BombTower object at the specified position.
     * 
     * @param position The initial position of the BombTower.
    */
    BombTower(sf::Vector2f);
    /**
     * @brief Override of the base class method. 
     * 
     * @param enemies is passed from calling Game::update method
     * @param time is passed from calling Game::update method and is used to update fireTimer_
     */
    void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) override;
    /**
     * @brief Override of the base class method to produce a BombProjectile.
     * 
     * @return BulletProjectile* A pointer to the created BombProjectile object.
     */
    BombProjectile* shoot() override;
};
#endif //BOMB_TOWER