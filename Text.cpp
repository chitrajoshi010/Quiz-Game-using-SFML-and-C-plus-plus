#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
class Text{
private:
    sf::Text text;
    sf::Font& font;
public:
    Text(sf::Font& font, const std::string& label, int size, sf::Vector2f position, sf::Color color = sf::Color::Transparent)
		: font(font) {
            
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(position.x, position.y);
	}
    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }
};