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

/**
 * 
*/
class Player : public sf::Sprite
{
    private:
        int hp_;
        int wallet_;
        std::string name_;
        int score_;
        sf::Vector2f position_; //of castle
        int level_;

    public:
        Player(std::string name = "player") 
        // position_ cannot be initialized as NULL, because it is of type sf::Vector2f
            :name_(name), hp_(500), wallet_(1000), score_(0), position_(sf::Vector2f(0, 0)), level_(0){}

        ~Player() {}

        /**
         * @brief returns how much money the player has
        */
        int getWallet() const;

        /**
         * @brief returns how many health points the player has
        */
        int getHP() const;

        /**
         * @brief returns the name of the player
        */
        std::string getName() const;

        /**
         * @brief returns the current level of the player
        */
        int getLevel() const;

        /**
         * @brief increases the players level by one
        */
        void levelUp();

        /**
         * @brief adds money to the players wallet
         * @param amount is how much money is to be added
        */
        void addMoney(int amount);

        /**
         * @brief removes money from the players wallet
         * @param cost is how much money is to be removed
        */
        void removeMoney(int cost);

        /**
         * @brief removes health pointe from the player
         * @param amount is how much hp is to be removed
        */
        void removeHP(int amount);

        /**
         * @brief adds points to the players score
         * @param amount is how many points is to be added
        */
        void addToScore(int amount);

        //void reachedCastle (std::shared_ptr<Enemy>& enemy); //checks if an enemy has reached the castle or should game do it?
        //std::list<std::shared_ptr<Enemy>> increaseLevel(ResourceContainer<Textures::EnemyID, sf::Texture>& enemytextures, path& path);
        //void buyTower(int cost, Textures::TowerID towerID);
        //void sellTower(Tower& tower);
        //void upgradeTower(Tower& tower);

        /**
         * updates the position coordinates of castle
         * should be called whenever map changes
         * and probably during first load of a map, since player is initiated before map is loaded?
        */
        //void updateCastlePosition(sf::Vector2f position);
};

#endif