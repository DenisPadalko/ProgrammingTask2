#pragma once
#include <memory>
#include <vector>
#include "Iterator.h"

template <typename T>
class Container
{
public:
    Container();
    Container(const vector<T>& Data);
    Container(const unique_ptr<T[]>& Data, const int InSize);

    void LoadFromFile();
    void LoadFromConsole();
    const unique_ptr<T[]>& GetQuickSort();
    const unique_ptr<T[]>& GetUsualSort();

    Iterator<T>& Begin();
    Iterator<T>& End();
    Iterator<const T>& Begin() const;
    Iterator<const T>& End() const;

    const T& operator[](const int Index);
    
    int GetSize() const;
    const vector<T> GetVectorOfData() const;
private:
    unique_ptr<T[]> ArrayOfData;
    int SizeOfArray;
};