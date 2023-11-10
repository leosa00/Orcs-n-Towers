#ifndef PLAYER
#define PLAYER

#include <string>
#include "enemy.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Player : public sf::Transformable
{
    private:
        int hp_;
        int wallet_;
        std::string name_;
        int score_;
        sf::Vector2f position_; //of castle
    public:
        Player(std::string name, sf::Vector2f position) 
            : hp_(500), wallet_(500), name_(name), //TODO: determine amounts for hp / wallet
            score_(0), position_(position){}

        ~Player() {}
        int getWallet() const;
        int getHP() const;
        std::string& getName() const;
        void addMoney(int amount);
        void removeMoney(int cost);
        void removeHP(int amount); //actually probably not needed
        void addToScore(int amount);
        void reachedCastle (Enemy& enemy); //checks if an enemy has reached the castle
};

#endif