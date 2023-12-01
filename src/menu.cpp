#include "menu.hpp"
#include "bombTower.hpp"
#include "bulletTower.hpp"
#include <stdio.h>

void Menu::draw(sf::RenderWindow& window) {
    for (auto button : buttons_) {
        window.draw(button);
        window.setVerticalSyncEnabled(true);//this should help with the major screen tearing
        window.draw(button.getLabel());
    }
}

void Menu::checkButtons(Game* game) {
    for (auto button : buttons_) {
        if (button.isClicked((sf::Vector2f) sf::Mouse::getPosition(game->window_))) {
            //TODO: check if player can afford before creating tower and handle removing money here

            switch (button.getAction())
            {
            case Actions::Tower1 :
            {
                BombTower* new_bomb = new BombTower((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bomb->setTexture(game->tower_textures_.get(Textures::Tower1));
                /* New tower takes first place in array of towers. 
                   This is enough to identify the new tower which is being dragged, as only one tower 
                   can be added at a time
                */
                game->towers_.push_front(new_bomb);

                // Set flag which indicates an object is being dragged
                game->dragged_ = true;
                break;
            }
            case Actions::Tower2 :
            {
                BulletTower* new_bullet = new BulletTower((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bullet->setTexture(game->tower_textures_.get(Textures::Tower2));
                game->towers_.push_front(new_bullet);

                // Set flag which indicates an object is being dragged
                game->dragged_ = true;
                break;
            }

            // If the button upgrade is pressed, there is already a upgrade menu in existence
            // And the tower which wi want to upgrade is known
            case Actions::Upgrade :
            {

            }
            case Actions::Pause :
            {
                game->paused_ = !game->paused_;
                break;
            }
            default:
                break;
            }
        }    
        }

}

void Menu::createMenu(MenuType menu, Game* game) {
    switch (menu)
    {
    case MenuType::Shop:
        {
            // Create Buttons
            buttons_.push_back(Button(Actions::Tower1, game->tower_textures_.get(Textures::Tower1), sf::Vector2f(920, 40), "300", game->font_));
            buttons_.push_back(Button(Actions::Tower2, game->tower_textures_.get(Textures::Tower2), sf::Vector2f(920, 100), "200", game->font_));
            // This needs a texture or something
            buttons_.push_back(Button(Actions::Pause, game->tower_textures_.get(Textures::Tower3), sf::Vector2f(900, 700), "pause", game->font_));//uses pause button texture as tower3
        }
        break;
    case MenuType::Upgrade:
        {
            std::cout << "Upgrade menu created" << std::endl;
        }
    default:
        break;
    }
}