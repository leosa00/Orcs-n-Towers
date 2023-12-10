#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <string>
#include "path.hpp"
#include <queue>
#include "player.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 
#include <random>

enum class EnemyType {
    Ground,
    Flying,
    Split,
};

class Enemy :public sf::Sprite {
public:

    Enemy(int hp, int speed, EnemyType type, int money, std::queue<sf::Vector2f> waypoints)
         : hp_(hp), actualSpeed_(speed), speed_(speed), effectiveSpeed_(speed), type_(type), money_(money), waypoints_(waypoints), initialHp_(hp) {
        
        // Random y value of starting pos, gets set as a negative value
        // So enemies spawn outside window and then move in
        //int rand_y = std::rand() % 40; 

        //tries to avoid enemies being on top of eachother
        std::random_device rd;
        std::uniform_int_distribution range(1,40);
        int x = range(rd);
        int y = range(rd);
        setPosition(waypoints_.front() - sf::Vector2f(x,y));
        
        if (!waypoints_.empty()) {
            currentWaypoint_ = waypoints_.front();
        }
        setVelocity();
    }



    ~Enemy() {}
    
    void update(sf::Time time); //update the state of the monster in relation to the game
    
    sf::Vector2f getCenter();

    sf::Vector2f getLocation();

    bool dead();

    int hp();

    int initialHp();
    
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

    std::queue<sf::Vector2f> getWaypoints();

	void moveEnemy(sf::Vector2f movement);

    int getMoney() const;

    void updateHealthText(const sf::Font& font);

    const sf::Text& getHealthText() const;

private:
    int hp_;

    int initialHp_;
    
    bool dead_= false;

    float speed_;

    float actualSpeed_;

    float effectiveSpeed_;

    sf::Text healthText_;

    EnemyType type_;

    int poison_=0; //If poison is larger than 0 that means that the enemy is poisoned
    // the length of time that the enemy is poisoned for depends on how large the poison
    //value is as the number decreases incrimently until 0
    int slowed_=0; 
    //How much money the player recieves for killing the monster
    int money_;
    //waypoint based movement, the path class provides a queue of waypoints that take the enemies through the path to the end

    sf::Vector2f velocity_;

	std::queue<sf::Vector2f> waypoints_;

	sf::Vector2f currentWaypoint_;

    int direction_; //0 = down, 1= left, 2= right, 3 = up
    
};

#endif
