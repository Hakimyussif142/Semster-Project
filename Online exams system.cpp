#include <iostream>
#include <vector>
#include <string>
#include <ctime> // for time
#include <cstdlib> // for rand and srand
#include <iomanip> // for stream manipulations

// Question structure - base class
class Question {
public:
    std::string text;

    virtual void displayQuestion() = 0;
    virtual bool checkAnswer() = 0;
};

// MultipleChoiceQuestion derived from Question
class MultipleChoiceQuestion : public Question {
public:
    std::vector<std::string> choices;
    int correctChoice;

    void displayQuestion() override {
        std::cout << text << std::endl;
        for (int i = 0; i < choices.size(); ++i) {
            std::cout << i + 1 << ". " << choices[i] << std::endl;
        }
    }

    bool checkAnswer() override {
        int answer;
        std::cout << "Enter your choice: ";
        std::cin >> answer;
        return answer - 1 == correctChoice;
    }
};

// EssayQuestion derived from Question
class EssayQuestion : public Question {
public:
    std::string answer;

    void displayQuestion() override {
        std::cout << text << std::endl;
    }

    bool checkAnswer() override {
        std::string userAnswer;
        std::cout << "Enter your answer: " << std::endl;
        std::getline(std::cin >> std::ws, userAnswer);
        return userAnswer == answer;
    }
};

// Test structure
struct Test {
    std::string name;
    std::vector<Question*> questions;
};

// ExamResult structure
struct ExamResult {
    std::string testName;
    std::vector<bool> answers;
    double marksObtained;
    int timeSpent;
    std::string comment;
};

// Function to set up a test
Test setUpTest() {
    Test test;
    std::cout << "Enter your index number: ";
    std::getline(std::cin >> std::ws, test.name);

    // Multiple Choice Questions
    MultipleChoiceQuestion* mcq1 = new MultipleChoiceQuestion;
    mcq1->text = "What is the capital of France?";
    mcq1->choices = { "London", "Berlin", "Paris" };
    mcq1->correctChoice= 2;

    MultipleChoiceQuestion* mcq2 = new MultipleChoiceQuestion;
    mcq2->text = "What is the chemical symbol for gold?";
    mcq2->choices = { "Go", "Au", "Gd" };
    mcq2->correctChoice = 1;

     MultipleChoiceQuestion* mcq3 = new MultipleChoiceQuestion;
    mcq3->text = "Which planet is knowm as the red planet?";
    mcq3->choices = { "Earth", "Mars", "Venus" };
    mcq3->correctChoice = 1;

    test.questions.push_back(mcq1);
    test.questions.push_back(mcq2);
    test.questions.push_back(mcq3);

    // Essay Questions
    EssayQuestion* eq1 = new EssayQuestion;
    eq1->text = "Define Keywords as used in programming.";

    EssayQuestion* eq2 = new EssayQuestion;
    eq2->text = "Define Tokens as used in programming.";

    test.questions.push_back(eq1);
    test.questions.push_back(eq2);

    return test;
}

// Function to administer a test
ExamResult administerTest(const Test& test, int duration) {
    std::cout << "----- " << test.name << " -----" << std::endl;

    int totalQuestions = test.questions.size();
    std::vector<bool> answers(totalQuestions, false);
    time_t start = time(nullptr);

    for (int i = 0; i < totalQuestions; ++i) {
        std::cout << "Question " << i + 1 << ": ";
        test.questions[i]->displayQuestion();

        bool isCorrect = test.questions[i]->checkAnswer();
        answers[i] = isCorrect;
        std::cout << (isCorrect ? "Correct!" : "Incorrect!") << std::endl;
        std::cout << std::endl;
    }

    std::cout << "----- Test Completed -----" << std::endl;
    std::cout << std::endl;

    time_t end = time(nullptr);
    int timeSpent = static_cast<int>(end - start);

    std::string comment;
    std::cout << "Please enter your comments on the test results: ";
    std::getline(std::cin >> std::ws, comment);

    double marksObtained = 0.0;
    for (bool answer : answers
) {
        if (answer) {
            marksObtained += 1.0;
        }
    }

    return { test.name, answers, marksObtained, timeSpent, comment };
}// Function to analyze performance data
void analyzePerformance(const ExamResult& result) {
    int totalQuestions = result.answers.size();
    int score = 0;

    for (bool answer : result.answers) {
        if (answer) {
            ++score;
        }
    }double percentage = static_cast<double>(score) / totalQuestions * 100;std::cout << std::fixed << std::setprecision(2);

    std::cout << "----- Performance Analysis -----" << std::endl;
    std::cout << "Test Name: " << result.testName << std::endl;
    std::cout << "Total Questions: " << totalQuestions << std::endl;
    std::cout << "Total Correct Answers: " << score << std::endl;
    std::cout << "Percentage Correct: " << percentage << "%" << std::endl;
    std::cout << "Marks Obtained: " << result.marksObtained << std::endl;
    std::cout << "Time Spent: " << result.timeSpent << " seconds" << std::endl;
    std::cout << "Comments: " << result.comment << std::endl;
    std::cout << std::endl;
}

// Function to publish test results and print a summary
void publishResults(const std::vector<ExamResult>& results) {
    std::cout << "----- Published Test Results -----" << std::endl;
    for (const auto& result : results) {
        std::cout << "Test Name: " << result.testName << std::endl;
        std::cout << "Marks Obtained: " << result.marksObtained << std::endl;
        std::cout << "Time Spent: " << result.timeSpent << " seconds" << std::endl;
        std::cout << "Comments: " << result.comment << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Welcome to the Online Exam System!" << std::endl;
    std::cout << std::endl;

    std::srand(static_cast<unsigned int>(time(0))); // seed the random number generator

    int duration = 60; // Duration of each test in seconds

    std::vector<ExamResult> allResults;

    for (int testNumber = 1; testNumber <= 2; ++testNumber) {
        std::cout << "Test #" << testNumber << std::endl;
        std::cout << "------------" << std::endl;

        Test test = setUpTest();
        ExamResult result = administerTest(test, duration);
        analyzePerformance(result);
        allResults.push_back(result);

        std::cout << std::endl;
    }

    publishResults(allResults);

    std::cout << "Thank you for using the Online Exam System!" << std::endl;


    return 0;
}
