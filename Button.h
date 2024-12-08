#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font& font;

    bool isSelected; // New member to track if the button is selected
    sf::Color originalColor;
    sf::Color selectedColor;


public:
    Button(sf::Font& font, const std::string& label, sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Color buttoncolor = sf::Color::White, int Size = 40);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
    void select(sf::RenderWindow& window);    // Set the button as selected
    void deselect();  // Set the button as deselected
    bool getSelectionState() const; // Check if the button is selected

};
