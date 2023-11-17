#include "game.hpp"

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
    // Do stuff
    // Pavel: following order of updates is perhaps ok
    
    for (auto& enemy : enemies_) {
        enemy->update();
    }
    // Pavel: updating towers below. Would someone double-check that logic is correct?
    // Perhaps I could try to migrate tower logic inside tower class, but is there any 
    // simple way to do so as updating tower logic uses protected members enemies_ and 
    // projectiles_?
    for (auto& tower: towers_) {
        auto lockedEnemy = tower.getLockedEnemy();
        // If tower currently has no locked enemy, it should try to find one.
        // Following assumes that enemy object is removed from container enemies_
        // as soon as 0 hp is reached and thus hp is not checked when iterating through
        // enemies_
        if (lockedEnemy == nullptr) {
            for (auto& enemy : enemies_) {
                if (tower.enemyWithinRange(enemy)) {
                    tower.setLockedEnemy(enemy);
                    break;
                }
            }
        }
        else {
            if (lockedEnemy->hp() <= 0 || !tower.enemyWithinRange(lockedEnemy)) {
                tower.setLockedEnemy(nullptr);
                for (auto& enemy : enemies_) {
                    if (tower.enemyWithinRange(enemy)) {
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

    for (auto& projectile : projectiles_) {
        projectile.update();
    }
}

// Iterate over objects, render them onto window
void Game::render() {
    // Render stuff
}