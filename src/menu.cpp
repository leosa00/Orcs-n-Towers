#include "menu.hpp"
#include "bombTower.hpp"
#include "bulletTower.hpp"
#include "missileTower.hpp"
#include <string>
#include <stdio.h>

// Draws all the buttons in the menu
void Menu::draw(sf::RenderWindow& window) {
    window.draw(bg_);
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

            // TODO: this is highly repetitive in tower creation, could probably be somehow streamlined...
            switch (button.getAction())
            {
            case Actions::Tower1:
            {
                if (game->activeTower_) {
                    delete game->alternativeMenu_;
                    game->alternativeMenu_ = nullptr;
                    game->activeTower_ = nullptr;
                }
                BombTower* new_bomb = new BombTower((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bomb->setTexture(game->tower_textures_.get(Textures::BombTower));
                /* New tower takes first place in array of towers. 
                   This is enough to identify the new tower which is being dragged, as only one tower 
                   can be added at a time
                */
                game->activeTower_ = new_bomb;

                // Set flag which indicates an object is being dragged
                game->dragged_ = true;

                // Color remove area red
                bg_.setFillColor(sf::Color(100, 26, 26, 100));
                break;
            }
            case Actions::Tower2:
            {
                 if (game->activeTower_) {
                    delete game->alternativeMenu_;
                    game->alternativeMenu_ = nullptr;
                    game->activeTower_ = nullptr;
                }
                BulletTower* new_bullet = new BulletTower((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_bullet->setTexture(game->tower_textures_.get(Textures::BulletTower));
                game->activeTower_ = new_bullet;

                // Set flag which indicates an object is being dragged
                game->dragged_ = true;
                bg_.setFillColor(sf::Color(100, 26, 26, 100));
                break;
            }
            case Actions::Tower3:
            {
                 if (game->activeTower_) {
                    delete game->alternativeMenu_;
                    game->alternativeMenu_ = nullptr;
                    game->activeTower_ = nullptr;
                }
                MissileTower* new_missile = new MissileTower((sf::Vector2f) sf::Mouse::getPosition(game->window_));
                new_missile->setTexture(game->tower_textures_.get(Textures::MissileTower));
                game->activeTower_ = new_missile;
                game->dragged_ = true;
                bg_.setFillColor(sf::Color(100, 26, 26, 100));
                break;
            }

            // If the button upgrade is pressed, there is already a upgrade menu in existence
            // And the tower which wi want to upgrade is known
            case Actions::Upgrade:
            {
                // Check that there is enough money for upgrading
                int upgradecost = game->activeTower_->getUpgradeCost();
                if (game->player_.getWallet() >= upgradecost) {
                    // Check that max level is not reached
                    if (!game->activeTower_->isMaxLevelReached()){
                        // Remove money and upgrade
                        game->player_.removeMoney(upgradecost);
                        game->activeTower_->upgradeTower();
                        // Update texts of current damage and level
                        texts_.front().setString("Level: " + std::to_string(game->activeTower_->getCurrentLvl()));
                        texts_.back().setString("Damage: " + std::to_string(game->activeTower_->getDamage()));
                    }
                }
                break;
            }
            case Actions::Close:
            {
                // Afraid that this leaks memory...
                game->alternativeMenu_ = nullptr;
                game->activeTower_ = nullptr;
                //sf::FloatRect buttonbounds = button.getGlobalBounds();
                break;
            }
            case Actions::Pause:
            {
                game->paused_ = !game->paused_;
                break;
            }
            case Actions::Level:
            {
                game->enemies_ = game->player_.increaseLevel(game->enemy_textures_, game->path_);
                game->paused_ = false;
                game->alternativeMenu_ = nullptr;
                break;
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
            // Create background
            bg_ = sf::RectangleShape(sf::Vector2f(100, 800));
            bg_.setPosition(900, 0);
            bg_.setFillColor(sf::Color(0, 26, 26, 100));
            // Create Buttons
            buttons_.push_back(Button(Actions::Tower1, game->tower_textures_.get(Textures::BombTower), sf::Vector2f(920, 40), "300", game->font_));
            buttons_.push_back(Button(Actions::Tower2, game->tower_textures_.get(Textures::BulletTower), sf::Vector2f(920, 100), "200", game->font_));
            buttons_.push_back(Button(Actions::Tower3, game->tower_textures_.get(Textures::MissileTower), sf::Vector2f(920, 160), "200", game->font_));
            // This needs a texture or something
            buttons_.push_back(Button(Actions::Pause, game->various_textures_.get(Textures::Pause), sf::Vector2f(900, 700), "pause", game->font_));//uses pause button texture as tower3
            
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
            std::string cost = std::to_string(game->activeTower_->getUpgradeCost());
            buttons_.push_back(Button(Actions::Upgrade, game->enemy_textures_.get(Textures::Enemy2), sf::Vector2f(150, 700), cost, game->font_));

            // create texts of type current damage and level
            // + operator with string handles conversion
            sf::Text damage(("Damage: " + std::to_string(game->activeTower_->getDamage())), game->font_, 20);
            sf::Text level(("Level: " + std::to_string(game->activeTower_->getCurrentLvl())), game->font_, 20);
            sf::Text type(game->activeTower_->getType(), game->font_, 20);
            
            type.setPosition(30, 700);
            level.setPosition(30, 720);
            damage.setPosition(30, 740);

            // This is a dumb solution, but level is stored first and damage last
            // So they are easy to access if they get updated
            texts_.push_back(level);
            texts_.push_back(type);
            texts_.push_back(damage);
            break;
        }
    case MenuType::Begin:
        {
            buttons_.push_back(Button(Actions::Level, game->enemy_textures_.get(Textures::Enemy2), sf::Vector2f(400, 450), "Begin", game->font_));

            sf::Text intro("Welcome to Orcs n Towers\nClick to start the first level!", game->font_, 20);
            intro.setPosition(400, 400);
            texts_.push_back(intro);
            break;
        }
    case MenuType::Level:
        {
            // TODO: It would be nice to have a money bonus for completing each level
            buttons_.push_back(Button(Actions::Level, game->enemy_textures_.get(Textures::Enemy2), sf::Vector2f(400, 440), "Next level", game->font_));
            // FIXME: The text does not include the first letter :(
            sf::Text intro(("Congratulations for completing level " + game->player_.getLevel()), game->font_, 20);
            intro.setPosition(400, 400);
            texts_.push_back(intro);
            break;
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

void Menu::drag(Game* game) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        game->activeTower_->setPosition(sf::Mouse::getPosition(game->window_).x, sf::Mouse::getPosition(game->window_).y);
    } else {
        if (game->player_.getWallet() < game->activeTower_->getBaseCost() || !canBePlaced(game)) {
            delete game->activeTower_;
        } else {
            game->player_.removeMoney(game->activeTower_->getBaseCost());
            game->towers_.push_front(game->activeTower_);
        }
        game->activeTower_ = nullptr;
        game->dragged_ = false;
        bg_.setFillColor(sf::Color(0, 26, 26, 100));
    }
}

bool Menu::canBePlaced(Game* game){
    // TODO: Check intersection with path

    sf::Rect pos = game->activeTower_->getGlobalBounds();
    // Check intersection with window
    if (!pos.intersects(sf::Rect(sf::Vector2f(0, 0), (sf::Vector2f) game->window_.getSize()))) {
        return false;
    }

    // Check intersection with delete area
    if (bg_.getGlobalBounds().intersects(pos)){
        return false;
    }

    // Check intersection with other towers
    for (auto tower : game->towers_) {
        if (pos.intersects(tower->getGlobalBounds())) {
            return false;
        }
    }

    return true;
}