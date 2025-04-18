#include <iostream>
#include <vector>
#include <string>

#include "FileHandler.h"
#include "SortAlgorithms/InsertionSort.h"
#include "SortAlgorithms/HeapSort.h"
#include "SortAlgorithms/QuickSort.h"
#include "SortAlgorithms/ShellSort.h"
#include "Test.h"
#include "time.h"


void runAlgTest() {
    int reps = 100;
    int minVal = 1;
    int maxVal = 1000;

    Test<int> testInt;
    Test<float> testFloat;
    Test<double> testDouble;


    std::vector<int> standardSizes  = {20000,40000,60000,80000,100000,120000,140000};


    std::vector<arrayType> arrTypes = {
        arrayType::FULLRANDOM,
        arrayType::ASCENDING,
        arrayType::DESCENDING,
        arrayType::PARTLYSORTEDLOW,
        arrayType::PARTLYSORTEDHIGH
    };

    InsertionSort<int> insertion;
    QuickSort<int> quickMid(pivotType::MID);
    QuickSort<int> quickLeft(pivotType::LEFT);
    QuickSort<int> quickRight(pivotType::RIGHT);
    QuickSort<int> quickRand(pivotType::RANDOM);
    ShellSort<int> shellShell(shellFormula::SHELL);
    ShellSort<int> shellKnuth(shellFormula::KNUTH);
    HeapSort<int> heapInt;
    HeapSort<float> heapFloat;
    HeapSort<double> heapDouble;

    std::vector<std::pair<ISort<int>*, std::string>> algsInt = {
        {&insertion, "InsertionSort"},
        {&quickMid, "QuickSort(MID)"},
        {&quickLeft, "QuickSort(LEFT)"},
        {&quickRight, "QuickSort(RIGHT)"},
        {&quickRand, "QuickSort(RANDOM)"},
        {&shellShell, "ShellSort(SHELL)"},
        {&shellKnuth, "ShellSort(KNUTH)"},
        {&heapInt, "HeapSort<int>"}
    };

    std::vector<std::pair<ISort<float>*, std::string>> algsFloat = {
        {&heapFloat, "HeapSort<float>"}
    };

    std::vector<std::pair<ISort<double>*, std::string>> algsDouble = {
        {&heapDouble, "HeapSort<double>"}
    };

    for (auto tabtype : arrTypes) {
        for (int n : standardSizes) {
            testInt.allAlgorithmTest(algsInt, n, minVal, maxVal, reps, tabtype);
            testFloat.allAlgorithmTest(algsFloat, n, 1.0f, 1000.0f, reps, tabtype);
            testDouble.allAlgorithmTest(algsDouble, n, 1.0, 1000.0, reps, tabtype);
        }
    }

    }

int main() {
    srand(time(NULL));
        int choice;

        do {
            std::cout << "1. Tryb testowania z pliku\n";
            std::cout << "2. Uruchom testowanie algorytmow\n";
            std::cout << "3. Wyjscie\n";
            std::cout << "Wybor: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    FileHandler::testMode<int>("test.txt");
                    //w test.txt:
                    //file <nazwapliku> - wczytanie tablicy z pliku
                    //sort <nazwaalgorytmu> - sortowanie tablicy - shellShell/quickMid/insertion/heap...
                    //show - pokazanie wczytanej tablicy
                    //random <n> <minval> <maxvaL> - wygenerowanie tablicy n elementowej z warosciami od minval do maxval
                break;
                case 2:
                    runAlgTest();
                break;
                case 3:
                    break;
                default:
                    std::cout << "Nieprawidłowa opcja.\n";
            }

        } while (choice != 3);
        return 0;
    }

