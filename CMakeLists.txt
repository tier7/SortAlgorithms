cmake_minimum_required(VERSION 3.30)
project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1073741824")



add_executable(SortAlgorithms main.cpp
        SortAlgorithms/insertionSort.h
        SortAlgorithms/heapSort.cpp
        SortAlgorithms/heapSort.h
        SortAlgorithms/quickSort.cpp
        SortAlgorithms/quickSort.h
        SortAlgorithms/shellSort.cpp
        SortAlgorithms/shellSort.h
        arrayGenerator.cpp
        arrayGenerator.h
        isSorted.cpp
        isSorted.h
        SortAlgorithms/iSort.cpp
        SortAlgorithms/iSort.h
        Timer.cpp
        Timer.h
        Test.cpp
        Test.h
        FileHandler.cpp
        FileHandler.h
        Utils.cpp
        Utils.h)
