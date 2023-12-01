#include "menu.hpp"
#include "bombTower.hpp"
#include "bulletTower.hpp"

void Menu::draw(sf::RenderWindow& window) {
    for (auto button : buttons_) {
        window.draw(button);
    }
}

void Menu::checkButtons(Game& game) {
    for (auto button : buttons_) {
        if (button.isClicked((sf::Vector2f) sf::Mouse::getPosition(game.window_))) {
            //TODO: check if player can afford before creating tower and handle removing money here

            switch (button.getAction())
            {
            case Actions::Tower1 :
            {
                BombTower* new_bomb = new BombTower((sf::Vector2f) sf::Mouse::getPosition(game.window_));
                new_bomb->setTexture(game.tower_textures_.get(Textures::Tower1));
                /* New tower takes first place in array of towers. 
                   This is enough to identify the new tower which is being dragged, as only one tower 
                   can be added at a time
                */
                game.towers_.push_front(new_bomb);

                // Set flag which indicates an object is being dragged
                game.dragged_ = true;
                break;
            }
            case Actions::Tower2 :
            {
                BulletTower* new_bullet = new BulletTower((sf::Vector2f) sf::Mouse::getPosition(window_));
                new_bullet->setTexture(game.tower_textures_.get(Textures::Tower2));
                game.towers_.push_front(new_bullet);

                // Set flag which indicates an object is being dragged
                game.dragged_ = true;
                break;
            }
            case Actions::Upgrade :
            {
                game.upgrade_ = 
            }
            case Actions::Pause :
            {
                game.paused_ = !game.paused_;
                break;
            }
            default:
                break;
            }
        }    
        }

}