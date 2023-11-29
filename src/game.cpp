#include "game.hpp"
#include "bombTower.hpp"
#include <memory>
#include "path.hpp"
#include "button.hpp"

// initialize game object, mainly create window...
Game::Game() : window_(sf::VideoMode(1000, 800), "Orcs n Towers") {
    // Set dragging flag
    dragged_ = false;
    paused_ = false;

    // Create tower texture container, load texture    
    tower_textures_ = ResourceContainer<Textures::TowerID, sf::Texture>();
    tower_textures_.load(Textures::Tower1, "/home/tweety/cpp-course/tower-defense/textures/tower1.png");
    tower_textures_.load(Textures::Tower2, "/home/tweety/cpp-course/tower-defense/textures/tower2.png");

    enemy_textures_ = ResourceContainer<Textures::EnemyID, sf::Texture>();
    enemy_textures_.load(Textures::Enemy1, "/home/tweety/cpp-course/tower-defense/textures/goblin_test.png");

    // Create Buttons
    buttons_.push_back(Button(Actions::Tower1, tower_textures_.get(Textures::Tower1), sf::Vector2f(920, 40)));
    buttons_.push_back(Button(Actions::Tower2, tower_textures_.get(Textures::Tower2), sf::Vector2f(920, 100)));
    // This needs a texture or something
    buttons_.push_back(Button(Actions::Pause, enemy_textures_.get(Textures::Enemy1), sf::Vector2f(900, 760)));


    testEnemy();


    player_ = Player(); 
    player_.addMoney(500);
};



// Run main game loop
void Game::run() {
    while(window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

// Process inputs, handle closing window
void Game::processEvents(){
    sf::Event event;
    while(window_.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        
        case sf::Event::MouseButtonPressed:
            // If statement checks that nothing is being dragged currently
            // if MouseButtonPressed event only happens when button is initially pressed
            // this if statement is unnesessary
            if (!dragged_) {
                checkButtons(); // Check if some button has been pressed
                break;
            } 

        default:
            break;
        }
    }
}

// Call functions necessary for iterating over all objects and updating their states
void Game::update() {
    time_=clock_.restart();
    // If a tower is being dragged, update it's position
    if (dragged_) {
        drag();
    }

    // If the game is paused stop updating
    if (paused_) {
        return;
    }

    // Pavel: following order of updates is perhaps ok
    
    for (auto& enemy : enemies_) {
        enemy->update(getElapsedTime());
        
        //if enemy has reached the castle
        player_.reachedCastle(enemy);
        if(player_.getHP() <= 0){
            //game over
            break;
        }

        /**
         * depending wether game or palyer keeps track of castle position
         * atl:
         * castle_.getGlobalBounds().intersects(enemy.getGlobalBounds())){
            player_.removeHP(10) <-- should prob be enemy specific
        */

    }
    // Pavel: updating towers below. Would someone double-check that logic is correct?
    // Perhaps I could try to migrate tower logic inside tower class, but is there any 
    // simple way to do so as updating tower logic uses private members enemies_ and 
    // projectiles_?
    for (auto* tower : towers_) {
        tower->update(enemies_);
        if (tower->getLockedEnemy() != nullptr && 
            tower->getFireTimer().getElapsedTime().asSeconds() >= 1.0f / tower->getFireRate()) {
                projectiles_.push_back(&(tower->shoot()));
                tower->resetFireTimer();
        }
    }
    
    /*for (auto& tower : towers_) {
        auto lockedEnemy = tower.getLockedEnemy();
        // If tower currently has no locked enemy, it should try to find one.
        // Following assumes that enemy object is removed from container enemies_
        // as soon as 0 hp is reached and thus hp is not checked when iterating through
        // enemies_
        if (lockedEnemy == nullptr) {
            auto damageType = tower.getDamageType();
            for (auto& enemy : enemies_) {
                auto enemyType = enemy->type();
                if (tower.enemyWithinRange(enemy) && ((damageType == CanDamage::Both) ||
                    (damageType == CanDamage::Flying && enemyType == EnemyType::Flying) ||
                    (damageType == CanDamage::Ground && enemyType == EnemyType::Ground))) {
                    tower.setLockedEnemy(enemy);
                    break;
                }
            }
        }
        else {
            if (lockedEnemy->hp() <= 0 || !tower.enemyWithinRange(lockedEnemy)) {
                tower.setLockedEnemy(nullptr);
                auto damageType = tower.getDamageType();
                for (auto& enemy : enemies_) {
                    auto enemyType = enemy->type();
                    if (tower.enemyWithinRange(enemy) && ((damageType == CanDamage::Both) ||
                        (damageType == CanDamage::Flying && enemyType == EnemyType::Flying) ||
                        (damageType == CanDamage::Ground && enemyType == EnemyType::Ground))) {
                        tower.setLockedEnemy(enemy);
                        break;
                    }
                }
            }
        }
        if (lockedEnemy != nullptr && tower.getFireTimer().getElapsedTime().asSeconds() >= 1.0f / tower.getFireRate()) {
            projectiles_.push_back(tower.shoot()); // shoot method returns Projectile that is appended to projectiles_
            tower.resetFireTimer();
        }      
    }*/

    for (auto* projectile : projectiles_) {
        projectile->update(*this);
        
        if(projectile->isDestroyed()){
//            delete projectile;
        }
    }
}

// Iterate over objects, render them onto window
void Game::render() {
    window_.clear();
    for (Button button : buttons_) {
        window_.draw(button);
    }
    for (auto* tower : towers_) {
        window_.draw(*tower);
    }
    for (auto* projectile : projectiles_) {
        window_.draw(*projectile);
    }
    for (auto enemy : enemies_) {
        if(!enemy->dead()) { //added a if statement to check if the enemy is dead, if it is it wont be rendered
            window_.draw(*enemy);
        }
    
    }
    window_.display();
}
// Check if a button has been pressed and act accordingly
void Game::checkButtons() {
    for (auto button : buttons_) {
        if (button.isClicked((sf::Vector2f) sf::Mouse::getPosition(window_))) {
            switch (button.getAction())
            {
            case Actions::Tower1 :
            {
                BombTower* new_bomb = new BombTower((sf::Vector2f) sf::Mouse::getPosition(window_));
                new_bomb->setTexture(tower_textures_.get(Textures::Tower1));
                /* New tower takes first place in array of towers. 
                   This is enough to identify the new tower which is being dragged, as only one tower 
                   can be added at a time
                */
                towers_.push_front(new_bomb);

                // Set flag which indicates an object is being dragged
                dragged_ = true;
                break;
            }
            case Actions::Tower2 :
            {
                BulletTower* new_bullet = new BulletTower((sf::Vector2f) sf::Mouse::getPosition(window_));
                new_bullet->setTexture(tower_textures_.get(Textures::Tower2));
                towers_.push_front(new_bullet);

                // Set flag which indicates an object is being dragged
                dragged_ = true;
            }
            case Actions::Pause :
            {
                paused_ = !paused_;
                break;
            }
            default:
                break;
            }
        }    
        }

}

// If a tower is being dragged into place this handles it's movement
void Game::drag() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        towers_.front()->setPosition(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y);
        //printf("Position: %f, %f \n", dragged_->getPosition().x, dragged_->getPosition().y);
    } else {
        Tower* bought_tower = towers_.front();
        if (player_.getWallet() < bought_tower->getBaseCost()) {
            towers_.pop_front();
            delete bought_tower;
        } else {
            player_.removeMoney(bought_tower->getBaseCost());
        }
        dragged_ = false;
        // TODO: Check tower collision conds
        // TODO: Work with player class to check money
    }
}

sf::Time Game::getElapsedTime() const {
    return time_;
}

// Test function for enemy class
void Game::testEnemy() {

    path newpath;
    newpath.addWaypoint(sf::Vector2f(400, 400));
    newpath.addWaypoint(sf::Vector2f(500, 400));
    newpath.addWaypoint(sf::Vector2f(500, 200));

    Enemy test(1, 100, EnemyType::Ground, 10, newpath);
    test.setPosition(100, 100);
    test.setTexture(enemy_textures_.get(Textures::Enemy1));

    enemies_.push_back(std::make_shared<Enemy>(test));

    Enemy test2(1, 60, EnemyType::Ground, 10, newpath);
    test2.setPosition(50, 50);
    test2.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test2));

    Enemy test3(1, 30, EnemyType::Ground, 10, newpath);
    test3.setPosition(70, 70);
    test3.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test3));
}
