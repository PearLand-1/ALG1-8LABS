/* ======================================================= 

    Алгоритми і структура данних
    Лабораторна робота №1-8
    Виконав: Чорноус Сергій ІПЗ-22

 ======================================================= */

#include "sort.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include "../MyLib.h"

using namespace std;

// ===== SELECTION SORT =====
void SelectionSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = n - 1; j > 0; j--)
    {
        int idx = 0;

        for (int i = 1; i <= j; i++)
        {
            if ((ascending && a[i] > a[idx]) ||
                (!ascending && a[i] < a[idx]))
                idx = i;

            if (visualize)
            {
                Log("Пошук максимуму...");
                PrintArray(a, i, idx);
            }
        }

        if (idx != j) {
            swap(a[idx], a[j]);
            if (visualize)
            {
                Log("Обмін:");
                PrintArray(a, idx, j);
            }
        } else {
            if (visualize) {
                Log("Без змін (обміну не було):");
                PrintArray(a, -1, -1);
            }
        }
    }

    if (n <= 200) 
    {
        LogSuccess("Відсортовано SelectionSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано SelectionSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== INSERTION SORT =====
void InsertionSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = 1; j < n; j++)
    {
        int key = a[j];
        int i = j - 1;

        bool swapped = false; 

        while (i >= 0 && 
            ((ascending && a[i] > key) ||
            (!ascending && a[i] < key)))
        {
            a[i + 1] = a[i];
            i--;
            swapped = true;

            if (visualize)
            {
                Log("Зсув елементів...");
                PrintArray(a, i, j);
            }
        }

        a[i + 1] = key;

        if (visualize)
        {
            Log("Вставка:");
            PrintArray(a, i + 1, j);
        }

        if (!swapped && visualize) {
            Log("Без змін (зсувів не було):");
            PrintArray(a, -1, -1);
        }
    }

    if (n <= 200) 
    {
        LogSuccess("Відсортовано InsertionSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано InsertionSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== BUBBLE SORT =====
void BubbleSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();

    for (int j = 0; j < n - 1; j++)
    {
        bool swapped = false;

        for (int i = 0; i < n - j - 1; i++)
        {
            if ((ascending && a[i] > a[i + 1]) ||
                (!ascending && a[i] < a[i + 1]))
            {
                swap(a[i], a[i + 1]);
                swapped = true;

                if (visualize)
                {
                    Log("Обмін сусідніх:");
                    PrintArray(a, i, i + 1);
                }
            }
        }

        if (!swapped && visualize)
        {
            Log("Без змін (обміну не було):");
            PrintArray(a, -1, -1);
        }

        if (!swapped)
            break;
    }

    if (n <= 200) 
    {
        LogSuccess("Відсортовано BubbleSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано BubbleSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== MERGE SORT =====
void Merge(vector<int>& a, int left, int mid, int right, bool visualize, bool ascending)
{
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if ((ascending && a[i] < a[j]) ||
            (!ascending && a[i] > a[j]))
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);

        if (visualize)
            PrintArray(a, i, j);
    }

    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);

    for (int k = 0; k < temp.size(); k++)
        a[left + k] = temp[k];

    // Візуалізація після кожного злиття
    if (visualize)
        PrintArray(a, -1, -1);
}

void MergeSortRec(vector<int>& a, int left, int right, bool visualize, bool ascending)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    MergeSortRec(a, left, mid, visualize, ascending);
    MergeSortRec(a, mid + 1, right, visualize, ascending);
    Merge(a, left, mid, right, visualize, ascending);
}

void MergeSort(vector<int>& a, bool visualize, bool ascending)
{
    MergeSortRec(a, 0, a.size() - 1, visualize, ascending);
    if (a.size() <= 200) 
    {
        LogSuccess("Відсортовано MergeSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано MergeSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== QUICK SORT =====
int Partition(vector<int>& a, int low, int high, bool visualize, bool ascending)
{
    int pivot = a[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if ((ascending && a[j] < pivot) || (!ascending && a[j] > pivot)) {
            i++;
            swap(a[i], a[j]);
            if (visualize) {
                Log("Обмін:");
                PrintArray(a, i, j);
            }
        }
    }
    swap(a[i + 1], a[high]);
    if (visualize) {
        Log("Опорний елемент на місці:");
        PrintArray(a, i + 1, high);
    }
    return i + 1;
}

void QuickSortRec(vector<int>& a, int low, int high, bool visualize, bool ascending)
{
    if (low < high) {
        int pi = Partition(a, low, high, visualize, ascending);
        QuickSortRec(a, low, pi - 1, visualize, ascending);
        QuickSortRec(a, pi + 1, high, visualize, ascending);
    }
}

void QuickSort(vector<int>& a, bool visualize, bool ascending)
{
    QuickSortRec(a, 0, a.size() - 1, visualize, ascending);
    if (a.size() <= 200) 
    {
        LogSuccess("Відсортовано QuickSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано QuickSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== SHELL SORT =====
void ShellSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            
            for (j = i; j >= gap && ((ascending && a[j - gap] > temp) || (!ascending && a[j - gap] < temp)); j -= gap) {
                a[j] = a[j - gap];
                if (visualize) {
                    Log("Зсув з кроком " + to_string(gap));
                    PrintArray(a, j - gap, j);
                }
            }
            a[j] = temp;
            
            if (visualize && j != i) {
                Log("Вставка:");
                PrintArray(a, j, i);
            }
        }
    }
    if (n <= 200) 
    {
        LogSuccess("Відсортовано ShellSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано ShellSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== SHAKER SORT =====
void ShakerSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();
    int left = 0, right = n - 1;
    bool swapped;
    
    do {
        swapped = false;
        
        // Прохід зліва направо
        for (int i = left; i < right; i++) {
            if ((ascending && a[i] > a[i + 1]) || (!ascending && a[i] < a[i + 1])) {
                swap(a[i], a[i + 1]);
                swapped = true;
                if (visualize) {
                    Log("Обмін (←→):");
                    PrintArray(a, i, i + 1);
                }
            }
        }
        right--;
        
        if (!swapped) break;
        swapped = false;
        
        // Прохід справа наліво
        for (int i = right; i > left; i--) {
            if ((ascending && a[i - 1] > a[i]) || (!ascending && a[i - 1] < a[i])) {
                swap(a[i - 1], a[i]);
                swapped = true;
                if (visualize) {
                    Log("Обмін (→←):");
                    PrintArray(a, i - 1, i);
                }
            }
        }
        left++;
    } while (swapped);
    
    if (n <= 200) 
    {
        LogSuccess("Відсортовано ShakerSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано ShakerSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== HEAP SORT =====
void Heapify(vector<int>& a, int n, int i, bool visualize, bool ascending)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Порівнюємо з лівим дочірнім вузлом
    if (left < n && ((ascending && a[left] > a[largest]) || (!ascending && a[left] < a[largest])))
        largest = left;
    
    // Порівнюємо з правим дочірнім вузлом
    if (right < n && ((ascending && a[right] > a[largest]) || (!ascending && a[right] < a[largest])))
        largest = right;
    
    // Якщо найбільший елемент не є поточним
    if (largest != i) {
        swap(a[i], a[largest]);
        if (visualize) {
            Log("Обмін у купі:");
            PrintArray(a, i, largest);
        }
        // Рекурсивно відновлюємо купу
        Heapify(a, n, largest, visualize, ascending);
    }
}

void HeapSort(vector<int>& a, bool visualize, bool ascending)
{
    int n = a.size();
    
    // Будуємо максимальну (або мінімальну) купу
    for (int i = n / 2 - 1; i >= 0; i--) {
        if (visualize) {
            Log("Побудова купи:");
            PrintArray(a, -1, -1);
        }
        Heapify(a, n, i, visualize, ascending);
    }
    
    // Витягуємо елементи з купи один за одним
    for (int i = n - 1; i > 0; i--) {
        // Переміщуємо поточний корінь (найбільший елемент) на край
        swap(a[0], a[i]);
        if (visualize) {
            Log("Переміщення коренів купи:");
            PrintArray(a, 0, i);
        }
        // Відновлюємо купу для скороченого масиву
        Heapify(a, i, 0, visualize, ascending);
    }
    
    if (n <= 200) 
    {
        LogSuccess("Відсортовано HeapSort():");
        PrintArray(a, -1, -1);
    } else {
        LogSuccess("Відсортовано HeapSort().\nРозмір масиву перевищує 200, результат не відображатиметься");
    }
}

// ===== МЕНЮ =====

void RunAlgorithm(int type)
{
    bool visualize;
    Log("Візуалізувати? 1 - так, 0 - ні\n>> ");
    cin >> visualize;
    
    if (visualize)
    {
        Log("Затримка (мс, рекомендовано 100-1000)\n>> ");
        cin >> visualizationDelay;
    }

    int orderChoice;
    Log("Порядок сортування:");
    Log("1 - За зростанням");
    Log("2 - За спаданням\n>> ");
    cin >> orderChoice;

    bool ascending = (orderChoice == 1);

    int inputType;
    Log("1 - Ввести вручну\n2 - Випадкові значення\n>> ");
    cin >> inputType;

    vector<int> arr;

    if (inputType == 1)
        arr = InputArray();
    else
        arr = RandomArray();

    Log("Початковий масив:");
    PrintArray(arr, -1, -1);

    switch (type)
    {
    case 1: SelectionSort(arr, visualize, ascending); break;
    case 2: InsertionSort(arr, visualize, ascending); break;
    case 3: BubbleSort(arr, visualize, ascending); break;
    case 4: MergeSort(arr, visualize, ascending); break;
    case 5: QuickSort(arr, visualize, ascending); break;
    case 6: ShellSort(arr, visualize, ascending); break;
    case 7: ShakerSort(arr, visualize, ascending); break;
    case 8: HeapSort(arr, visualize, ascending); break;
    }
}