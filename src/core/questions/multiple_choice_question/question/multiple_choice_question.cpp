#include "multiple_choice_question.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(std::string text,
                                               std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                                               std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                                               std::vector<std::string> choices)
    : Question<MultipleChoiceAnswer>(text, Enums::QuestionType::MCQ, std::move(correctAnswer),
                                     std::move(studentAnswer)),
      choices(std::move(choices)) {}

MultipleChoiceQuestion::~MultipleChoiceQuestion() {}

bool MultipleChoiceQuestion::isCorrect() {
    if (!this->studentAnswer->getDegree().has_value()) {
        this->calculateStudentDegree();
    }
    return this->studentAnswer->getDegree().value() == this->correctAnswer->getDegree().value();
}

void MultipleChoiceQuestion::ask(const unsigned short& index) {
    auto [questionBody, validAnswers] = this->getQuestionTextWithValidAnswers(index);
    auto answer = Utils::askQuestion(questionBody, validAnswers);
    this->studentAnswer->setText(Utils::convertChoiceCharToIndex(answer[0]));
}

void MultipleChoiceQuestion::printWithCorrection(const unsigned short& index) {
    if (this->isCorrect()) {
        throw std::runtime_error(
            "This method should not be called when the student answer is correct");
    }
    auto [questionBody, validAnswers] = this->getQuestionTextWithValidAnswers(index, true);
    auto answer = Utils::askQuestion(questionBody);
}

void MultipleChoiceQuestion::shuffleAnswers() {
    auto indexArray = Utils::generateIndices(static_cast<unsigned short>(this->choices.size()), true);
    std::vector<std::string> originalChoices(this->choices);
    bool correctAnswerUpdated = false;
    for (size_t i = 0; i < this->choices.size(); ++i) {
        this->choices[i] = originalChoices[indexArray[i]];
        if (!correctAnswerUpdated && this->correctAnswer->getText().value() == indexArray[i]) {
            this->correctAnswer->setText(static_cast<uint8_t>(i));
            correctAnswerUpdated = true;
        }
    }
}

std::tuple<std::string, std::vector<std::string>>
    MultipleChoiceQuestion::getQuestionTextWithValidAnswers(const unsigned short& index, bool withCorrection) {
    std::vector<std::string> vaildAnswers(this->choices.size());
    std::ostringstream oss;

    int questionNumber = index + 1;
    oss << questionNumber << ". " << this->text << '\n';
    for (size_t i = 0; i < this->choices.size(); ++i) {
        char letter = Utils::convertIndexToChoiceChar(static_cast<uint8_t>(i));
        vaildAnswers[i] = static_cast<char>(std::toupper(letter));
        size_t indentWidth = std::to_string(questionNumber).length() + 2;
        if (i > 0) {
            oss << '\n';
        }
        oss << std::string(indentWidth, ' ') << letter << ". " << choices[i];

        if (withCorrection) {
            if (static_cast<int>(i) == this->correctAnswer->getText().value()) {
                oss << "  ✅";
            }
            if (static_cast<int>(i) == this->studentAnswer->getText().value()) {
                oss << "  ❌";
            }
        }
    }

    if (withCorrection) {
        oss << "\n\nPress enter to continue";
    }
    return std::make_tuple(oss.str(), vaildAnswers);
}

void MultipleChoiceQuestion::calculateStudentDegree() {
    double studentDegree = this->studentAnswer->getText().value() == this->correctAnswer->getText().value()
                               ? this->correctAnswer->getDegree().value()
                               : 0;
    this->studentAnswer->setDegree(studentDegree);
}
