#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "path.hpp"
#include <queue>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 

class Enemy :public sf::Drawable {
public:
    Enemy(int hp, int speed, std::string type, int goldWorth);

    ~Enemy() {}

    void move(); //use the speed_ variable to advance the position of the enemy, keep it void for now
    
    void update(); //update the state of the monster in relation to the game

    bool atBase(); //checks if the enemy has reached the base

    sf::Vector2f getPosition(); //returns the position of the enemy as a Vector2f position
    
    void setTexture(sf::Texture * texture);

    void draw(sf::RenderTarget & target) const;

    sf::Vector2f getLocation();
    
    int hp();
    
    int speed();
    
    int poisonStatus();

    int slowedStatus();

    std::string type();
    
    void takeDamage(int damage); //decreases the hp_ variable and if hp reaches 0 than the enemy is automatically destroyed

    void kill();

    void applyPoison(int duration);

    void poisonDamage();

    void applySlowed(int duration);

    void slowedDamage();

    void setVelocity();

	bool isWaypointPassed(sf::Vector2f movement);

	void findNewWaypoint();

	void move(sf::Vector2f movement);

private:
    int hp_;

    bool dead_= false;

    float speed_;

    std::string type_;

    int poison_; //If poison is larger than 0 that means that the enemy is poisoned
    // the length of time that the enemy is poisoned for depends on how large the poison
    //value is as the number decreases incrimently until 0
    int slowed_; 
    //How much gold the player recieves for killing the monster
    int goldWorth_;
    //waypoint based movement, the path class provides a queue of waypoints that take the enemies through the path to the end
    sf::Vector2f velocity_;

	std::queue<sf::Vector2f> waypoints_;

	sf::Vector2f *currentWaypoint_;

    int direction_; //0 = down, 1= left, 2= right, 3 = up
    //sprite
    sf::Sprite sprite_;

    sf::Vector2u spriteSize_;
    
};

#endif