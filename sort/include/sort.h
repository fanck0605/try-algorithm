#pragma once
#include <vector>
#include <algorithm>

template <typename DataType>
std::vector<DataType> insertSort(std::vector<DataType> toSort)
{
    toSort.push_back({});

    const auto rbegin = std::rbegin(toSort);
    const auto rend = std::rend(toSort);

    for (auto i = rbegin + 2; i != rend; ++i)
    {
        *rbegin = *i;
        for (auto j = i; *j > *(j - 1); --j)
        {
            std::iter_swap(j, j - 1);
        }
    }

    toSort.pop_back();

    return toSort;
}

template <typename DataType>
std::vector<DataType> bubbleSort(std::vector<DataType> toSort)
{
    const auto begin = toSort.begin();
    const auto end = toSort.end();

    for (auto i = begin; i != end; ++i)
    {
        bool swap = false;
        for (auto j = end - 1; j != i; --j)
        {
            if (*j < *(j - 1))
            {
                swap = true;
                std::iter_swap(j, j - 1);
            }
        }
        if (!swap)
            break;
    }

    return toSort;
}

template<typename Iterator>
Iterator quickSortPartition(Iterator begin, Iterator end)
{
    auto pivot = *begin;
    auto left = begin;
    auto right = end;

    while (left != right)
    {
        while (*--right >= pivot && right != left);

        *left = *right;

        while (right != left && *++left <= pivot);

        *right = *left;
    }

    *left = pivot;

    return left;
}

template <typename Iterator>
void quickSortHelper(Iterator begin, Iterator end)
{
    if (begin == end) return;
    if (begin + 1 == end) return;

    Iterator pivot = quickSortPartition(begin, end);
    quickSortHelper(begin, pivot);
    quickSortHelper(pivot + 1, end);
}

template <typename DataType>
std::vector<DataType> quickSort(std::vector<DataType> toSort)
{
    quickSortHelper(toSort.begin(), toSort.end());
    return toSort;
}

template <typename Iter>
void maxHeapify(Iter begin, Iter end, Iter start)
{
    const size_t sizeHalf = (end - begin) / 2;
    Iter parent = start;
    while (true) {
        size_t parentIndex = parent - begin;

        if (parentIndex >= sizeHalf) return; // parent is a leaf

        Iter largest = parent;

        Iter leftChild = begin + parentIndex * 2 + 1;
        if (*leftChild > *largest) // we must have a left child
        {
            largest = leftChild;
        }

        Iter rightChild = leftChild + 1;
        if (rightChild != end && *rightChild > *largest)
        {
            largest = rightChild;
        }

        if (largest == parent) return;

        std::iter_swap(largest, parent);
        parent = largest;
    }
}

template<typename Iter>
void buildMaxHeap(Iter begin, Iter end)
{
    auto length = end - begin;
    if (length < 2) return;

    Iter i = begin + length / 2 - 1;
    for (;;)
    {
        maxHeapify(begin, end, i);
        if (i == begin) return;
        --i; // to be optimized
    }
}

// the last element is the newly inserted
template <typename Iter>
void maxHeapify2(Iter begin, Iter last)
{
    Iter changed = last;
    while (changed != begin)
    {
        Iter parent = begin + (changed - begin - 1) / 2;
        if (*changed > *parent)
        {
            std::iter_swap(changed, parent);
            changed = parent;
        }
        else
        {
            break;
        }
    }
}

template<typename Iter>
void buildMaxHeap2(Iter begin, Iter end)
{
    auto length = end - begin;
    if (length < 2) return;

    for (auto i = begin + 1; i != end; i++)
    {
        maxHeapify2(begin, i);
    }
}

template <typename DataType>
std::vector<DataType> heapSort(std::vector<DataType> toSort)
{
    auto begin = toSort.begin();
    auto end = toSort.end();
    buildMaxHeap2(begin, end);

    for (auto i = end - 1; i != begin; --i)
    {
        std::iter_swap(begin, i);
        maxHeapify(begin, i, begin);
    }

    return toSort;
}

template <typename Iter>
void merge(Iter begin, Iter middle, Iter end)
{

    std::vector<typename std::iterator_traits<Iter>::value_type> temp{ begin, middle };

    auto leftIter = temp.begin();
    auto leftEnd = temp.end();
    auto rightIter = middle;
    auto rightEnd = end;

    auto resultIter = begin;

    while (leftIter < leftEnd && rightIter < rightEnd)
    {
        if (*leftIter < *rightIter)
        {
            *resultIter++ = *leftIter++;
        }
        else
        {
            *resultIter++ = *rightIter++;
        }
    }

    if (leftIter < leftEnd)
    {
        std::copy(leftIter, leftEnd, resultIter);
    }
}

template <typename Iter>
void mergeSortHelper(Iter begin, Iter end)
{
    if (begin == end) return;
    if (begin + 1 == end) return;

    auto length = end - begin;
    auto middle = begin + length / 2;

    mergeSortHelper(begin, middle);
    mergeSortHelper(middle, end);

    merge(begin, middle, end);
}

template <typename Data>
std::vector<Data> mergeSort(std::vector<Data> toSort)
{
    mergeSortHelper(toSort.begin(), toSort.end());
    return toSort;
}


template <typename Data>
std::vector<Data> shellSort(std::vector<Data> toSort)
{
    for (size_t step = toSort.size() / 2; step > 0; step /= 2)
    {
        for (size_t i = step; i < toSort.size(); i++)
        {
            for (size_t j = i; j >= step && toSort[j] < toSort[j - step]; j -= step)
            {
                std::swap(toSort[j], toSort[j - step]);
            }
        }
    }

    return toSort;
}
