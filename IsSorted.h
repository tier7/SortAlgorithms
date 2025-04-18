
#ifndef ISSORTED_H
#define ISSORTED_H
#include <utility>

template <typename T>
bool isSorted(T tab, int n) {
    for (int i=n-1; i>0; i--) {
        if (tab[i] < tab[i-1]) {
            return false;
        }
    }
    return true;
};



#endif //ISSORTED_H
