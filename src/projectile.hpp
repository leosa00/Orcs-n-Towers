#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Projectile : public sf::Transformable
{
    private:
        double speed_;
        sf::Vector2f velocity_;
        sf::Vector2f position_;
        Tower& owner_;
        std::string type_;
        int damage_;
        sf::Vector2f shootDirection_;
        Enemy& targetEnemy_;

    public:
        //derived classes should have default speed, velocity, type, damage
        //position, owner, lockedEnemy comes from tower
        Projectile(double speed, sf::Vector2f velocity, sf::Vector2f position, Tower& owner, std::string type, int damage, Enemy& targetEnemy) 
        : speed_(speed), velocity_(velocity), position_(position), owner_(owner), type_(type), damage_(damage), targetEnemy_(targetEnemy){}
        ~Projectile() {}
        
        double getSpeed() const;
        //sf::Vector2f getVelocity() const; shouldn't be needed
        Tower* getOwner() const;
        std::string& getType() const;
        int getDamage() const;

        /**
         * calculates distance from owner tower
         * deletes the projectile if it hasn't hit an enemy and is just travelling further from tower
         * so that projectiles don't just float about when they've gone out of range
         * probably needs to be called every frame after the projectile has been shot
        */
        bool distToTower(); 

        /**
         * called in update
         * checks if projectile has collided with the enemy that the tower is shooting at
         * deals damage to enemy
         * deletes the projectile
        */
        bool collision();

        /**
         * calculates the direction for the projectile
         * Adds the projectile specifc velocity to the direction vector
         * should be called sometime during construction
        */
        void shootDirection();

        sf::Vector2f getDirection();

        /**
         * moves the projectile if it hasn't collided / gone out of range
         * needs delta time somehow, now passed as a parameter
         * towers should call update on their projectiles?
        */
<<<<<<< HEAD
       /* Pavel: maybe better implementation would be if we add private 
        * member target_ to projectile class which would be same as tower class' 
        * lockedEnemy_. This way projectile doesn't have to be bounded to 
        * any particular tower and we would also save on function calls.  */
        void update(float dt, Enemy& enemy);
=======
        void update(float dt);
>>>>>>> 72659479aa62dec791b15f4b1bc3c6db3b8609a9
};
#endif