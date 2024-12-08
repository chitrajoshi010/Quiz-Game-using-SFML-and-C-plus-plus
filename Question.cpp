#include "Question.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Text.cpp"


// Constructor
Question::Question( const std::string& question,
    const std::vector<std::string>& options, int correctAnswerIndex)
    : question(question), options(options), correctAnswerIndex(correctAnswerIndex) {
}

// Getters
std::string Question::getQuestion() const {
    return question;
}

std::vector<std::string> Question::getOptions() const {
    return options;
}

int Question::getCorrectAnswerIndex() const {
    return correctAnswerIndex;
}

// Static function to load questions from CSV file
std::vector<Question> Question::loadQuestions(const std::string& filename) {
    std::vector<Question> questions;
    std::ifstream file(filename);  // Open CSV file

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return questions;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);  // To split the line
        std::string question, option1, option2, option3, option4;
        int correctAnswerIndex;

        // Split the line by the delimiter '|'
        std::getline(ss, question, '|');
        std::getline(ss, option1, '|');
        std::getline(ss, option2, '|');
        std::getline(ss, option3, '|');
        std::getline(ss, option4, '|');
        ss >> correctAnswerIndex;  // Read correct answer index

        // Create a Question object and add it to the vector
        Question q( question, { option1, option2, option3, option4 }, correctAnswerIndex);
        questions.push_back(q);
    }

    file.close();
    return questions;
}
