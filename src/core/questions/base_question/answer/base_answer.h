#ifndef BASE_ANSWER_H
#define BASE_ANSWER_H

#include <optional>

template <class T, class U>
class Answer {
public:
    virtual ~Answer() = default;
    virtual void setValue(const T& value) = 0;
    virtual std::optional<T> getValue() = 0;
    virtual void setDegree(const U& degree) = 0;
    virtual std::optional<U> getDegree() = 0;

protected:
    std::optional<T> value = std::nullopt;
    std::optional<U> degree = std::nullopt;
};

#endif // BASE_ANSWER_H
