#include "Iterator.h"

template <typename T>
Iterator<T>::Iterator(PointerType InPtr) : Ptr(InPtr)
{}

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
    ++Ptr;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    auto Iter = this;
    ++(*this);
    return Iter;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--()
{
    --Ptr;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int)
{
    auto Iter = this;
    --(*this);
    return Iter;
}

template <typename T>
typename Iterator<T>::ReferenceType Iterator<T>::operator[](const int Index)
{
    return *(Ptr + Index);
}

template <typename T>
typename Iterator<T>::PointerType Iterator<T>::operator->()
{
    return Ptr;
}

template <typename T>
typename Iterator<T>::ReferenceType Iterator<T>::operator*()
{
    return *Ptr;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator& OtherIterator)
{
    return Ptr == OtherIterator.Ptr;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& OtherIterator)
{
    return !(*this == OtherIterator);
}

template <typename T>
const typename Iterator<T>::ReferenceType Iterator<T>::First() const
{
    return Container<T>::Begin();
}

template <typename T>
const typename Iterator<T>::ReferenceType Iterator<T>::Next()
{
    return ++Ptr;
}