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

enum class CanDamage { 
    Ground,
    Flying,
    Both
};

class Tower : public sf::Sprite { 
public:                             
    Tower(sf::Vector2f position, const std::string& type = "Basic",  int baseCost = 100, float range = 100.0, float fireRate = 1.0,
          int damage = 10, int currentLvl = 1, int upgradeCost = 150, CanDamage damageType = CanDamage::Both, std::shared_ptr<Enemy> lockedEnemy = nullptr,
          sf::Clock fireTimer = sf::Clock(), bool maxLevelReached = false);
    /*Tower(sf::Vector2f position);*/
    // I think there is really no need for copy constructor or copy assignment operator
    const std::string& getType() const {return type_;}
    const sf::Vector2f getPosition() const {return position_;}
    const int getBaseCost() const {return baseCost_;}
    const float getFireRate() const {return fireRate_;}
    const CanDamage getDamageType() const {return damageType_;}
    const float getRange() const {return range_;}
    int getDamage() const {return damage_;}
    const CanDamage getDamageType() const {return damageType_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    bool isMaxLevelReached() const {return maxLevelReached_;};
    int getCurrentLvl() const {return currentLvl_;}
    const int getUpgradeCost() const {return upgradeCost_;}; 
    sf::Clock getFireTimer() {return fireTimer_;}
    // lockOn is redundant in current implementation
    void lockOn(std::shared_ptr<Enemy> enemy);
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    void resetFireTimer() {fireTimer_.restart();}
    // shoot() creates a projectile that flies towards lockedEnemy_
    // Changed it to virtual as different types of towers create different projectiles
    virtual Projectile& shoot(); 
    void upgradeTower(); // Will be defined in .cpp 
    // update() method is redundant in current implementation as I moved
    // tower logic update into game.cpp for now
    virtual void update(std::list<std::shared_ptr<Enemy>> &enemies);
private:
    virtual void draw();
    const std::string type_;
    const sf::Vector2f position_;
    const int baseCost_;
    const float range_;
    int damage_; 
    const float fireRate_; // Rate at which tower creates new projectiles; perhaps fireRate shouldn't be upgradable, instead stronger projectiles are created
    int currentLvl_;
    const CanDamage damageType_;
    const int upgradeCost_; 
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Clock fireTimer_;
    bool maxLevelReached_;
};
#endif //TOWER_H