#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include "Timer.h"
#include "SortAlgorithms/ISort.h"
#include "ArrayGenerator.h"
#include "IsSorted.h"


template <typename T>
class Test {
public:
    long long algorithmTest(ISort<T>* sort, std::string algorithmName,
                            int n, T minVal, T maxVal, int reps, arrayType tabtype);


    void allAlgorithmTest(std::vector<std::pair<ISort<T>*, std::string>>& algs,
                          int n, T minVal, T maxVal, int reps, arrayType tabtype);


    void correctnessTest(ISort<T>* sorter, std::string algname, const std::string& filename);
};

#endif // TEST_H
