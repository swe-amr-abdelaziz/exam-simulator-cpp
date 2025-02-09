#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

namespace Messages {

const std::string INVALID_CHAR_INDEX = "Invalid index, must be between 0 and 25";
const std::string INVALID_CHOICE_CHAR =
    "Invalid choice character, must be between A and Z (case insensitive)";
const std::string INVALID_MCQ_ANSWER = "Invalid answer. Please choose from: ";
const std::string INVALID_RUN_MODE = "Invalid run mode";
const std::string SIZE_GT_ZERO = "Size must be greater than zero";

} // namespace Messages

#endif // MESSAGES_H
