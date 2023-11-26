#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>

enum class Actions{
    Tower1,
    Tower2,
    Tower3,
    Tower4,
    Tower5,
    Pause,
    Upgrade
};

class Button : public sf::Sprite {
public:
    Button(Actions action, sf::Texture& texture, sf::Vector2f position) : action_(action) {
        setTexture(texture);
        setPosition(position);
    }
    bool isClicked(sf::Vector2f mousePos) const {
        return getGlobalBounds().contains(mousePos);
    }

    Actions getAction() const {return action_;}

private:
    Actions action_;

};


#endif