#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "path.hpp"
#include <queue>
#include "player.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 

enum class EnemyType {
    Ground,
    Flying,
};

class Enemy :public sf::Sprite {
public:

    Enemy(int hp, int speed, EnemyType type, int gold, const path& path)
         : hp_(hp), speed_(speed), effectiveSpeed_(speed), type_(type), goldWorth_(gold), waypoints_(path.getWaypoints()) {
        if (!waypoints_.empty()) {
            currentWaypoint_ = waypoints_.front();
        }
        setVelocity();
    }



    ~Enemy() {}
    
    void update(sf::Time time); //update the state of the monster in relation to the game
    
    sf::Vector2f getCenter();

    sf::Vector2f getLocation();
    
    int hp();
    
    float speed();
    
    int poisonStatus();

    int slowedStatus();

    EnemyType type();
    
    void takeDamage(int damage); //decreases the hp_ variable and if hp reaches 0 than the enemy is automatically destroyed

    void kill();

    void applyPoison(int duration);

    void poisonDamage();

    void applySlowed(int duration);

    void slowedDamage();

    void setVelocity();

	bool isWaypointPassed(sf::Vector2f movement);

	void findNewWaypoint();

	void moveEnemy(sf::Vector2f movement);

private:
    int hp_;

    bool dead_= false;

    float speed_;

    float effectiveSpeed_;

    EnemyType type_;
         //has reference to player instance so money can be deposited to the player as well as the use of other player functions

    int poison_=0; //If poison is larger than 0 that means that the enemy is poisoned
    // the length of time that the enemy is poisoned for depends on how large the poison
    //value is as the number decreases incrimently until 0
    int slowed_=0; 
    //How much gold the player recieves for killing the monster
    int goldWorth_;
    //waypoint based movement, the path class provides a queue of waypoints that take the enemies through the path to the end
    sf::Vector2f velocity_;

	std::queue<sf::Vector2f> waypoints_;

	sf::Vector2f currentWaypoint_;

    int direction_; //0 = down, 1= left, 2= right, 3 = up
    
};

#endif
