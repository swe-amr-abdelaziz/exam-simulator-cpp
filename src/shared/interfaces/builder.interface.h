#ifndef IBUILDER_H
#define IBUILDER_H

template <class T>
class IBuilder {
public:
    virtual ~IBuilder() = default;
    virtual T build() = 0;
};

#endif // IBUILDER_H
