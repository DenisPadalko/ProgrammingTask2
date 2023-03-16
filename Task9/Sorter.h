#pragma once
#include <functional>
#include <vector>

using namespace std;

template <typename T>
class Sorter
{
public:
    using PredicateType = function<bool(const T& left, const T& right)>;
    virtual void Sort(vector<T>& DataToSort) const = 0;
    virtual void SortWithPredicate(vector<T>& DataToSort, const Sorter<T>::PredicateType& Predicate) const = 0;
};

template <typename T>
class QuickSorter : public Sorter<T>
{
public:
    virtual void Sort(vector<T>& DataToSort) const override;
    virtual void SortWithPredicate(vector<T>& DataToSort, const typename Sorter<T>::PredicateType& Predicate) const override;
private:
    void Sort_Internal(vector<T>& DataToSort, const int Start, const int End) const;
    void SortWithPredicate_Internal(vector<T>& DataToSort, const int Start, const int End,
        const typename Sorter<T>::PredicateType& Predicate) const;
    static int Partition(vector<T>& DataToSort, const int Start, const int End);
    static int PartitionWithPredicate(vector<T>& DataToSort, const int Start, const int End,
        const typename Sorter<T>::PredicateType& Predicate);
};

template <typename T>
class UsualSorter : public Sorter<T>
{
public:
    virtual void Sort(vector<T>& DataToSort) const override;
    virtual void SortWithPredicate(vector<T>& DataToSort, const Sorter<T>::PredicateType& Predicate) const override;
};