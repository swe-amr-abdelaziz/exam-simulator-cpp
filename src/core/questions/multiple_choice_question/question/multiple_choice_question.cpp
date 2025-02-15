#include <constants/messages.h>
#include <multiple_choice_question/question/multiple_choice_question.h>
#include <multiple_choice_question/question/validator/multiple_choice_question.validator.h>
#include <utils/utils.h>

MultipleChoiceQuestion::MultipleChoiceQuestion(std::string text,
                                               std::unique_ptr<MultipleChoiceAnswer> correctAnswer,
                                               std::unique_ptr<MultipleChoiceAnswer> studentAnswer,
                                               std::vector<std::string> choices)
    : Question<MultipleChoiceAnswer>(
          MultipleChoiceQuestionValidator::validateText(text), Enums::QuestionType::MCQ,
          MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer), choices),
          MultipleChoiceQuestionValidator::validateStudentAnswer(std::move(studentAnswer), choices)),
      choices(MultipleChoiceQuestionValidator::validateChoices(choices)) {}

bool MultipleChoiceQuestion::isCorrect() {
    if (!this->studentAnswer->getDegree().has_value()) {
        this->calculateStudentDegree();
    }
    return this->studentAnswer->getDegree().value() == this->correctAnswer->getDegree().value();
}

void MultipleChoiceQuestion::ask(const unsigned short& index) {
    auto [questionBody, validAnswers] = this->getQuestionTextWithValidAnswers(index);
    auto answer = Utils::askQuestion(questionBody, validAnswers);
    this->studentAnswer->setValue(Utils::convertChoiceCharToIndex(answer[0]));
}

void MultipleChoiceQuestion::printWithCorrection(const unsigned short& index) {
    if (this->isCorrect()) {
        throw std::runtime_error(Messages::METHOD_CANNOT_BE_CALLED_WITH_CORRECT_ANSWER);
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
        if (!correctAnswerUpdated && this->correctAnswer->getValue().value() == indexArray[i]) {
            this->correctAnswer->setValue(static_cast<uint8_t>(i));
            correctAnswerUpdated = true;
        }
    }
}

void MultipleChoiceQuestion::setText(const std::string& text) {
    this->text = MultipleChoiceQuestionValidator::validateText(text);
}

std::string MultipleChoiceQuestion::getText() const {
    return this->text;
}

void MultipleChoiceQuestion::setCorrectAnswer(std::unique_ptr<MultipleChoiceAnswer> correctAnswer) {
    this->correctAnswer =
        MultipleChoiceQuestionValidator::validateCorrectAnswer(std::move(correctAnswer), this->choices);
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceQuestion::getCorrectAnswer() const {
    return this->correctAnswer->clone();
}

void MultipleChoiceQuestion::setStudentAnswer(std::unique_ptr<MultipleChoiceAnswer> studentAnswer) {
    this->studentAnswer =
        MultipleChoiceQuestionValidator::validateStudentAnswer(std::move(studentAnswer), this->choices);
}

std::unique_ptr<MultipleChoiceAnswer> MultipleChoiceQuestion::getStudentAnswer() const {
    return this->studentAnswer->clone();
}

void MultipleChoiceQuestion::setChoices(const std::vector<std::string>& choices) {
    this->choices = MultipleChoiceQuestionValidator::validateChoices(choices);
}

std::vector<std::string> MultipleChoiceQuestion::getChoices() const {
    return this->choices;
}

std::unique_ptr<MultipleChoiceQuestion> MultipleChoiceQuestion::clone() const {
    return std::make_unique<MultipleChoiceQuestion>(this->text, this->correctAnswer->clone(),
                                                    this->studentAnswer->clone(), this->choices);
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
            if (static_cast<int>(i) == this->correctAnswer->getValue().value()) {
                oss << "  " << Messages::CORRECT_ANSWER_EMOJI;
            }
            if (static_cast<int>(i) == this->studentAnswer->getValue().value()) {
                oss << "  " << Messages::WRONG_ANSWER_EMOJI;
            }
        }
    }

    if (withCorrection) {
        oss << "\n\n" << Messages::PRESS_ENTER_PROMPT;
    }
    return std::make_tuple(oss.str(), vaildAnswers);
}

void MultipleChoiceQuestion::calculateStudentDegree() {
    auto studentAnswer = this->studentAnswer->getValue();
    double studentDegree =
        studentAnswer.has_value() && studentAnswer.value() == this->correctAnswer->getValue().value()
            ? this->correctAnswer->getDegree().value()
            : 0;
    this->studentAnswer->setDegree(studentDegree);
}
