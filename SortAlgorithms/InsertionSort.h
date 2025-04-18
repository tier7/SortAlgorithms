
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include "ISort.h"
#include "utility"


template<typename T>
class InsertionSort : public ISort<T> {
public:
    void sort(T* tab, int n) override {
        int i = 1;
        while (i < n) {
            int j = i;
            while (j > 0 && tab[j - 1] > tab[j])
            {
                std::swap(tab[j], tab[j - 1]);
                j--;
            }
            i++;
        }
    }
};


#endif //INSERTIONSORT_H
