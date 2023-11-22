#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

class Projectile : public sf::Transformable, sf::Sprite
{
    private:
        float speed_;
        Tower& owner_;
        std::string type_;
        int damage_;
        sf::Vector2f position_;
        int maxDistance_;
        sf::Vector2f shootDirection_;

        //derived classes keep track of their target enemy/ies

    public:
        //derived classes should have default speed, type, damage
        //shootdirection, position, owner, comes from tower
        Projectile(sf::Vector2f shootDirection, sf::Vector2f position, Tower& owner, float speed = 1.0, std::string type = "default", int damage = 0, int maxDistance = 0) 
        : shootDirection_(shootDirection), position_(position), owner_(owner), speed_(speed), type_(type), damage_(damage), maxDistance_(maxDistance){}
       
        ~Projectile() {}
        
        float getSpeed() const;
        Tower* getOwner() const;
        std::string& getType() const;
        int getDamage() const;
        sf::Vector2f getShootDir() const;

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
        bool hasHitEnemy(Enemy& enemy) = 0;

        /**
         * moves the projectile if it hasn't collided / gone out of range
         * needs delta time somehow, now passed as a parameter
         * towers should call update on their projectiles?
         * purely virtual
        */
        void update(float dt) = 0;
};
#endif