#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>
#include <list>
#include "button.hpp"
#include "game.hpp"

// These are used in createMenu()
// the enum determines what type of menu is created:
// Which buttons are added etc.
enum class MenuType{
    Shop,
    Upgrade,
    Begin,
    Level
};
/**
 * @brief Class for storing a collection of buttons, a menu.
 *
*/
class Menu {
public:
    void draw(sf::RenderWindow& window);
    void checkButtons(Game* game);
    void createMenu(MenuType menu, Game* game);
    void update(Player& player);
    bool canBePlaced(Game* game);
    void drag(Game* game);
private:
    std::list<Button> buttons_;
    std::list<sf::Text> texts_;
    sf::RectangleShape bg_;
};

#endif