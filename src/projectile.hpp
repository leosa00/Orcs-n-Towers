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
        /* Pavel to Ellen: should we change speed_ to float instead? Apparently 
         * sf::Vector2f can not be multiplied/divided by double (now that I think of it 
         * that's probably what f stands for).
         * I don't think we need shootDirection_ either because it is basically 
         * velocity divided by speed (you can refer to shoot() method implementation
         * inside tower.cpp)
         * Also I suggest we use std::shared_ptr<Enemy> for targetEnemy_ (I added my 
         * reasoning in favour for that approach into game.hpp; but we should perhaps discuss on
         * this matter during our next weekly meeting.)
         * */
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
        void update(float dt);
};
#endif