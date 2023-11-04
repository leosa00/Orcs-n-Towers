#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include <SFML/System/Vector2.hpp>

class Projectile
{
    private:
        double speed_;
        sf::Vector2f velocity_;
        sf::Vector2f position_;
        tower* owner_;
        std::string type_;
        int damage_;
    public:
        Projectile(/* args */);
        ~Projectile();
        double getSpeed() const;
        double getVelocity() const;
        std::string& getOwner() const;
        void dealDamage();

};

#endif