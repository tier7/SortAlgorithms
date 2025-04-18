#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <utility>
#include "ISort.h"

enum class pivotType {
    LEFT,
    RIGHT,
    MID,
    RANDOM
};

template<typename T>
class QuickSort : public ISort<T> {
public:
    QuickSort(pivotType pvtType = pivotType::MID)
        : pvt(pvtType) {}

    void sort(T* tab, int n) override {
        quickSortRecursion(tab, 0, n - 1);
    }

private:
    pivotType pvt;

    void quickSortRecursion(T* tab, int left, int right) {
        if (left >= right) return;

        int i = left - 1;
        int j = right + 1;

        T pivotVal;
        switch (pvt) {
            case pivotType::LEFT:
                pivotVal = tab[left];
            break;
            case pivotType::RIGHT:
                pivotVal = tab[right];
            break;
            case pivotType::MID:
                pivotVal = tab[(left + right) / 2];
            break;
            case pivotType::RANDOM:
                default:
                    pivotVal = tab[left + rand() % (right - left + 1)];
            break;
        }

        while (true) {
            do { i++; } while (tab[i] < pivotVal);
            do { j--; } while (tab[j] > pivotVal);
            if (i <= j) {
                std::swap(tab[i], tab[j]);
            } else {
                break;
            }
        }
        if (j > left)
            quickSortRecursion(tab, left, j);
        if (i < right)
            quickSortRecursion(tab, i, right);
    }
};

#endif // QUICKSORT_H