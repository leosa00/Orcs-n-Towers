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
}

// Iterate over objects, render them onto window
void Game::render() {
    // Render stuff
}