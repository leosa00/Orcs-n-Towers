#ifndef PLAYER
#define PLAYER

#include <string>
#include <SFML/System/Vector2.hpp>

class Player
{
    private:
        int hp_;
        int wallet_;
        std::string name_;
        int score_;
        sf::Vector2f position_; //of castle
    public:
        Player(std::string name, sf::Vector2f position) : hp_(), wallet_(), name_(name), score_(0), position_(position){}
        ~Player() {}
        int getWallet() const;
        int getHP() const;
        std::string& getName() const;
        void addMoney(int amount);
        void removeMoney(int cost);
        void removeHP(int amount);
        void addToScore(int amount);

};

#endif