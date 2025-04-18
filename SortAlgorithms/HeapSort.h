//
// Created by wiktor on 03.04.2025.
//

#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "ISort.h"


template<typename T>
class HeapSort : public ISort<T> {
    void heapify(T* tab, int n, int i) {
        int largest = i;
        int left = (i*2)+1;
        int right =(i*2)+2;
        if (left < n && tab[left] > tab[largest]) {
            largest = left;
        }
        if (right < n && tab[right] > tab[largest]) {
            largest = right;
        }
        if (largest != i) {
            T temp = tab[i];
            tab[i] = tab[largest];
            tab[largest] = temp;
            heapify(tab, n, largest);
        }
    }

public:
    void sort(T* tab, int n) override {
        //BUDOWANIE KOPCA
        for (int i = (n/2)-1; i >= 0; i-- ) {
            heapify(tab, n, i);
        }
        //SORTOWANIE PRZEZ KOPCOWANIE
        for (int i = n-1; i > 0; i--) {
            T temp = tab[0];
            tab[0] = tab[i];
            tab[i] = temp;
            heapify(tab, i, 0);
        }
    }
};



#endif //HEAPSORT_H
