#ifndef TOWER_H
#define TOWER_H
#define TOWER_MAX_LVL 5 // Assume maximum lvl of tower is 5
#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "projectile.hpp"
#include "enemy.hpp"
#include <memory>

class Tower : public sf::Drawable { //perhaps can also inherit from sf::Sprite?
public:                             //which might be preferred as I believe Sprite is more light-weight.
    Tower(sf::Vector2f position);
    // I think there is really no need for copy constructor or copy assignment operator
    const std::string& getType() const {return type_;}
    const sf::Vector2f getPosition() const {return position_;}
    const int getBaseCost() const {return baseCost_;}
    const float getFireRate() const {return fireRate_;}
    const float getRange() const {return range_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    int getCurrentLvl() const {return currentLvl_;}
    int getUpgradeCost() const; // Will be defined in .cpp
    sf::Clock getFireTimer() {return fireTimer_;}
    void lockOn(std::shared_ptr<Enemy> enemy); 
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    void resetFireTimer() {fireTimer_.restart();}
    //maybe lockOn method can be integrated within shootAt, but I think it is necessary
    //if we want Tower to keep on shooting same enemy as long as it is within its range
    Projectile shoot(); //creates a projectile that flies towards lockedEnemy_
    void upgradeTower(); // Will be defined in .cpp
    void update(); // method for updating tower logic
private:
    const std::string type_;
    const sf::Vector2f position_;
    const int baseCost_;
    const float range_;
    const float fireRate_; // Rate at which tower creates new projectiles; perhaps fireRate shouldn't be upgradable, instead stronger projectiles are created
    int currentLvl_;
    int* upgradeCost_; // Index 0 stores upgrade cost from lvl 1 to lvl 2, index 1 upgrade cost from lvl 2 to lvl 3 etc.
    // Enemy* lockedEnemy_;
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Clock fireTimer_;
};
#endif //TOWER_H