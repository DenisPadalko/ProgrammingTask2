#pragma once
#include <iterator>

using namespace std;
template<typename T>
class Container;

template<typename T>
class IIterator : public iterator<input_iterator_tag, T>
{
    virtual const T& First() const = 0;
    virtual const T& Next() = 0;
};

template <typename T>
class Iterator : public IIterator<T>
{
public:
    using  ValueType = T;
    using PointerType =  ValueType*;
    using ReferenceType =  ValueType&;
    
    Iterator(PointerType InPtr);

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    ReferenceType operator[](const int Index);
    PointerType operator->();
    ReferenceType operator*();
    bool operator==(const Iterator& OtherIterator);
    bool operator!=(const Iterator& OtherIterator);

    virtual const ReferenceType First() const override;
    virtual const ReferenceType Next() override;
private:
    PointerType Ptr;
};
