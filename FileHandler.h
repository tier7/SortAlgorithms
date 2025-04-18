#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "ArrayGenerator.h"
#include "IsSorted.h"
#include "SortAlgorithms/InsertionSort.h"
#include "SortAlgorithms/HeapSort.h"
#include "SortAlgorithms/QuickSort.h"
#include "SortAlgorithms/ShellSort.h"
#include "Test.h"

class FileHandler {
public:
    template<typename T>
    static T* readTabFromFile(const std::string& filename, int &size) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Can not open file: " << filename << std::endl;
            size = 0;
            return nullptr;
        }
        file >> size;
        if (size <= 0) {
            std::cerr << "Size of tab is 0" << std::endl;
            return nullptr;
        }
        T* array = new T[size];
        for (int i = 0; i < size; i++) {
            if (!(file >> array[i])) {
                std::cerr << "Reading data error" << std::endl;
                delete[] array;
                size = 0;
                return nullptr;
            }
        }
        file.close();
        return array;
    }

    template<typename T>
    static void saveResultsToFile(const std::string &filename,const std::string &algorithmName,int reps,T* arrayBefore,T* arrayAfter,int n,bool isCorrect,long long time)
    {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Cannot open results file: " << filename << std::endl;
            return;
        }
        file << "Algorithm name: " << algorithmName << std::endl
             << "Tab size: " << n << std::endl
             << "Repeat number: " << reps << std::endl
             << "Time[ms]: " << time << std::endl
             << "isSorted: " << (isCorrect ? "YES" : "NO") << std::endl;

        file << "TAB BEFORE SORT: ";
        for (int i = 0; i < n; i++) {
            file << arrayBefore[i] << " ";
        }
        file << "\n\n\n";

        file << "TAB AFTER SORT: ";
        for (int i = 0; i < n; i++) {
            file << arrayAfter[i] << " ";
        }
        file << "\n\n\n\n";
        file.close();
    }

    template<typename T>
    static void testMode(const std::string& configFile)
    {
        std::ifstream fin(configFile);
        if (!fin.is_open()) {
            std::cerr << "Can not open config file: " << configFile << std::endl;
            return;
        }

        T* lastTab = nullptr;
        int lastSize = 0;
        bool isTabCreated = false;

        static InsertionSort<T> insertion;
        static HeapSort<T> heap;
        static QuickSort<T> quickMid(pivotType::MID);
        static QuickSort<T> quickLeft(pivotType::LEFT);
        static QuickSort<T> quickRight(pivotType::RIGHT);
        static QuickSort<T> quickRand(pivotType::RANDOM);
        static ShellSort<T> shellShell(shellFormula::SHELL);
        static ShellSort<T> shellKnuth(shellFormula::KNUTH);


        auto algorithms = [&](const std::string& name) -> ISort<T>* {
            if (name=="insertion")   return &insertion;
            else if (name=="heap")   return &heap;
            else if (name=="quickMid")   return &quickMid;
            else if (name=="quickLeft")  return &quickLeft;
            else if (name=="quickRight") return &quickRight;
            else if (name=="quickRand")  return &quickRand;
            else if (name=="shellShell") return &shellShell;
            else if (name=="shellKnuth") return &shellKnuth;
            return nullptr;
        };

        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::string command;
            iss >> command;

            if (command == "file") {
                std::string fname;
                iss >> fname;
                if (fname.empty()) {
                    std::cout << "ERROR no filename\n";
                    continue;
                }
                int n;
                T* tab = FileHandler::readTabFromFile<T>(fname, n);
                if (!tab) {
                    std::cout << "ERROR can not read " << fname << "\n";
                } else {
                    if (isTabCreated && lastTab) {
                        delete[] lastTab;
                    }
                    lastTab = tab;
                    lastSize = n;
                    isTabCreated = true;
                }
            }
            else if (command == "random") {
                int n, minval, maxval;
                iss >> n >> minval >> maxval;
                if (iss.fail() || n <= 0) {
                    std::cout << "ERROR: generate n minVal maxVal\n";
                } else {
                    T* tab = arrayGenerator<T>(n, (T)minval, (T)maxval, arrayType::FULLRANDOM);
                    if (isTabCreated && lastTab) {
                        delete[] lastTab;
                    }
                    lastTab = tab;
                    lastSize = n;
                    isTabCreated = true;
                    std::cout<<"NEW TAB GENERATED \n";
                }
            }
            else if (command == "show") {
                if (!isTabCreated || !lastTab) {
                    std::cout << "No tab created\n";
                } else {
                    std::cout << "CURRENT TAB\n";
                    std::cout << "TAB SIZE: " << lastSize << std::endl;
                    for(int i=0; i<lastSize; i++){
                        std::cout << lastTab[i] << " ";
                    }
                    std::cout << "\n\n";
                }
            }
            else if (command == "sort") {
                std::string algName;
                iss >> algName;
                ISort<T>* sorter = algorithms(algName);
if (!sorter) {
    std::cout << "ERROR: unknown algorithm \"" << algName << "\"\n";
    continue;
}
                if (!isTabCreated || !lastTab) {
                    std::cout << "No tab created\n";
                } else {
                    T* copyTab = new T[lastSize];
                    for(int i=0; i<lastSize; i++){
                        copyTab[i] = lastTab[i];
                    }
                    ISort<T>* sorter = algorithms(algName);
                    if (!sorter) {
                        std::cout << "Unknown algorithm \"" << algName << "\"\n";
                        continue;
                    }
                    std::cout<<algName<<std::endl;
                    std::cout<<"SORTING...\n";
                    sorter->sort(copyTab, lastSize);
                    bool isOk = isSorted(copyTab, lastSize);
                    std::cout << "IS SORTED? " << (isOk ? "YES" : "NO") << "\n";
                    std::cout<<"TAB AFTER SORTING\n";
                    for(int i=0; i<lastSize; i++) {
                        std::cout << copyTab[i] << " ";
                    }
                    std::cout << "\n\n\n";
                    delete[] copyTab;
                }
            }
        }

        fin.close();

        if (isTabCreated && lastTab) {
            delete[] lastTab;
            lastTab = nullptr;
        }
    }
};

#endif // FILEHANDLER_H
