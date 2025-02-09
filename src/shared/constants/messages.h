#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

namespace Messages {

const std::string CHOICES_CANNOT_BE_EMPTY = "Choices cannot be empty strings";
const std::string CHOICES_CANNOT_BE_VERY_LONG = "Choices cannot be longer than 500 characters";
const std::string CHOICES_CANNOT_HAVE_DUPLICATES = "Choices cannot have duplicate elements";
const std::string INVALID_CHAR_INDEX = "Invalid index, must be between 0 and 25";
const std::string INVALID_CHOICE_CHAR =
    "Invalid choice character, must be between A and Z (case insensitive)";
const std::string INVALID_DEGREE = "Degree must be greater than or equal to zero";
const std::string INVALID_MCQ_ANSWER = "Invalid answer. Please choose from: ";
const std::string INVALID_MCQ_ANSWER_VALUE = "Answer text must be one of the provided choices";
const std::string INVALID_MCQ_CHOICES_RANGE = "Choices must be between 3 and 5 elements";
const std::string INVALID_RUN_MODE = "Invalid run mode";
const std::string QUESTION_TEXT_CANNOT_BE_EMPTY = "The question text cannot be empty";
const std::string QUESTION_TEXT_CANNOT_BE_VERY_LONG =
    "The question text cannot be longer than 500 characters";
const std::string SIZE_GT_ZERO = "Size must be greater than zero";

} // namespace Messages

#endif // MESSAGES_H
