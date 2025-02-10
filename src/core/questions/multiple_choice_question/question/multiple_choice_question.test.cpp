#include "builder/multiple_choice_question.builder.h"

// Important Note: use clone() to get a new instance of the QUESTION to prevent modifying the
// original one

// Static const variables
static const auto CORRECT_ANSWER = MultipleChoiceAnswerBuilder::create()
                                       .setText(MCQ_CORRECT_ANSWER_TEXT)
                                       .setDegree(MCQ_CORRECT_ANSWER_DEGREE)
                                       .build();
static const auto STUDENT_ANSWER = MultipleChoiceAnswerBuilder::create().build();
static const uint8_t TEXT_NEW = 1;
static const double DEGREE_NEW = 5.0;
static const auto QUESTION = MultipleChoiceQuestionBuilder::create()
                                 .setText(MCQ_TEXT)
                                 .setCorrectAnswer(std::move(CORRECT_ANSWER->clone()))
                                 .setStudentAnswer(std::move(STUDENT_ANSWER->clone()))
                                 .setChoices(CHOICES)
                                 .build();
