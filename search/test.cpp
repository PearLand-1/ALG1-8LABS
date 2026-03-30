#include <iostream>
#include <chrono>
#include <cstdlib>
#include "search.h"
#include "../MyLib.h"
#include "test.h"

using namespace std;

double TestSearchAlgorithm(int algorithmType, vector<int> arr_, int target)
{
    visualizationDelay = 0;

    vector<int> arrCopy = arr_;

    auto start = chrono::high_resolution_clock::now();
    switch (algorithmType)
    {
    case 9: LinearSearch(arrCopy, target, false); break;
    case 10: BinarySearch(arrCopy, target, false); break;
    case 1: JumpSearch(arrCopy, target, false); break;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

void RunTest2(int arraySize)
{
    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; i++)
        arr[i] = rand() % 2000 - 1000;

    int target = arr[rand() % arraySize];

    double t1 = TestSearchAlgorithm(9, arr, target);
    double t2 = TestSearchAlgorithm(10, arr, target);
    double t3 = TestSearchAlgorithm(1, arr, target);

    cout << "\nРЕЗУЛЬТАТИ ТЕСТУ (" << arraySize << " елементів):\n";
    cout << "Алгоритм         | Час (сек)\n";
    cout << "-----------------|-----------\n";
    cout << "Лінійний пошук   | " << t1 << "\n";
    cout << "Двійковий пошук  | " << t2 << "\n";
    cout << "Стрибковий пошук | " << t3 << "\n";
}

