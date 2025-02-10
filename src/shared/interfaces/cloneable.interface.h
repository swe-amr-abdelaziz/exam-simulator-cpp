#ifndef ICLONEABLE_H
#define ICLONEABLE_H

#include <memory>

template <class T>
class ICloneable {
public:
    virtual ~ICloneable() = default;
    virtual std::unique_ptr<T> clone() const = 0;
};

#endif // ICLONEABLE_H
