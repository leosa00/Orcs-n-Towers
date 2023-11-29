#ifndef PLAYER
#define PLAYER

#include <string>
#include <list>
#include "enemy.hpp"
#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include "resource_container.hpp"

class Tower;
class Enemy;

// Changed this as well to inherit sprite at least temporarily, because
// otherwise getGlobalBounds() function does not exist, which is needed in
// reachedCastle()
class Player : public sf::Sprite
{
    private:
        int hp_;
        int wallet_;
        std::string name_;
        int score_;
        sf::Vector2f position_; //of castle

    public:
        Player(std::string name = "player") 
        // position_ cannot be initialized as NULL, because it is of type sf::Vector2f
            :name_(name), hp_(500), wallet_(500), score_(0), position_(sf::Vector2f(0, 0)){}

        ~Player() {}
        int getWallet() const;
        int getHP() const;
        std::string getName() const;
        void addMoney(int amount);
        void removeMoney(int cost);
        void removeHP(int amount);
        void addToScore(int amount);
        void reachedCastle (std::shared_ptr<Enemy>& enemy); //checks if an enemy has reached the castle or should game do it?
        //void buyTower(int cost, Textures::TowerID towerID);
        //void sellTower(Tower& tower);
        //void upgradeTower(Tower& tower);

        /**
         * updates the position coordinates of castle
         * should be called whenever map changes
         * and probably during first load of a map, since player is initiated before map is loaded?
        */
        void updateCastlePosition(sf::Vector2f position);
};

#endif