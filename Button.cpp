#include "Button.h"

Button::Button(sf::Font& font, const std::string& label, sf::Vector2f size, sf::Vector2f position, sf::Color OutlineColor, sf::Color buttonColor , int Size)
    : font(font), isSelected(false) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(OutlineColor);
    shape.setOutlineThickness(5);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(Size);
    text.setFillColor(buttonColor);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}
bool Button::isClicked(sf::Vector2i mousePos) {
    return shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::select(sf::RenderWindow& window) {
    isSelected = true;
    shape.setFillColor(sf::Color::Blue); //Change the color to indicate selection
    window.draw(shape);
    window.display();
}
void Button::deselect() {
    isSelected = false;
    shape.setFillColor(sf::Color::Black); // Revert to the original color
}
bool Button::getSelectionState() const {
    return isSelected;
}
