//
// Created by wiktor on 05.04.2025.
//

#ifndef ISORT_H
#define ISORT_H



template<typename T>
class ISort {
public:
    virtual void sort(T* tab, int n) = 0;
    virtual ~ISort() {}
};


#endif //ISORT_H
