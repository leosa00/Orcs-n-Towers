#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>
#include <list>
#include "button.hpp"
#include "game.hpp"


/**
 * @brief Class for storing a collection of buttons, a menu.
 *
*/
class Menu {
public:
    void draw(sf::RenderWindow& window);
    void checkButtons(Game& game);
    void addButtons();
private:
    std::list<Button> buttons_;
};

#endif