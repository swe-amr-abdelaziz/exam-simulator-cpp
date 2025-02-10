#include "builder/multiple_choice_question.builder.h"

auto getCorrectAnswerInstance() {
    return MultipleChoiceAnswerBuilder::create()
        .setText(MCQ_CORRECT_ANSWER_TEXT)
        .setDegree(MCQ_CORRECT_ANSWER_DEGREE)
        .build();
}

auto getStudentAnswerInstance() {
    return MultipleChoiceAnswerBuilder::create().build();
}

auto getQestionInstance() {
    return MultipleChoiceQuestionBuilder::create()
        .setText(MCQ_TEXT)
        .setCorrectAnswer(std::move(getCorrectAnswerInstance()))
        .setStudentAnswer(std::move(getStudentAnswerInstance()))
        .setChoices(CHOICES)
        .build();
}

TEST(GetTextTest, should_return_question_text_when_text_is_set) {
    auto question = getQestionInstance();
    EXPECT_EQ(question->getText(), MCQ_TEXT);
}
