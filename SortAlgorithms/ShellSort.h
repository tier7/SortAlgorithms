#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "ISort.h"
enum class shellFormula {
    SHELL,
    KNUTH,
};
template<typename T>
class ShellSort : public ISort<T> {
    shellFormula gap;
public:
    ShellSort(shellFormula f) : gap(f) {}
    void sort(T* tab, int n) {
        if (gap == shellFormula::SHELL) {
            for (int h = n/2; h>0; h/=2) {
                for (int i = h; i<n; i++) {
                    T tmp = tab[i];
                    int j = i;
                    while (j >= h && tab[j - h] > tmp)
                    {
                        tab[j] = tab[j - h];
                        j-=h;
                    }
                    tab[j] = tmp;
                }
            }
        }
        else if (gap == shellFormula::KNUTH) {
            int h = 1;
            while (h < n/3) {
                h = 3*h + 1;
            }
            while (h>0) {
                for (int i = h; i<n; i++) {
                    T tmp = tab[i];
                    int j = i;
                    while (j >= h && tab[j - h] > tmp) {
                        tab[j] = tab[j - h];
                        j-=h;
                    }
                    tab[j] = tmp;
                }
                h = (h-1)/3;

            }
        }


    }
};

#endif //SHELLSORT_H
