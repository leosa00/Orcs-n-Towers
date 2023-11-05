#ifndef TOWER_H
#define TOWER_H
#define TOWER_MAX_LVL 5 // Assume maximum lvl of tower is 5
#include <string>
#include <array>
#include <SFML/System/Vector2.hpp>
class Tower {
public:
    Tower(sf::Vector2f position);
    // I think there is really no need for copy constructor or copy assignment operator
    const std::string& getType() const {return type_;}
    const sf::Vector2f getPosition() const {return position_;}
    const int getBaseCost() const {return baseCost_;}
    const float getFireRate() const {return fireRate_;}
    const float getRange() const {return range_;}
    int getCurrentLvl() const {return currentLvl_;}
    int getUpgradeCost() const; // Will be defined in .cpp
    void lockOn(const Enemy& enemy); 
    //maybe lockOn method can be integrated within shootAt, but I think it is necessary
    //if we want Tower to keep on shooting same enemy as long as it is within its range
    void shoot(); //creates a projectile that flies towards lockedEnemy_
    void upgradeTower(); // Will be defined in .cpp
private:
    const std::string type_;
    const sf::Vector2f position_;
    const int baseCost_;
    const float range_;
    const float fireRate_; // Rate at which tower creates new projectiles; perhaps fireRate shouldn't be upgradable, instead stronger projectiles are created
    int currentLvl_;
    int* upgradeCost_; // Index 0 stores upgrade cost from lvl 1 to lvl 2, index 1 upgrade cost from lvl 2 to lvl 3 etc.
    Enemy& lockedEnemy_;
};
#endif //TOWER_H