#include "Container.h"
#include "Sorter.cpp"
#include "Loader.h"
#include "Exceptions.h"
#include <sstream>

using namespace std;

template <typename T>
Container<T>::Container() = default;


template <typename T>
Container<T>::Container(const vector<T>& Data) : ArrayOfData(new T[Data.size()]), SizeOfArray(Data.size())
{
    copy(Data.begin(), Data.end(), ArrayOfData.get());
}

template <typename T>
Container<T>::Container(const unique_ptr<T[]>& Data, const int InSize) : ArrayOfData(new T[InSize]), SizeOfArray(InSize)
{
    copy(Data.get(), Data.get() + SizeOfArray, ArrayOfData.get());
}

template <typename T>
const T ConvertFromStringToSomeType(const string& Str)
{
    T Value;
    istringstream Stream(Str);
    Stream >> Value;
    return Value;
}

template <typename T>
void Container<T>::LoadFromFile()
{
    vector<string> DataFromFile;
    try
    {
        FileLoader Loader;
        DataFromFile = Loader.Load();
    }
    catch (const CannotOpenTheFileException& Ex)
    {
        cout << Ex.GetMessage() << endl;
    }
    unique_ptr<T[]> Temp(new T[SizeOfArray]);
    int TempSize = SizeOfArray;
    move(ArrayOfData.get(), ArrayOfData.get() + SizeOfArray, Temp.get()); 
    SizeOfArray += DataFromFile.size();
    ArrayOfData.reset(new T[SizeOfArray]);
    move(Temp.get(), Temp.get() + TempSize, ArrayOfData.get());
    for(int i = 0; i < DataFromFile.size(); ++i)
    {
        ArrayOfData[TempSize + i] = ConvertFromStringToSomeType<T>(DataFromFile[i]);
    }
}

template <typename T>
void Container<T>::LoadFromConsole()
{
    ConsoleLoader Loader;
    vector<string> DataFromConsole = Loader.Load();
    unique_ptr<T[]> Temp(new T[SizeOfArray]);
    int TempSize = SizeOfArray;
    move(ArrayOfData.get(), ArrayOfData.get() + SizeOfArray, Temp.get()); 
    SizeOfArray += DataFromConsole.size();
    ArrayOfData.reset(new T[SizeOfArray]);
    move(Temp.get(), Temp.get() + TempSize, ArrayOfData.get()); 
    for(int i = 0; i < DataFromConsole.size(); ++i)
    {
        ArrayOfData[TempSize + i] = ConvertFromStringToSomeType<T>(DataFromConsole[i]);
    }
}

template <typename T>
const unique_ptr<T[]>& Container<T>::GetQuickSort()
{
    QuickSorter<T> Sorter;
    vector<T> Vec = GetVectorOfData();
    Sorter.Sort(Vec);
    copy(Vec.begin(), Vec.end(), ArrayOfData.get());
    return ArrayOfData;
}

template <typename T>
const unique_ptr<T[]>& Container<T>::GetUsualSort()
{
    UsualSorter<T> Sorter;
    vector<T> Vec = GetVectorOfData();
    Sorter.Sort(Vec);
    copy(Vec.begin(), Vec.end(), ArrayOfData.get());
    return ArrayOfData;
}

template <typename T>
Iterator<T>& Container<T>::Begin()
{
    return Iterator<T>(ArrayOfData);
}

template <typename T>
Iterator<T>& Container<T>::End()
{
    return Iterator<T>(ArrayOfData + SizeOfArray);
}

template <typename T>
Iterator<const T>& Container<T>::Begin() const
{
    return Iterator<const T>(ArrayOfData);
}

template <typename T>
Iterator<const T>& Container<T>::End() const
{
    return Iterator<const T>(ArrayOfData + SizeOfArray);
}

template <typename T>
const T& Container<T>::operator[](const int Index)
{
    return ArrayOfData.get()[Index];
}


template <typename T>
int Container<T>::GetSize() const
{
    return SizeOfArray;
}

template <typename T>
const vector<T> Container<T>::GetVectorOfData() const
{
    vector<T> Vec(make_move_iterator(ArrayOfData.get()), make_move_iterator(ArrayOfData.get() + SizeOfArray));
    return Vec;
}