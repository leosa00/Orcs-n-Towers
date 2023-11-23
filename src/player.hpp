#ifndef PLAYER
#define PLAYER

#include <string>
#include <list>
#include "enemy.hpp"
#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Player //: public sf::Transformable
{
    private:
        int hp_;
        int wallet_;
        std::string name_;
        int score_;
        sf::Vector2f position_; //of castle
        std::vector<Tower*> towers_; //towers the player has bought / owns, pointers or references?

    public:
        Player(std::string name = "player") 
            :name_(name), hp_(500), wallet_(500), score_(0), position_(NULL){}

        ~Player() {
            for(auto& i : towers_) {
                delete i;
            }
            towers_.clear();
        }
        int getWallet() const;
        int getHP() const;
        std::string& getName() const;
        void addMoney(int amount);
        void removeMoney(int cost);
        void removeHP(int amount);
        void addToScore(int amount);
        void reachedCastle (std::shared_ptr<Enemy> enemy); //checks if an enemy has reached the castle or should game do it?
        void buyTower(int cost, Textures::TowerID towerID);
        void sellTower(Tower& tower);
        void upgradeTower(Tower& tower);

        /**
         * updates the position coordinates of castle
         * should be called whenever map changes
         * and probably during first load of a map, since player is initiated before map is loaded?
        */
        void updateCastlePosition(sf::Vector2f position);
};

#endif