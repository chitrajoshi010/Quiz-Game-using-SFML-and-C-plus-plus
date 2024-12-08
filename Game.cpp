#include "Game.h"
#include<iostream>

Game::Game()
    : window(sf::VideoMode(windowWidth, windowHeight), "Quiz Game"), currentState(MENU), currentQuestionIndex(0), playerScore(0), currentAnswerIndex(-1), optionButtons() {
    loadAssets();

    // Initialize buttons
    playButton = new Button(font, "Play", { (buttonSizeX - 50), buttonSizeY }, { ((windowWidth - buttonSizeX) / 2.f) + 30, (2.f * windowHeight) / 3.5f }, sf::Color::Transparent, sf::Color::Black, 50);
    scienceButton = new Button(font, "Science", { buttonSizeX, buttonSizeY }, { (windowWidth - buttonSizeX) / 2.f, (windowHeight/3.f + buttonSizeY) }, sf::Color::Transparent);
    mathButton = new Button(font, "Math", { buttonSizeX, buttonSizeY }, { (windowWidth - buttonSizeX) / 2.f, (windowHeight/3.f + (3.f *buttonSizeY)) }, sf::Color::Transparent);
    gkButton = new Button(font, "GK", { buttonSizeX, buttonSizeY }, { (windowWidth - buttonSizeX) / 2.f, (windowHeight / 3.f + (5.f * buttonSizeY)) }, sf::Color::Transparent);
    Next = new Button(font, "NEXT", { buttonSizeX , buttonSizeY }, { (3 * windowWidth) / 4.f, (3.f * windowHeight) / 4.f }, sf::Color::Transparent);
    Menu = new Button(font, "Menu", { buttonSizeX, buttonSizeY }, { (windowWidth) / 4.f, (3.f * windowHeight) / 4.f }, sf::Color::Transparent);
    Exit = new Button(font, "Exit", { buttonSizeX, buttonSizeY }, { (2.5f* windowWidth) / 4.f, (3.f * windowHeight) / 4.f }, sf::Color::Transparent);
    CheckAsnwers = new Button(font, "Check Answer", { buttonSizeX, buttonSizeY }, { (windowWidth) / 1.5f, (3.5f * windowHeight) / 4.f }, sf::Color::Transparent);
}
Game::~Game() {
    delete playButton;
    delete scienceButton;
    delete mathButton;
    delete gkButton;
    delete Next;
    delete Menu;
    delete Exit;
    delete CheckAsnwers;
    // Clean up dynamically allocated buttons in optionButtons
    for (auto button : optionButtons) {
        delete button;
    }
}

void Game::loadAssets() {
    if (!font.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\assets\\arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}
void Game::loadBackground(sf::RenderWindow& window) {
    // Create sprite to display the texture
    sf::Sprite background(texture);
    // Adjust the background to fit the window size
    resizeBackgroundImage(background, texture);

    // Draw the background to the window
    window.draw(background);
}

void Game::resizeBackgroundImage(sf::Sprite& background, const sf::Texture& texture) {
    // Get the original image size
    sf::Vector2u imageSize = texture.getSize();
    // Get the new window size
    sf::Vector2u windowSize = window.getSize();
    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
    // Use the smaller scale factor to maintain aspect ratio
    float scale = std::min(scaleX, scaleY);
    background.setScale(scale, scale);
    // Center the image
    sf::FloatRect spriteBounds = background.getGlobalBounds();
    background.setPosition(
        (windowSize.x - spriteBounds.width) / 2.f,
        (windowSize.y - spriteBounds.height) / 2.f
    );
}

void Game::renderNextAction() {
    if (currentState == gkQuestion || currentState == scienceQuestion || currentState == mathQuestion) {
        if (currentAnswerIndex != -1) { // Ensure an answer was selected
            const auto& q = questions[currentQuestionIndex];
            // Check if the answer is correct
            if (currentAnswerIndex == q.getCorrectAnswerIndex()) {
                playerScore++;  // Increment score for correct answer
            }
            else {
                WrongQuestions.push_back(q);
                WrongAnswers.push_back(q.getOptions()[currentAnswerIndex]);
            }
            // Move to the next question
            currentQuestionIndex++;
            currentAnswerIndex = -1; // Reset the answer index for the next question

            if (currentQuestionIndex >= questions.size()) {
                currentState = GAME_OVER; // End game if no more questions
            }
        }
    }
    else if (currentState == checkAnswer) {
            // Move to the next question
            currentQuestionIndex++;
            if (currentQuestionIndex >= WrongQuestions.size()) {
                currentState = GAME_OVER; // End game if no more questions
            }
    }
}

void Game::DisplayQuestions() {
    if (currentQuestionIndex < questions.size()) {
        const auto& q = questions[currentQuestionIndex];

        // Render question text
        Text questionText(font, q.getQuestion(), 30, { windowWidth / 2.f, windowHeight / 3.f }, sf::Color::White);
        questionText.draw(window);

        // Resize the vector if needed to match the number of options
        float yOffset = (windowHeight / 3.f) + 80.f;
        float optionPositionX = windowWidth / 3.f;

        // Clear existing option buttons if any
        for (auto button : optionButtons) {
            delete button;
        }
        optionButtons.clear();

        // Add new buttons for the current question options
        for (size_t i = 0; i < q.getOptions().size(); ++i) {
            optionButtons.push_back(new Button(font, q.getOptions()[i], sf::Vector2f(500.f, 100.f), sf::Vector2f(optionPositionX, yOffset), sf::Color::Black));
            yOffset += 100.f;  // Adjust position for the next button
        }

        // Render the option buttons
        for (auto& button : optionButtons) {
            button->draw(window);
            //button->deselect(); // Ensure no options are selected initially
        }

        // Render "Next" button
        Next->draw(window);
    }
}

void Game::stateTransition() {
    if (currentState == MENU) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\menu.jpg")) {
            std::cerr << "Error loading menu background!" << std::endl;
            return;
        }
        loadBackground(window);
        renderMenuState();
    }
    else if (currentState == CATEGORIES) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\categories.jpg")) {
            std::cerr << "Error loading categories background!" << std::endl;
            return;
        }
        loadBackground(window);
        renderCategoriesState();
    }
    else if (currentState == scienceQuestion) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\science.png")) {
            std::cerr << "Error loading science background!" << std::endl;
            return;
        }
        loadBackground(window);
        questions = Question::loadQuestions(filePath_Science);  // Load questions from file
        renderScienceQuestionState();
    }
    else if (currentState == mathQuestion) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\math.jpg")) {
            std::cerr << "Error loading math background!" << std::endl;
            return;
        }
        loadBackground(window);
        questions = Question::loadQuestions(filePath_Math);  // Load questions from file
        renderMathQuestionState();
    }
    else if (currentState == gkQuestion) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\gk.jpg")) {
            std::cerr << "Error loading Gk background!" << std::endl;
            return;
        }
        loadBackground(window);
        questions = Question::loadQuestions(filePath_Gk);  // Load questions from file
        renderGkQuestionState();
    }
    else if (currentState == GAME_OVER) {
        if (!texture.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\Practice\\gameOver.jpg")) {
            std::cerr << "Error loading gameOver background!" << std::endl;
            return;
        }
        loadBackground(window);
        renderGameOverState();
    }
    else if (currentState == checkAnswer) {
        renderWrongQuestionState();
    }
    

}

void Game::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Get the buttons and actions for the current state
        auto buttonActionMap = getButtonActionMap();
        
        // Check which button is clicked and execute the associated action
        for (const auto& pair : buttonActionMap) {
            Button* button = pair.first;
            std::function<void()> action = pair.second;

            if (button->isClicked(mousePos)) {

                action(); // Execute the action associated with the button
                break;    // Exit once a button is clicked
            }
        }

    }
}

std::vector<std::pair<Button*, std::function<void()>>> Game::getButtonActionMap() {
    std::vector<std::pair<Button*, std::function<void()>>> buttonActions;

    // Populate the buttons and their actions based on the current state
    if (currentState == MENU) {
        buttonActions.emplace_back(playButton, [this]() {
            currentState = CATEGORIES;
            });
    }
    else if (currentState == CATEGORIES) {
        buttonActions.emplace_back(scienceButton, [this]() {
            currentState = scienceQuestion;
            });
        buttonActions.emplace_back(mathButton, [this]() {
            currentState = mathQuestion;
            });
        buttonActions.emplace_back(gkButton, [this]() {
            currentState = gkQuestion;
            });
    }
    else if (currentState == scienceQuestion) {
        // Define "Next" button action
        buttonActions.emplace_back(Next, [this]() {
            renderNextAction();
        });
        // Handle option selection
        for (int i = 0; i < optionButtons.size(); ++i) {
            buttonActions.emplace_back(optionButtons[i], [this,i]() {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && optionButtons[i]->isClicked(sf::Mouse::getPosition(window))) {
                    // Deselect all other buttons
                    for (auto& button : optionButtons) {
                        button->deselect();
                    }
                    // Select the clicked button
                    optionButtons[i]->select(window);
                    currentAnswerIndex = i; // Update the currently selected answer index
                }
            });
        }
    }
    else if (currentState == mathQuestion) { 
        // Define "Next" button action
        buttonActions.emplace_back(Next, [this]() {
            renderNextAction();
            });

        // Handle option selection
        for (size_t i = 0; i < optionButtons.size(); ++i) {
            buttonActions.emplace_back(optionButtons[i], [this, i]() {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && optionButtons[i]->isClicked(sf::Mouse::getPosition(window))) {
                    // Deselect all other buttons
                    for (auto& button : optionButtons) {
                        button->deselect();
                    }
                    // Select the clicked button
                    optionButtons[i]->select(window);
                    currentAnswerIndex = i; // Update the currently selected answer index
                }
                });
        }
    }
    else if (currentState == gkQuestion) {
        // Define "Next" button action
        buttonActions.emplace_back(Next, [this]() {
            renderNextAction();
            });

        // Handle option selection
        for (size_t i = 0; i < optionButtons.size(); ++i) {
            buttonActions.emplace_back(optionButtons[i], [this, i]() {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && optionButtons[i]->isClicked(sf::Mouse::getPosition(window))) {
                    // Deselect all other buttons
                    for (auto& button : optionButtons) {
                        button->deselect();
                    }
                    // Select the clicked button
                    optionButtons[i]->select(window);
                    currentAnswerIndex = i; // Update the currently selected answer index
                }
                });
        }
    }
    else if (currentState == GAME_OVER) {
        buttonActions.emplace_back(Exit, [this]() {
            window.close();
        });
        buttonActions.emplace_back(Menu, [this]() {
            currentState = CATEGORIES;
            currentQuestionIndex = 0;
            playerScore = 0;
            WrongQuestions.clear();
            WrongAnswers.clear();
        });
        buttonActions.emplace_back(CheckAsnwers, [this]() {
            currentState = checkAnswer;
            currentQuestionIndex = 0;

        });
    }
    else if (currentState == checkAnswer){
        // Define "Next" button action
        buttonActions.emplace_back(Next, [this]() {
            renderNextAction();
        });
    }
    return buttonActions;
}

void Game::renderMenuState() {
    playButton->draw(window);
    sf::Font quizfont;
    if (!quizfont.loadFromFile("C:\\Users\\kunal\\source\\repos\\Practice\\assets\\Quiz.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    Text quiz(quizfont, "Quiz Game", 60, { windowWidth / 2.f, windowHeight / 3.f }, sf::Color::Black);
    quiz.draw(window);
}

void Game::renderCategoriesState() {
    scienceButton->draw(window);
    mathButton->draw(window);
    gkButton->draw(window);
}

void Game::renderScienceQuestionState() {
    DisplayQuestions();
}

void Game::renderMathQuestionState() {
    DisplayQuestions();
}

void Game::renderGkQuestionState() {
    DisplayQuestions();
}

void Game::renderGameOverState() {
    std::string scoreText = "Your score: " + std::to_string(playerScore);
    Text gameOverText(font, "Game Over!\n" + scoreText, 100, { windowWidth / 2.f, windowHeight / 2.f }, sf::Color::Red);
    gameOverText.draw(window);
    Menu->draw(window);
    Exit->draw(window);
    CheckAsnwers->draw(window);
}

void Game::renderWrongQuestionState() {
    if (currentQuestionIndex < WrongQuestions.size()) {
        const auto& q = WrongQuestions[currentQuestionIndex];
        std::string wronganswer = WrongAnswers[currentQuestionIndex];

        // Render question text
        Text questionText(font, q.getQuestion(), 30, { windowWidth / 2.f, windowHeight / 3.f }, sf::Color::White);
        questionText.draw(window);

        // Resize the vector if needed to match the number of options
        float yOffset = (windowHeight / 3.f) + 80.f;
        float optionPositionX = windowWidth / 3.f;

        // Clear existing option buttons if any
        for (auto button : textButtons) {
            delete button;
        }
        textButtons.clear();

        
        // Add new text the current question options
        for (size_t i = 0; i < q.getOptions().size(); ++i) {
            if (q.getOptions()[i] == wronganswer) {
                textButtons.push_back(new Text(font, q.getOptions()[i], 30, sf::Vector2f(optionPositionX, yOffset), sf::Color::Red));
            }
            else if (i == q.getCorrectAnswerIndex()) {
                textButtons.push_back(new Text(font, q.getOptions()[i], 30, sf::Vector2f(optionPositionX, yOffset), sf::Color::Green));
            }
            else
                    textButtons.push_back(new Text(font, q.getOptions()[i], 30, sf::Vector2f(optionPositionX, yOffset), sf::Color::White));

            yOffset += 100.f;  // Adjust position for the next button
        }
        
        // Render the option text
        for (auto& button : textButtons) {
            button->draw(window);
        }

        // Render "Next" button
        Next->draw(window);
    }
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleEvents(event); // Unified event handling for all states
        }

        window.clear();
        stateTransition();
        window.display();

    }
}
