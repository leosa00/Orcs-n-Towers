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

enum class CanDamage { 
    Ground,
    Flying,
    Both
};

class Tower : public sf::Sprite { 
public:                             
    Tower(sf::Vector2f position, const std::string& type,  int baseCost, float range, sf::Time fireRate,
          int damage, int currentLvl, int upgradeCost, CanDamage damageType, std::shared_ptr<Enemy> lockedEnemy,
          bool maxLevelReached);
    /*Tower(sf::Vector2f position);*/
    // I think there is really no need for copy constructor or copy assignment operator
    const std::string& getType() const {return type_;}
    //const sf::Vector2f getPosition() const {return position_;}
    const int getBaseCost() const {return baseCost_;}
    sf::Time getFireRate() const {return fireRate_;}
    const CanDamage getDamageType() const {return damageType_;}
    const float getRange() const {return range_;}
    int getDamage() const {return damage_;}
//    const CanDamage getDamageType() const {return damageType_;}
    std::shared_ptr<Enemy> getLockedEnemy() const {return lockedEnemy_;}
    void setLockedEnemy(std::shared_ptr<Enemy> enemy) {lockedEnemy_ = enemy;}
    bool isMaxLevelReached() const {return maxLevelReached_;};
    int getCurrentLvl() const {return currentLvl_;}
    const int getUpgradeCost() const {return upgradeCost_;}; 
    sf::Time getFireTimer() {return fireTimer_;}
    bool enemyWithinRange(std::shared_ptr<Enemy> enemy);
    void resetFireTimer() {fireTimer_ = sf::Time::Zero;}
    // shoot() creates a projectile that flies towards lockedEnemy_
    // Changed it to pure virtual 
    virtual Projectile* shoot() = 0; 
    virtual void upgradeTower(); // Will be defined in .cpp 
    /* update() method is declared as virtual. Some derived
       classes will use base update() and other will use override*/
    virtual void update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time);
    void updateFireTimer(sf::Time &dt);
    //This is what I add to support for the map class
    bool isActive();//Whether the Tower is active or not
    bool HUDactive = false;//Temporary variable hold the state of the Tower
    void unactiveHUD();//Function to deactivate Tower (when sell)
    void activateHUD();//Function to activate Tower (when buy)
    sf::Vector2f getSize();//Get the height and width of the Tower we want to build
    virtual void build(); //build function which change the temporary variable builded to tru
    bool builded = false; //Temporary variable define whether the tower is built or not.
    void setLevel(int level) {currentLvl_ = level;}
    void setMaxLevelFlag() {maxLevelReached_ = true;}
private:
//    virtual void draw();
    const std::string type_;
    //const sf::Vector2f position_;
    const int baseCost_;
    const float range_;
    int damage_; 
    int currentLvl_;
    const CanDamage damageType_;
    const int upgradeCost_; 
    std::shared_ptr<Enemy> lockedEnemy_;
    sf::Time fireTimer_;
    sf::Time fireRate_;
    bool maxLevelReached_;
};
#endif //TOWER_H