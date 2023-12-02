#include "game.hpp"
#include "bombTower.hpp"
#include <memory>
#include "path.hpp"
#include "button.hpp"
#include <iostream>

// initialize game object, mainly create window...
Game::Game() : window_(sf::VideoMode(1000, 800), "Orcs n Towers") {
    // Set dragging flag
    dragged_ = false;
    paused_ = false;
    std::cout << "testtest" << std::endl;


    //Load the Map texture
    if (!map.texture.loadFromFile("../textures/grass.jpeg"))
    {
        return;
    }
    map.background.setTexture(map.texture);

    // Create tower texture container, load texture    
    tower_textures_ = ResourceContainer<Textures::TowerID, sf::Texture>();
    
    tower_textures_.load(Textures::Tower1, "../textures/tower1.png");
    tower_textures_.load(Textures::Tower2, "../textures/tower2.png");
    tower_textures_.load(Textures::Tower3, "../textures/pausebutton.png");//pause button texture needs to be changed to its own texture class later
    enemy_textures_ = ResourceContainer<Textures::EnemyID, sf::Texture>();
   
    enemy_textures_.load(Textures::Enemy1, "../textures/goblin_test.png");
    enemy_textures_.load(Textures::Enemy2, "../textures/mikey.png");
    
    projectile_textures_ = ResourceContainer<Textures::ProjectileID, sf::Texture>();

    projectile_textures_.load(Textures::Bullet, "../textures/bullet_test.png");
    projectile_textures_.load(Textures::Bomb, "../textures/bomb_test.png");
    projectile_textures_.load(Textures::Missile, "../textures/mikey.png");
    // Load font
  
    font_.loadFromFile("../textures/OpenSans_Condensed-Bold.ttf");
    

    // Initialize menus
    shop_ = new Menu();
    shop_->createMenu(MenuType::Shop, this);
    upgrade_ = nullptr;
    upgradedTower_ = nullptr;

    //game over text
    gameOverText.setFont(font_);
    gameOverText.setString("Game Over Loser!!");
    gameOverText.setCharacterSize(24); 
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(400, 200);
    createPath();

    testEnemy();

    player_ = Player();
    
    //player_.updateCastlePosition(**coordinates for end of path**);
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
                shop_->checkButtons(this);
                if (upgrade_) {
                    upgrade_->checkButtons(this);
                }
                if (!dragged_) {
                    checkTowers(); // If no button was pressed check if a tower has been clicked
                }
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
    if(player_.getHP() <= 0){
            //game over
            isGameOver_ = true;
            return;
    }
    
    // Updates displayed wallet amount and health
    shop_->update(player_);
    
    // Pavel: following order of updates is perhaps ok
    for (auto it = enemies_.begin(); it != enemies_.end();) {
    if ((*it)->dead()) {
        //this if statement and the functions inside are used to test the
        //enemy split functionality
        if((*it)->getWaypoints().empty()) {
            player_.removeHP(250);
            std::cout << "player health: " << player_.getHP() << std::endl;//player hp deduction test (works!!)
        } else {
            // Add money to player for successful kill
            player_.addMoney((*it)->getMoney());
        }
        if((*it)->type() == EnemyType::Flying) { //now if the enemy dies because it reached the castle it wont split, otherwise it will
        //I also fixed the split enemies movement
            std::queue<sf::Vector2f> waypoints = (*it)->getWaypoints();
            if(!waypoints.empty()) {
                sf::Vector2f position = (*it)->getCenter();
                testEnemySplit(position, waypoints);
                }
        }
        //removes an enemy from the list and subsequently it is destroyed, if the enemy
        //is dead
        it = enemies_.erase(it); 
    } else {
//        std::cout << enemies_.size() << std::endl;
        (*it)->update(getTime());
        //if enemy has reached the castle
       //player_.reachedCastle(*it); //this might not work since enemies are dead once they reach the final
        //checkpoint (the castle) may not activate this
        ++it;
    }
    }

        /**
         * depending wether game or palyer keeps track of castle position
         * atl:
         * castle_.getGlobalBounds().intersects(enemy.getGlobalBounds())){
            player_.removeHP(10) <-- should prob be enemy specific
        */

    
    // Pavel: updating towers below. Would someone double-check that logic is correct?
    // Perhaps I could try to migrate tower logic inside tower class, but is there any 
    // simple way to do so as updating tower logic uses private members enemies_ and 
    // projectiles_?
    for (auto* tower : towers_) {
        tower->update(enemies_);
        if (tower->getLockedEnemy() != nullptr && 
            tower->getFireTimer().getElapsedTime().asSeconds() >= 1.0f / tower->getFireRate()) {
                // Added an intermediate step into shooting which sets the projectile texture
                Projectile* newproj = &(tower->shoot());
                newproj->setTexture(projectile_textures_.get(newproj->textureType()));
                //newproj->setPosition(tower->getPosition());
                projectiles_.push_back(newproj);
                
                //projectiles_.push_back(&(tower->shoot()));
                
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


//cleans up list while iterating
    for(auto i = projectiles_.begin(); i != projectiles_.end();){
        (*i)->update(*this);

        if((*i)->isDestroyed()){
            delete (*i);
            //erase returns next iterator
            i = projectiles_.erase(i);
        }
        else{
            i++;
        }
    }
}
//createPath function used to test the game out, so far the coordinates are
//hardcoded
void Game::createPath() {
    path_.addWaypoint(sf::Vector2f(400, 400));
    path_.addWaypoint(sf::Vector2f(500, 400));
    path_.addWaypoint(sf::Vector2f(500, 200));
    path_.addWaypoint(sf::Vector2f(400, 200));
    path_.addWaypoint(sf::Vector2f(400, 100));
}
// Iterate over objects, render them onto window
void Game::render() {
    window_.clear();
    window_.draw(map);

    
    shop_->draw(window_);
    if (upgrade_ != nullptr) {
        upgrade_->draw(window_);
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
    if(isGameOver_) {
        window_.draw(gameOverText);
    }
    window_.display();
}

// If a tower is being dragged into place this handles it's movement
void Game::drag() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        towers_.front()->setPosition(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y);
    } else {
        Tower* bought_tower = towers_.front();
        if (player_.getWallet() < bought_tower->getBaseCost()) {
            towers_.pop_front();
            delete bought_tower;
        } else {
            player_.removeMoney(bought_tower->getBaseCost());
        }
        dragged_ = false;
    }
}

sf::Time Game::getTime() const {
    return time_;
}

void Game::checkTowers() {
    sf::Vector2f mousepos = (sf::Vector2f) sf::Mouse::getPosition(window_);
    for (auto* tower : towers_) {
        if (tower->getGlobalBounds().contains(mousepos)) {
            // This stores the pointer to the tower that the upgrade button
            // Will potentially upgrade
            upgradedTower_ = tower;
            upgrade_ = new Menu();
            upgrade_->createMenu(MenuType::Upgrade, this);
        }
    }
}

// Test function for enemy class
void Game::testEnemy() {


    Enemy test(1, 100, EnemyType::Ground, 10, path_.getWaypoints());
    test.setPosition(100, 100);
    test.setTexture(enemy_textures_.get(Textures::Enemy1));

    enemies_.push_back(std::make_shared<Enemy>(test));

    Enemy test2(30, 60, EnemyType::Flying, 10, path_.getWaypoints());
    test2.setPosition(100, 50);
    test2.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test2));

    Enemy test3(900, 30, EnemyType::Ground, 10, path_.getWaypoints());
    test3.setPosition(100, 70);
    test3.setTexture(enemy_textures_.get(Textures::Enemy1));
    enemies_.push_back(std::make_shared<Enemy>(test3));

    //Projectile* missl = new MissileProjectile(sf::Vector2f(300,100), 50, enemies_.front());
    ////this actually renders
    //missl->setTexture(tower_textures_.get(Textures::Tower2));

    //projectiles_.push_back(missl);
}
//This function is used to test a splitting enemy functionality, i used the
//tower texture to make it easier to debug, the idea is that a type of enemy, at this
//point i just used Flying as the tag, upon death will split into two smaller enemies
//currently this works but the path doesnt seem to work properly yet
void Game::testEnemySplit(sf::Vector2f position, std::queue<sf::Vector2f> waypoints) {
    Enemy split(1, 60, EnemyType::Ground, 10, waypoints);
    split.setPosition(position.x, position.y);
    split.setTexture(enemy_textures_.get(Textures::Enemy2));

    enemies_.push_back(std::make_shared<Enemy>(split));

}

