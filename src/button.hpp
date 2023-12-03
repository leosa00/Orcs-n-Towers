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
    Upgrade,
    Close,  // In upgrade menu, closes upgrade menu.
    Level   // Click to start level
};

class Button : public sf::Sprite {
public:
    Button(Actions action, sf::Texture& texture, sf::Vector2f position, std::string text, sf::Font& font) : action_(action) {
        setTexture(texture);
        setPosition(position);
        label_ = sf::Text(text, font, 15);
        label_.setPosition(position.x, position.y+20);
    }
    bool isClicked(sf::Vector2f mousePos) const {
        return getGlobalBounds().contains(mousePos);
    }

    Actions getAction() const {return action_;}
    sf::Text getLabel() const {return label_;}

private:
    Actions action_;
    sf::Text label_;

};


#endif