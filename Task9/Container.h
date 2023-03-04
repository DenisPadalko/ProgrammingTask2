#pragma once
#include <functional>
#include <map>
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
    const vector<char> ReadActionsFromFile();
    const T& Calculate() const;
private:
    unique_ptr<T[]> ArrayOfData;
    int SizeOfArray;
    vector<char> Actions;
};

template <typename T>
class MapOfActions
{
public:
    MapOfActions(char InAction);
    void operator()(T& LeftOperator, const T& RightOperator);
private:
    char Operation;
    map<char, function<T(T, T)>> Actions;
};