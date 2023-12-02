#include "menu.hpp"
#include "bombTower.hpp"
#include "bulletTower.hpp"
#include <string>
#include <stdio.h>

// Draws all the buttons in the menu
void Menu::draw(sf::RenderWindow& window) {
    for (auto button : buttons_) {
        window.draw(button);
        window.setVerticalSyncEnabled(true);//this should help with the major screen tearing
        window.draw(button.getLabel());
    }

    for (auto text : texts_) {
        window.draw(text);
    }
}

// Iterates through the buttons in the menu and checks if something is clicked
// Chooses action based on button type
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
                // Check that there is enough money for upgrading
                int upgradecost = game->upgradedTower_->getUpgradeCost();
                if (game->player_.getWallet() >= upgradecost) {
                    // Remove money and upgrade
                    game->player_.removeMoney(upgradecost);
                    game->upgradedTower_->upgradeTower();

                    // Update texts of current damage and level
                    texts_.front().setString("Level: " + std::to_string(game->upgradedTower_->getCurrentLvl()));
                    texts_.back().setString("Damage: " + std::to_string(game->upgradedTower_->getDamage()));

                }
            }
            case Actions::Close :
            {
                // Afraid that this leaks memory...
                //game->upgrade_ = nullptr;
                //game->upgradedTower_ = nullptr;

            }
            case Actions::Pause :
            {
                // TODO: The pause button gets often accidentally activated
                //game->paused_ = !game->paused_;
                //break;
            }
            default:
                break;
            }
        }    
        }

}

// Creates menu based on the input enum given
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
            
            std::string money = std::to_string(game->player_.getWallet());
            std::string health = std::to_string(game->player_.getHP());
            sf::Text euro(money + " EUR", game->font_, 20);
            sf::Text hp(health + " HP", game->font_, 20);
            euro.setPosition(900, 600);
            hp.setPosition(900, 650);
            texts_.push_back(euro);
            texts_.push_back(hp);
            
        }
        break;
    case MenuType::Upgrade:
        {
            // Create upgrade and close buttons
            buttons_.push_back(Button(Actions::Close, game->enemy_textures_.get(Textures::Enemy2), sf::Vector2f(400, 700), "Close", game->font_));
            std::cout << "Upgrade menu created" << std::endl;
            std::string cost = std::to_string(game->upgradedTower_->getUpgradeCost());
            buttons_.push_back(Button(Actions::Upgrade, game->enemy_textures_.get(Textures::Enemy2), sf::Vector2f(150, 700), cost, game->font_));

            // create texts of type current damage and level
            // + operator with string handles conversion
            sf::Text damage(("Damage: " + std::to_string(game->upgradedTower_->getDamage())), game->font_, 20);
            sf::Text level(("Level: " + std::to_string(game->upgradedTower_->getCurrentLvl())), game->font_, 20);
            sf::Text type(game->upgradedTower_->getType(), game->font_, 20);
            
            type.setPosition(30, 700);
            level.setPosition(30, 720);
            damage.setPosition(30, 740);

            // This is a dumb solution, but level is stored first and damage last
            // So they are easy to access if they get updated
            texts_.push_back(level);
            texts_.push_back(type);
            texts_.push_back(damage);
        }
    default:
        break;
    }
}

void Menu::update(Player& player){
    std::string money = std::to_string(player.getWallet()) + " EUR";
    std::string health = std::to_string(player.getHP()) + " HP";
    texts_.front().setString(money);
    texts_.back().setString(health);
}