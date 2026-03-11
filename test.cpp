#include <iostream>
#include <chrono>
#include "sort.h"
#include "test.h"

using namespace std;

double TestSortingAlgorithm(int algorithmType, vector<int> arr) {
    bool visualize = false;
    visualizationDelay = 0;

    auto start = chrono::high_resolution_clock::now();
    switch (algorithmType) {
        case 1: SelectionSort(arr, visualize, true); break;
        case 2: InsertionSort(arr, visualize, true); break;
        case 3: BubbleSort(arr, visualize, true); break;
        case 4: MergeSort(arr, visualize, true); break;
        case 5: QuickSort(arr, visualize, true); break;
        case 6: ShellSort(arr, visualize, true); break;
        case 7: ShakerSort(arr, visualize, true); break;
        case 8: HeapSort(arr, visualize, true); break;
        default:
            cout << "Невірний тип сортування!" << endl;
            return 0.0;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    return diff.count();
}

void RunTest(int arraySize) {
    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; i++)
        arr[i] = rand() % 2000 - 1000;
    
    double t1 = TestSortingAlgorithm(1, arr);
    double t2 = TestSortingAlgorithm(2, arr);
    double t3 = TestSortingAlgorithm(3, arr);
    double t4 = TestSortingAlgorithm(4, arr);
    double t5 = TestSortingAlgorithm(5, arr);
    double t6 = TestSortingAlgorithm(6, arr);
    double t7 = TestSortingAlgorithm(7, arr);
    double t8 = TestSortingAlgorithm(8, arr);

    cout << "\nРЕЗУЛЬТАТИ ТЕСТУ (" << arraySize << " елементів):\n";
    cout << "Алгоритм         | Час (сек)\n";
    cout << "-----------------|-----------\n";
    cout << "Selection Sort   | " << t1 << "\n";
    cout << "Insertion Sort   | " << t2 << "\n";
    cout << "Bubble Sort      | " << t3 << "\n";
    cout << "Merge Sort       | " << t4 << "\n";
    cout << "Quick Sort       | " << t5 << "\n";
    cout << "Shell Sort       | " << t6 << "\n";
    cout << "Shaker Sort      | " << t7 << "\n";
    cout << "Heap Sort        | " << t8 << "\n";
}

int test() {
    vector<int> arr = { 5, 2, -3, 10, 8, 1, 7, -4, 3 };
    
    cout << "Масив для сортування: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    double t1 = TestSortingAlgorithm(1, arr);
    double t2 = TestSortingAlgorithm(2, arr);
    double t3 = TestSortingAlgorithm(3, arr);
    double t4 = TestSortingAlgorithm(4, arr);

    cout << "\nРЕЗУЛЬТАТИ ТЕСТУ:\n";
    cout << "Алгоритм         | Час (сек)\n";
    cout << "-----------------|-----------\n";
    cout << "Selection Sort   | " << t1 << "\n";
    cout << "Insertion Sort   | " << t2 << "\n";
    cout << "Bubble Sort      | " << t3 << "\n";
    cout << "Merge Sort       | " << t4 << "\n";

    return 0;
}