#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "tower.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "resource_container.hpp"
#include "player.hpp"
#include <memory> //for shared_ptr

// Class for running the game logic

class Game {
    
    friend class Tower;
    friend class BulletTower;
    friend class BombTower;
    friend class BombProjectile;
    friend class BulletProjectile;

public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void addTower(const Tower& tower);
    void addEnemy(const Enemy& enemy);
    void addProjectile(const Projectile& projectile);
    void checkButtons();
    void drag();
    //adding a function to return the elapsed time
    sf::Time getTime();
    //I am adding a clock and time functionality that will need to be used for enemy movement and updating and other game logic
    sf::Clock clock_;
    sf::Time time_;
    sf::RenderWindow window_;
    /* Pavel: should we change enemies_ to be 
    * std::list<std::shared_ptr<Enemy>> enemies_ instead and 
    * initialize it with enemies using 
    * enemies_.push_back(std::make_shared<TYPE_OF_ENEMY>(args))?
    * This way enemy would get destroyed automatically when
    * it is no longer locked by any tower AND it has reached 0 hp 
    * (it gets removed from the list at this point) AND no projectile
    * flies towards it (we need to add shared_ptr<Enemy> member to projectile class). 
    * There might be some error in my logic though....
    */
    std::list<Tower> towers_;
    //std::list<Enemy> enemies_;
    std::list<std::shared_ptr<Enemy>> enemies_;
    std::list<Projectile> projectiles_;
    
    std::list<sf::RectangleShape> buttons_; // Stores clickable buttons
    bool dragged_; // Indicates if a tower is currently being dragged into place
    
    ResourceContainer<Textures::TowerID, sf::Texture> tower_textures_;
    
    Player player_; 
};

#endif