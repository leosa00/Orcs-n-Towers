#ifndef TOWER_H
#define TOWER_H
// EDIT: I think we should reduce max level of tower to lvl 2.
#define TOWER_MAX_LVL 2
#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include "enemy.hpp"
#include <memory>

// enum class CanDamage is needed for implementing enemy-locking logic 
// (i.e., which EnemyType can be locked and damaged by a specific type of tower). 
class Projectile;

/* enum class CanDamage { 
    Ground,
    Flying,
    Both
}; */

class Tower : public sf::Sprite { 
public:                                
    Tower(sf::Vector2f position, const std::string& type,  int baseCost, float range, sf::Time fireRate,
          int damage, int currentLvl, int upgradeCost, std::shared_ptr<Enemy> lockedEnemy,
          bool maxLevelReached);
    const std::string& getType() const {return type_;}
    const int getBaseCost() const {return baseCost_;}
    sf::Time getFireRate() const {return fireRate_;}
    const float getRange() const {return range_;}
    int getDamage() const {return damage_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    bool isMaxLevelReached() const {return maxLevelReached_;};
    int getCurrentLvl() const {return currentLvl_;}
    const int getUpgradeCost() const {return upgradeCost_;}; 
    sf::Time getFireTimer() {return fireTimer_;}
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    /**
     * shoot() method is pure virtual as different types of towers produce different types 
     * of projectiles (or no projectiles at all as is the case with Poison and Freezing Towers).
     * @return Projectile* 
     */
    virtual Projectile* shoot() = 0; 
    /**
     * upgradeTower() method is virtual as upgrade logic is same for all types of towers
     * except Freezing Tower
     * 
     */
    virtual void upgradeTower();
    /**
     * @brief update() method is virtual as some types of towers use base update()
     * 
     * @param enemies is the list of Enemy shared pointers needed for setting lockedEnemy_
     * @param time is delta time from Game object needed for updating @see fireTimer_
     */
    virtual void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time);
    void updateFireTimer(sf::Time &dt);
    void setLevel(int level) {currentLvl_ = level;}
    void setMaxLevelFlag() {maxLevelReached_ = true;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    void resetFireTimer() {fireTimer_ = sf::Time::Zero;}
private:
    /**
     * @brief Private members of abstract tower class
     * 
     * @param type_ is a string representing type of the tower
     * @param baseCost_ is the base cost for the type of tower
     * @param range_ is the enemy locking range of the tower
     * @param damage_ is passed as a parameter to projectile constructor
     * @param currentLvl_ is current level of the tower, initially set 1 and can be upgraded to level 2
     * @param upgradeCost_ is set at 1.5 * base cost of tower for all types of towers
     * @param lockedEnemy_ is the locked enemy of the tower; initially set to nullptr
     * \param fireTimer_ is incremented with delta time from Game object
     * and compared to @param fireRate_ to check if tower is ready to shoot
     * @param maxLevelReached_ is the flag to check if whether tower is already at max level.
     * @
     * @
     */
    const std::string type_;
    const int baseCost_;
    const float range_;
    int damage_; 
    int currentLvl_;
    const int upgradeCost_; 
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Time fireTimer_;
    sf::Time fireRate_;
    bool maxLevelReached_;
};
#endif //TOWER_H