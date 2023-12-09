#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include "tower.hpp"
#include "path.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "resource_container.hpp"
#include "player.hpp"
#include <memory> //for shared_ptr
#include "bulletTower.hpp"
#include "button.hpp"
#include "map.hpp"
#include "missileProjectile.hpp"
#include "menu.hpp"
#include <vector>
#include "levelManager.hpp"
#include "explosion.hpp"

class Menu;
// Class for running the game logic

class Game {
    
    friend class Tower;
    friend class BulletTower;
    friend class BombTower;
    friend class MissileTower;
    friend class FreezingTower;
    friend class BombProjectile;
    friend class BulletProjectile;
    friend class MissileProjectile;
    friend class Menu; 
    friend class LevelManager;

public:
    Map map;
    Game();
    void run();

    ~Game(){
        
        for(auto i : enemies_){
            //delete i;
        }
        enemies_.clear();

        for(auto i : projectiles_){
            delete i;
        }
        projectiles_.clear();

        for(auto i : towers_){
            delete i;
        }
        towers_.clear();

        delete activeTower_;
        delete alternativeMenu_;
        delete shop_;
    }
    path& getPath();
private:
    void processEvents();
    void update();
    void render();
    void addTower(const Tower& tower);
    void addEnemy(const Enemy& enemy);
    void addProjectile(const Projectile& projectile);
    void createPath(); //this will create the path that the enemies will traverse (this should also be rendered visually in the game)
    void checkTowers();
    void testEnemy();
    void testEnemySplit(sf::Vector2f position, std::queue<sf::Vector2f> waypoints);
    //adding a function to return the elapsed time
    sf::Time getTime() const;
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
    std::list<Tower*> towers_;
    //std::list<Enemy> enemies_;

    /* Changed these to unque ptr, as looping over the abstract types directly 
        is not possible, at least according to my understanding
        */
    std::list<std::shared_ptr<Enemy>> enemies_;
    std::list<Projectile*> projectiles_;
    std::list<Explosion*> explosions_;
    path path_;
    std::list<Button> buttons_; // Stores clickable buttons
    bool dragged_; // Indicates if a tower is currently being dragged into place
    bool paused_; // Is the game paused?
    bool isGameOver_=false; //is the game over because the player has died to an enemy
    bool isGameFinished_ = false; //completed game
    sf::Font font_; // Stores text font
    sf::Text gameOverText;
    sf::Text gameFinishedText;
    sf::Sprite castle_sprite_;

    Menu* shop_; // Shop on left side
    Menu* alternativeMenu_; // stores menu for upgrading, beginning game, and advancing to next level
    Tower* activeTower_; // Pointer to tower that is being upgraded

    ResourceContainer<Textures::TowerID, sf::Texture> tower_textures_;
    ResourceContainer<Textures::EnemyID, sf::Texture> enemy_textures_;
    ResourceContainer<Textures::ProjectileID, sf::Texture> projectile_textures_;
    ResourceContainer<Textures::Various, sf::Texture> various_textures_;

    Player player_; 

    LevelManager levelManager_;
};

#endif