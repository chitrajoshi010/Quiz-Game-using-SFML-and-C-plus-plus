#pragma once
#include <string>
#include <vector>

class Question {
public:
    // Constructor
    Question(const std::string& question, const std::vector<std::string>& options, int correctAnswerIndex);

    // Getters
    std::string getQuestion() const;
    std::vector<std::string> getOptions() const;
    int getCorrectAnswerIndex() const;

    // Static function to load questions from a CSV file
    static std::vector<Question> loadQuestions(const std::string& filename);
     
    
private:
    std::string question;
    std::vector<std::string> options;
    int correctAnswerIndex;
};

