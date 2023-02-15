#pragma once
#include <vector>
#include "Iterator.h"

template <typename T>
class Container
{
public:
    Container();
    Container(vector<T> Data);

    void LoadFromFile();
    void LoadFromConsole();
    const vector<T>& GetQuickSort();
    const vector<T>& GetUsualSort();

    Iterator<T>& Begin();
    Iterator<T>& End();
    Iterator<const T>& Begin() const;
    Iterator<const T>& End() const;

    const T& operator[](const int Index);
    
    int GetSize();
private:
    vector<T> VectorOfData;
};
