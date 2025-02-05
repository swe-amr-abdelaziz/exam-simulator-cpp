#ifndef IQUESTION_H
#define IQUESTION_H

#include <string>

class IQuestion {
public:
    virtual ~IQuestion() = default;
    virtual bool isCorrect() = 0;
    virtual std::string ask(const unsigned short& index) = 0;
    virtual void printWithCorrection(const unsigned short& index) = 0;
};

#endif // IQUESTION_H
