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
        sf::Vector2f position_;
    public:
        Player();
        ~Player();
        int getWallet() const;
        int getHP() const;
        std::string& getName() const;
        void addMoney();
        void removeMoney();
        void removeHP();

};

#endif