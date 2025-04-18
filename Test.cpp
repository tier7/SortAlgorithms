#include "Test.h"
#include "FileHandler.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "Utils.h"


template <typename T>
long long Test<T>::algorithmTest(ISort<T>* sort, std::string algorithmName,int n, T minVal, T maxVal, int reps, arrayType tabtype)
{
    long long total_time = 0;
    for (int i = 0; i < reps; i++) {
        T* tab = arrayGenerator<T>(n, minVal, maxVal, tabtype);
        Timer timer;
        timer.start();
        sort->sort(tab, n);
        long long work_time = timer.end();
        total_time += work_time;
        delete[] tab;
    }
    long long average_time = total_time / reps;
    return average_time;
}

template <typename T>
void Test<T>::allAlgorithmTest(std::vector<std::pair<ISort<T>*, std::string>>& algs,
                                int n, T minVal, T maxVal, int reps, arrayType tabtype)
{
    int algs_size = static_cast<int>(algs.size());
    std::vector<double> total_times(algs_size, 0LL);

    for (int j = 0; j < reps; j++) {
        T* base_tab = arrayGenerator<T>(n, minVal, maxVal, tabtype);

        for (int i = 0; i < algs_size; i++) {
            ISort<T>* sorter = algs[i].first;
            std::string algName = algs[i].second;

            T* copy_tab = new T[n];
            for (int k = 0; k < n; k++) {
                copy_tab[k] = base_tab[k];
            }

            Timer timer;
            timer.start();
            sorter->sort(copy_tab, n);
            double work_time = timer.end();

            total_times[i] += work_time;

            delete[] copy_tab;
        }

        delete[] base_tab;
    }
    for (int i = 0; i < algs_size; i++) {
        std::cout << algs[i].second << "," << (total_times[i] / reps) << "," << tabtypes(tabtype) << "," << n << "\n";
    }


}


template <typename T>
void Test<T>::correctnessTest(ISort<T>* sorter, std::string algname, const std::string& filename)
{
    int n;
    T* tab = FileHandler::readTabFromFile<T>(filename, n);
    if (!tab) {
        std::cout << "Error reading file: " << filename << std::endl;
        return;
    }
    std::cout << "Sort algorithm: " << algname << std::endl;
    std::cout << "Tab size: " << n << std::endl;
    std::cout << "BEFORE SORT: ";
    for (int i = 0; i < n; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << "\n";

    sorter->sort(tab, n);

    std::cout << "AFTER SORT: ";
    for (int i = 0; i < n; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << "\n";

    bool isOk = isSorted(tab, n);
    std::cout << "IS SORTED: " << (isOk ? "YES" : "NO") << std::endl;

    delete[] tab;
}

template class Test<int>;
template class Test<float>;
template class Test<double>;

