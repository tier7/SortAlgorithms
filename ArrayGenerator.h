#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <cstdlib>
#include <ctime>
#include <type_traits>

enum class arrayType  {
    FULLRANDOM,       // cala tablica losowa
    ASCENDING,        // posortowana rosnaco
    DESCENDING,       // posortowana malejaco
    PARTLYSORTEDLOW,  // okolo 33% tablicy posortowane
    PARTLYSORTEDHIGH  // okolo 66% tablicy posortowane
};


inline int randomValue(int minVal, int maxVal) {
    return minVal + rand() % (maxVal - minVal + 1);
}

inline double randomValue(double minVal, double maxVal) {
    double fraction = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1.0);
    return minVal + fraction * (maxVal - minVal);
}


template<typename T>
T* arrayGenerator(int n, T minVal, T maxVal, arrayType type) {
    T* array = new T[n];

    int startIndex = 0;

    if (type == arrayType::PARTLYSORTEDLOW) {
        for (int i = 0; i < n/3; i++) {
            array[i] = static_cast<T>(1);
        }
        startIndex = n/3;
    }

    else if (type == arrayType::PARTLYSORTEDHIGH) {
        int limit = static_cast<int>(0.66 * n);
        for (int i = 0; i < limit; i++) {
            array[i] = static_cast<T>(1);
        }
        startIndex = limit;
    }

    else if (type == arrayType::ASCENDING) {
        double step = static_cast<double>(maxVal - minVal) / static_cast<double>(n - 1);
        for (int i = 0; i < n; i++) {
            double value = static_cast<double>(minVal) + i * step;
            array[i] = static_cast<T>(value);
        }
        return array;
    }

    else if (type == arrayType::DESCENDING) {
        double step = static_cast<double>(maxVal - minVal) / static_cast<double>(n - 1);
        for (int i = 0; i < n; i++) {
            double val = static_cast<double>(maxVal) - i * step;
            array[i] = static_cast<T>(val);
        }
        return array;
    }

    for (int i = startIndex; i < n; i++) {
        if constexpr (std::is_same_v<T, int>) {
            array[i] = randomValue((int)minVal, (int)maxVal);
        } else {
            array[i] = static_cast<T>(
                randomValue(static_cast<double>(minVal), static_cast<double>(maxVal))
            );
        }
    }

    return array;
}

#endif //ARRAYGENERATOR_H
