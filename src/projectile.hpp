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
        int getDamage() const;
        //void dealDamage(Enemy& enemy); shouldn't be needed

        /**
         * calculates distance from owner tower
         * deletes the projectile if it hasn't hit an enemy and is just travelling further from tower
         * so that projectiles don't just float about when they've gone out of range
         * probably needs to be called every frame after the projectile has been shot
        */
        void distToTower(); 

        /**
         * should probalby be called by tower
         * checks if projectile has collided with the enemy that the tower is shooting at
         * deals damage to enemy
         * deletes the projectile
        */
        void collision(Enemy& enemy);

        /**
         * calculates the direction for the projectile
         * Adds the projectile specifc velocity to the direction vector
         * takes the enemy that the tower has locked on as parameter
         * needs to be multiplied by deltaTime (projectile.move(shootdirection()*deltaTime))
        */
        sf::Vector2f shootDirection(Enemy& enemy);
};
#endif