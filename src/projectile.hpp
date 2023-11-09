#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Projectile : public sf::Transformable
{
    private:
        double speed_;
        sf::Vector2f velocity_;
        sf::Vector2f position_;
        Tower* owner_;
        std::string type_;
        int damage_;

    public:
        Projectile(double speed, sf::Vector2f velocity, sf::Vector2f position, Tower* owner, std::string type, int damage) : speed_(speed), velocity_(velocity), position_(position), owner_(owner), type_(type), damage_(damage){}
        ~Projectile() {}
        double getSpeed() const;
        sf::Vector2f getVelocity() const;
        Tower* getOwner() const;
        std::string& getType() const;
        void dealDamage(Enemy& enemy);

        /**
         * calculates distance from owner tower
         * deletes the projectile if it hasn't hit an enemy and is just travelling further from tower
         * so that projectiles don't just float about when they've gone out of range
         * probably needs to be called every frame after the projectile has been shot
        */
        void distToTower(); 
};
#endif