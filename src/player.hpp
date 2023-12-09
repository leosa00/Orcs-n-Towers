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
        int level_;

    public:
        Player() : hp_(500), wallet_(1000), level_(0){}

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
};

#endif