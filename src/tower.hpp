#ifndef TOWER_H
#define TOWER_H
// #define TOWER_MAX_LVL 5 // Assume maximum lvl of tower is 5
// I think we should reduce max level of tower to lvl 2.
#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include "enemy.hpp"
#include <memory>
// enum class CanDamage is needed for defining logic on which EnemyType can be 
// locked and damaged by a specific type of tower. 

enum class CanDamage { 
    Ground,
    Flying,
    Both
};

class Tower : public sf::Sprite { //perhaps can also inherit from sf::Sprite?
public:                             //which might be preferred as I believe Sprite is more light-weight.
    Tower(sf::Vector2f position);
    // I think there is really no need for copy constructor or copy assignment operator
    const std::string& getType() const {return type_;}
    const sf::Vector2f getPosition() const {return position_;}
    const int getBaseCost() const {return baseCost_;}
    const float getFireRate() const {return fireRate_;}
    const CanDamage getDamageType() const {return damageType_;}
    const float getRange() const {return range_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    int getCurrentLvl() const {return currentLvl_;}
    int getUpgradeCost() const; // Will be defined in .cpp
    sf::Clock getFireTimer() {return fireTimer_;}
    // lockOn is redundant in current implementation
    void lockOn(std::shared_ptr<Enemy> enemy); //redundant in current implementation
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    void resetFireTimer() {fireTimer_.restart();}
    // shoot() creates a projectile that flies towards lockedEnemy_
    // it should be made virtual as we will define different towers in future
    // that create different kind of projectiles.
    virtual Projectile shoot(); 
    void upgradeTower(); // Will be defined in .cpp 
    // update() method is redundant in current implementation as I moved
    // tower logic update into game.cpp for now
    void update();
private:
    void draw();
    const std::string type_;
    const sf::Vector2f position_;
    const int baseCost_;
    const float range_;
    int damage_; 
    const float fireRate_; // Rate at which tower creates new projectiles; perhaps fireRate shouldn't be upgradable, instead stronger projectiles are created
    int currentLvl_;
    const CanDamage damageType_;
    int* upgradeCost_; // Index 0 stores upgrade cost from lvl 1 to lvl 2, index 1 upgrade cost from lvl 2 to lvl 3 etc.
    // Enemy* lockedEnemy_;
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Clock fireTimer_;
};
#endif //TOWER_H