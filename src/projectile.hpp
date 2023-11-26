#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

class Game;

// Removed inheritance of sf::Transformable. 
// I checked that sf::Sprite inherits both Drawable and Transformable -Otto
class Projectile : public sf::Sprite
{
    private:
        float speed_;
        std::string type_;
        int damage_;
        sf::Vector2f position_; // of tower that created
        int maxDistance_;
        sf::Vector2f shootDirection_;
        bool isDestroyed_;

        //derived classes keep track of their target enemy/ies

    public:
        //derived classes should have default speed, type, damage
        
        //Pavel: I assumed you want normalized shootdirection when passing this
        //argument to Projectile constructor inside Tower::shoot().
        //I also commented out my alternative implementation for Projectile constructor below:
        //I think it should be preferred as it makes it more clear which initializers are default
        //and which are passed as an argument from Tower::shoot() method. 

        //abstract class, don't call this constructor
        Projectile(sf::Vector2f shootDirection, sf::Vector2f position, int damage, float speed, std::string type, int maxDistance) 
        : shootDirection_(shootDirection), position_(position), damage_(damage), speed_(speed), type_(type), maxDistance_(maxDistance),
        isDestroyed_(false){}

        // shootdirection, position, damage comes from tower
        // speed, type, maxDistance come from derived classes 
        // shootDirection needs to be normalised vector
        
        virtual ~Projectile() {}
        
        float getSpeed() const;
        std::string& getType() const;
        int getDamage() const;
        sf::Vector2f getShootDir() const;
        sf::Vector2f getVelocity() const;
        void destroy();
        bool isDestroyed();

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
        virtual bool hasHitEnemy(Enemy& enemy) = 0;

        /**
         * moves the projectile if it hasn't collided / gone out of range
         * needs delta time somehow, now passed as a parameter
         * towers should call update on their projectiles?
         * purely virtual
        */
       virtual void update(Game&) = 0;
};
#endif

