/**
 * \class Sorter
 *
 * \brief Sorter class.
 *
 * Implements quick sort algorithm.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __SORTER_H
#define __SORTER_H

#include <vector>

template <class T>
using Comparator = bool (*) (T, T);

template <typename T>
class Sorter
{
private:
    void swap(T* x1, T* x2);
    int partition(std::vector<T>& array, int leftIndex, int rightIndex, Comparator<T> pred);
    void quickSort(std::vector<T>& array, int leftIndex, int rightIndex, Comparator<T> pred);
public:
    void sort(std::vector<T>& data, Comparator<T> pred);
};

template <typename T>
void Sorter<T>::swap(T* x1, T* x2) 
{
    T tmp = *x1;
    *x1 = *x2;
    *x2 = tmp;
}

template <typename T>
int Sorter<T>::partition(std::vector<T>& array, int leftIndex, int rightIndex, Comparator<T> pred) 
{
    T pivotElement = array[rightIndex];
    int smallerElementIndex = (leftIndex - 1);

    for (int nextElementIndex = leftIndex; nextElementIndex < rightIndex; ++nextElementIndex) 
    {
        if (pred(array[nextElementIndex], pivotElement)) 
        {
            ++smallerElementIndex;
            swap(&array[smallerElementIndex], &array[nextElementIndex]);
        }
    }
    swap(&array[smallerElementIndex + 1], &array[rightIndex]);

    return (smallerElementIndex + 1);
}

template <typename T>
void Sorter<T>::quickSort(std::vector<T>& array, int leftIndex, int rightIndex, Comparator<T> pred) 
{
    if (leftIndex >= rightIndex) {
        return;
    }

    int partitionIndex = partition(array, leftIndex, rightIndex, pred);

    quickSort(array, leftIndex, partitionIndex - 1, pred);
    quickSort(array, partitionIndex + 1, rightIndex, pred);
}

template <typename T>
void Sorter<T>::sort(std::vector<T>& data, Comparator<T> pred)
{
    quickSort(data, 0, data.size() - 1, pred);
}

#endif