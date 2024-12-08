#pragma once
#include <SFML/Graphics.hpp>
#include "Text.cpp"
#include <functional>
#include <utility>
#include "Button.h"
#include "Question.h"
#include <vector>
#include"DEFINITIONS.h"

class Game {
protected:
    sf::RenderWindow window;
    sf::Font font;
    int playerScore;                     // To track the player's score
    size_t currentAnswerIndex;              // To track the current selected answer index


    // Buttons
    Button* playButton;
    Button* scienceButton;
    Button* mathButton;
    Button* gkButton;
    Button* Next;
    Button* Menu;
    Button* Exit;
    Button* CheckAsnwers;

    std::vector<Button*> optionButtons;
    std::vector<Text*> textButtons;
    std::vector<Question> questions;
    std::vector<Question> WrongQuestions;
    std::vector<std::string> WrongAnswers;
    size_t currentQuestionIndex;
    sf::Texture texture;
    
    // Game States

    enum State { MENU, CATEGORIES, scienceQuestion, mathQuestion, gkQuestion, GAME_OVER, checkAnswer};
    State currentState;

    void loadAssets();
    void loadBackground(sf::RenderWindow& window);
    void renderMenuState();
    void renderCategoriesState();
    void renderScienceQuestionState();
    void renderMathQuestionState();
    void renderGkQuestionState();
    void renderGameOverState();
    void renderWrongQuestionState();
    void renderNextAction();
    void stateTransition();
    void resizeBackgroundImage(sf::Sprite& background, const sf::Texture& texture);

    void DisplayQuestions();
    void handleEvents(const sf::Event&);
    std::vector<std::pair<Button*, std::function<void()>>> getButtonActionMap();
public:
    Game();
    ~Game();
    void run();
};


