#include "game.hpp"

// initialize game object, mainly create window...
Game::Game() : window_(sf::VideoMode(1000, 800), "Orcs n Towers") {
    // Create sidebar
    sf::RectangleShape sidebar(sf::Vector2f(100, 800));
    sidebar.setPosition(900, 0);
    sidebar.setFillColor(sf::Color::Blue);
    // Create test button
    sf::RectangleShape button(sf::Vector2f(60, 40));
    button.setPosition(920, 40);
    button.setFillColor(sf::Color::Red);
    // Add buttons to list of buttons
    buttons_.push_back(sidebar);
    buttons_.push_back(button);

    // Set dragging flag
    dragged_ = false;

    // Create tower texture container, load texture    
    tower_textures_ = ResourceContainer<Textures::TowerID, sf::Texture>();
    tower_textures_.load(Textures::Tower1, "tower_test.png");
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
        /* I think that we could include a case which detects if mouse button
        has been pressed. This case would then call a function, which maybe
        checks, if mouse was pressed on an object of interest.
        This would then call other necessary functions accordingly*/

        default:
            break;
        }
    }
}

// Call functions necessary for iterating over all objects and updating their states
void Game::update() {
    // TODO: If the game is paused stop updating

    // If a tower is being dragged, update it's position
    if (dragged_) {
        drag();
    }

    // Pavel: following order of updates is perhaps ok
    
    for (auto& enemy : enemies_) {
        enemy->update();
    }
    // Pavel: updating towers below. Would someone double-check that logic is correct?
    // Perhaps I could try to migrate tower logic inside tower class, but is there any 
    // simple way to do so as updating tower logic uses private members enemies_ and 
    // projectiles_?
    for (auto& tower : towers_) {
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
    }

    //for (auto& projectile : projectiles_) {
    //    projectile.update();
    //}
}

// Iterate over objects, render them onto window
void Game::render() {
    window_.clear();
    for (auto button : buttons_) {
        window_.draw(button);
    }
    for (auto tower : towers_) {
        window_.draw(tower);
    }
    window_.display();
}

// Check if a button has been pressed and act accordingly
// TODO: maybe a separate button class would make things easier, this should also recognize pause button
void Game::checkButtons() {
    for (auto button : buttons_) {
        // Ugly if statement, creates sf::Rect of the same size as the button, and checks if
        // mouse is inside it using the .contains method
        if ( sf::Rect<int>((sf::Vector2i) button.getSize(), (sf::Vector2i) button.getPosition())
        .contains(sf::Mouse::getPosition(window_))) {
            /* Currently we just recognize that the only button corresponding to the only button has been pressed
               so we create a new tower of which there is currently only one type.
               The buttons should probably be implemented in a separate class to enable easier
               implementation of separate buttons for different towers
             */
            Tower new_tower = Tower((sf::Vector2f) sf::Mouse::getPosition(window_));
            new_tower.setTexture(tower_textures_.get(Textures::Tower1));

            /* New tower takes first place in array of towers. 
               This is enough to identify the new tower which is being dragged, as only one tower 
               can be added at a time
            */
            towers_.push_front(new_tower);
    
            // Set flag which indicates an object is being dragged
            dragged_ = true;
        }

    }
}
// If a tower is being dragged into place this handles it's movement
void Game::drag() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        towers_.front().setPosition(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y);
        //printf("Position: %f, %f \n", dragged_->getPosition().x, dragged_->getPosition().y);
    } else {
        // TODO: Check tower collision conds
        dragged_ = false;
    }
}